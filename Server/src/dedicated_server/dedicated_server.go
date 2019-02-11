// Filename:    dedicated_server.go
// Author:      Joseph DeVictoria
// Date:        June_13_2018
// Purpose:     The dedicated game server for Oldentide written in Go.

package main

import (
	"database/sql"
	"flag"
	"fmt"
	_ "github.com/mattn/go-sqlite3"
	"github.com/vmihailenco/msgpack"
	"log"
	"math/rand"
	"net"
	"net/http"
	"net/smtp"
	"runtime"
	"strconv"
	"time"
)

// Global program variables.
var err error
var gport int
var wport int
var everify bool
var webadd string
var email string
var epass string
var eauth smtp.Auth
var db *sql.DB

func init() {
	flag.IntVar(&gport, "gport", 0, "Port used for dedicated game server.")
	flag.IntVar(&wport, "wport", 0, "Port used for website.")
	flag.BoolVar(&everify, "everify", false, "Use an emailer to verify accounts?")
	flag.StringVar(&webadd, "webadd", "", "Public website root address where accounts will be created.")
	flag.StringVar(&email, "email", "", "Gmail email address used to send verification emails.")
	flag.StringVar(&epass, "epass", "", "Gmail email password used to send verification emails.")
	rand.Seed(time.Now().UTC().UnixNano())
}

func main() {
	// Extract command line input.
	flag.Parse()
	fmt.Println("\n-------------------------------------------------------")
	fmt.Println("Server Configurations from command line:")
	fmt.Println("-------------------------------------------------------")
	fmt.Println("gport:", gport)
	fmt.Println("wport:", wport)
	fmt.Println("webadd:", webadd)
	fmt.Println("everify:", everify)
	fmt.Println("email:", email)
	fmt.Println("epass:", epass)
	if gport == 0 {
		log.Fatal("Please provide a game port with the command line flag -gport=<number>")
	}
	if wport == 0 {
		log.Fatal("Please provide a website port with the command line flag -wport=<number>")
	}
	if webadd == "" {
		log.Fatal("Please provide the website address/ip with the command line flag -webadd=<www.address.domain>")
	}
	if everify {
		if email == "" {
			log.Fatal("Please provide a Gmail email account with the command line flag -email=<email@gmail.com>")
		}
		if epass == "" {
			log.Fatal("Please provide a Gmail email password with the command line flag -epass=<P@55word>")
		}
	} else {
		fmt.Println("Warning: website allowing account creation without email verification!")
		fmt.Println("To enable email verification please use the command line flag -everify")
	}
	eauth = smtp.PlainAuth("", email, epass, "smtp.gmail.com")
	fmt.Println("\n-------------------------------------------------------")
	fmt.Println("Starting Oldentide dedicated server!")
	fmt.Println("-------------------------------------------------------")

	// --------------------------------------------------------------------------------------------
	// Opening database.
	// --------------------------------------------------------------------------------------------

	db, err = sql.Open("sqlite3", "../../../Server/db/Oldentide.db")
	checkErr(err)
	fmt.Println("* Database connected.\n")

	// Initialize the game state (populates all of the npcs, and game objects, etc).
	// --------------------------------------------------------------------------------------------
	pcs := pullPcs()
	fmt.Println("* PCs populated from database:\n")
	for _, pc := range pcs {
		fmt.Println(pc)
	}

	npcs := pullNpcs()
	fmt.Println("\n* NPCs populated from database:\n")
	for _, npc := range npcs {
		fmt.Println(npc)
	}

	// items : pullItems()

	// inventories := pullInventories()

	// --------------------------------------------------------------------------------------------
	// Kick off http server for registration page.
	// --------------------------------------------------------------------------------------------
	mux := http.NewServeMux()
	mux.HandleFunc("/", routeWebTraffic)
	go http.ListenAndServe(":"+strconv.Itoa(wport), mux)

	// --------------------------------------------------------------------------------------------
	// Create and bind a udp socket descriptor.
	// --------------------------------------------------------------------------------------------
	server_address := net.UDPAddr{
		IP:   net.IP{0, 0, 0, 0},
		Port: gport,
	}
	socket, err := net.ListenUDP("udp", &server_address)
	checkErr(err)

	// --------------------------------------------------------------------------------------------
	// Start our collecter to pull in packets from the hardware socket.
	// --------------------------------------------------------------------------------------------
	RawPacketQueue := make(chan raw_packet, 100000)
	QuitChan := make(chan bool)
	go Collect(socket, RawPacketQueue, QuitChan)
	fmt.Println("\n* Collector Launched.\n")

	// --------------------------------------------------------------------------------------------
	// Start as many handler goroutines as we have processors.
	// Should result in non-thrashing handler thread concurrency.
	// --------------------------------------------------------------------------------------------
	for i := 0; i < runtime.NumCPU(); i++ {
		go Handle(RawPacketQueue, QuitChan, i)
		fmt.Println("* Handler ", i+1, " of ", runtime.NumCPU(), " Launched.")
	}

	// Wait for a message to the Quit Channel to halt execution.
	<-QuitChan

	// Close database.
	db.Close()
}

// Places all UDP packets that arrive on the hardware socket into a queue for handling.
func Collect(connection *net.UDPConn, RawPacketQueue chan raw_packet, QuitChan chan bool) {
	for err == nil {
		buffer := make([]byte, 512) //65507) // Max IPv4 UDP packet size.
		n, remote_address, err := connection.ReadFromUDP(buffer)
		checkErr(err)
		RawPacketQueue <- raw_packet{n, remote_address, buffer}
	}
	fmt.Println("Collector Exited - ", err)
}

// Handle all arriving packets based on which opcode they are.
func Handle(RawPacketQueue chan raw_packet, QuitChan chan bool, rid int) {
	var packet raw_packet
	for {
		select {
		// This case will run when there is a packet available at the front of the packet queue.
		case packet = <-RawPacketQueue:
			//fmt.Println("Goroutine ID:", rid, "Size:", packet.Size, "Sender:", packet.Client, "Payload:", packet.Payload[:packet.Size]) //debug
			var op op_packet
			err = msgpack.Unmarshal(packet.Payload, &op)
			ifErrPrintErr(err)
			// Depending on what packet opcode we recieved, handle the data accordingly.
			switch op.Opcode {
			case EMPTY:
				fmt.Println("Handling an EMPTY packet.")
				continue
			case GENERIC:
				fmt.Println("Handling a GENERIC packet.")
				continue
			case ACK:
				fmt.Println("Handling an ACK packet.")
				continue
			case ERROR:
				fmt.Println("Handling an ERROR packet.")
				continue
			case REQCLIST:
				fmt.Println("Handling a REQCLIST packet.")
				continue
			case CREATEPLAYER:
				fmt.Println("Handling a CREATEPLAYER packet.")
				var cpp create_player_packet
				err = msgpack.Unmarshal(packet.Payload, &cpp)
				fmt.Println(cpp)
				// Need to get the account name by session id.
				account_name := "Jojo"
				player_name := "Joseph"
				if getRemainingPlayerSlots(account_name, 10) == 0 {
					log.Println("Account tried to create too many players.")
					continue
				}
				if playerFirstNameTaken(player_name) {
					log.Println("Account tried to create a player whose name was already taken.")
					continue
				}
				if validNewPlayer(cpp.Pc) {
					addNewPlayer(cpp.Pc)
					log.Println("Account <account> created a new player \"<player>\".")
				} else {
					log.Println("Account is trying something fraudulent during account creation!")
					//banAccount()
					continue
				}
			case CONNECT:
				fmt.Println("Handling a CONNECT packet.")
				continue
			case DISCONNECT:
				fmt.Println("Handling a DISCONNECT packet.")
				continue
			case MOVEPLAYER:
				fmt.Println("Handling a MOVEPLAYER packet.")
				continue
			case SPENDDP:
				fmt.Println("Handling a SPENDDP packet.")
				continue
			case TALKCMD:
				fmt.Println("Handling a TALKCMD packet.")
				continue
			case ATTACKCMD:
				fmt.Println("Handling a ATTACKCMD packet.")
				continue
			case TRADECMD:
				fmt.Println("Handling a TRADECMD packet.")
				continue
			case INVITECMD:
				fmt.Println("Handling a INVITECMD packet.")
				continue
			case GINVITECMD:
				fmt.Println("Handling a GINVITECMD packet.")
				continue
			case GKICK:
				fmt.Println("Handling a GKICK packet.")
				continue
			case GPROMOTE:
				fmt.Println("Handling a GPROMOTE packet.")
				continue
			case SAYCMD:
				fmt.Println("Handling a SAYCMD packet.")
				continue
			case YELLCMD:
				fmt.Println("Handling a YELLCMD packet.")
				continue
			case OOCCMD:
				fmt.Println("Handling a OOCCMD packet.")
				continue
			case HELPCMD:
				fmt.Println("Handling a HELPCMD packet.")
				continue
			case GCHATCMD:
				fmt.Println("Handling a GCHATCMD packet.")
				continue
			case WHISPERCMD:
				fmt.Println("Handling a WHISPERCMD packet.")
				continue
			case ACTIVATECMD:
				fmt.Println("Handling a ACTIVATECMD packet.")
				continue
			case DIALOGCMD:
				fmt.Println("Handling a DIALOGCMD packet.")
				continue
			case BUYITEM:
				fmt.Println("Handling a BUYITEM packet.")
				continue
			case TAKELOOT:
				fmt.Println("Handling a TAKELOOT packet.")
				continue
			case OFFERITEM:
				fmt.Println("Handling a OFFERITEM packet.")
				continue
			case PULLITEM:
				fmt.Println("Handling a PULLITEM packet.")
				continue
			case ACCTRADE:
				fmt.Println("Handling a ACCTRADE packet.")
				continue
			case UNACCTRADE:
				fmt.Println("Handling a UNACCTRADE packet.")
				continue
			default:
				continue
			}
		}
	}
}
