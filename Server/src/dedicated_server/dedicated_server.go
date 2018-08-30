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
	fmt.Println("Server Configurations from command line:")
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
	fmt.Println("Starting Oldentide dedicated server!")

	// --------------------------------------------------------------------------------------------
	// Opening database.
	// --------------------------------------------------------------------------------------------

	db, err = sql.Open("sqlite3", "../../../Server/db/Oldentide.db")
	checkErr(err)

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
	RawPacketQueue := make(chan RawPacket, 1000000)
	QuitChan := make(chan bool)
	go Collect(socket, RawPacketQueue, QuitChan)
	go Dispatch(RawPacketQueue, QuitChan)

	// Start as many worker goroutines as we have processors.
	// Should result in non-thrashing listener thread concurrency? Not sure go is weird.
	for i := 0; i < runtime.NumCPU(); i++ {
		fmt.Println("Core_", i)
	}

	// Close database.
	db.Close()
}

// Listen for new udp packet on the hardware socket.
// When a packet arrives, we place it into a go channel for dispatching.
func Collect(connection *net.UDPConn, RawPacketQueue chan RawPacket, QuitChan chan bool) {
	buffer := make([]byte, 65507) // Max IPv4 UDP packet size.
	for err == nil {
		n, remote_address, err := connection.ReadFromUDP(buffer)
		checkErr(err)
		RawPacketQueue <- RawPacket{n, remote_address, buffer}
	}
	fmt.Println("Collector Exited - ", err)
}

// As soon as packets arrive from the collector, identify what type of packet they are.
// Prepare a worker thread to handle the appropriate packet opcode.
func Dispatch(RawPacketQueue chan RawPacket, QuitChan chan bool) {
    for packet := range RawPacketQueue {
        var tp TestPacket
        err = msgpack.Unmarshal(packet.Payload, &tp)
        fmt.Println(packet.Size, packet.Client, packet.Payload[:packet.Size], tp.Payload)
    }
}

/*type Worker struct {
    Id int
    Work chan WorkRequest
    WorkerQueue chan WorkRequest
    QuitChan chan bool
}

// Recieve a work request and handle it according to the opcode.
// This function is the bulk meat of what the server does.
func Work() {
    for {
        select {
        case work := <-w.Work:
          // Receive a work request.
          fmt.Printf("Worker_d: Received work request, delaying for %f seconds\n", w.ID, 1)
          time.Sleep(1)
          fmt.Printf("Worker_%d: Hello, %s!\n", w.ID, )
        case <-w.QuitChan:
          // We have been asked to stop.
          fmt.Printf("Worker_%d stopping\n", w.ID)
          return
        }
    }
}*/
