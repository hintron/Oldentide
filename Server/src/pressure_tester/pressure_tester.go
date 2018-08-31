// Filename:    dedicated_server.go
// Author:      Joseph DeVictoria
// Date:        June_13_2018
// Purpose:     The dedicated game server for Oldentide written in Go.

package main

import (
	"flag"
	"fmt"
	"github.com/vmihailenco/msgpack"
	"log"
	"math/rand"
	"net"
	"strconv"
	"time"
)

// Global program variables.
var err error
var sport int
var sadd string

// Packet types. - These will probably need some tweaking in the future.
type opcode uint8

type OpPacket struct {
	Opcode opcode
}

const (
	EMPTY        opcode = iota // BOTH - Ignore these.
	GENERIC      opcode = iota // BOTH - Used for debug.
	ACK          opcode = iota // BOTH - Acknoledge that packet was received.
	ERROR        opcode = iota // BOTH - Pass error message.
	REQCLIST     opcode = iota // CLIENT - Client requests character list.
	SENDCLIST    opcode = iota // SERVER - Server sends character list.
	CONNECT      opcode = iota // CLIENT - Player selects a character and connects to server..
	DISCONNECT   opcode = iota // CLIENT - Player disconnects from the server.
	SENDPLAYER   opcode = iota // SERVER - Send all of the information to fully update the main player.
	SENDPC       opcode = iota // SERVER - Send all the needed information to set up or uptade another PC.
	SENDNPC      opcode = iota // SERVER - Send all the needed information to set up & update an NPC.
	MOVEPLAYER   opcode = iota // CLIENT - Send position information based on player input/actions.
	SPENDDP      opcode = iota // CLIENT - Send a request of dp expenditures for validation.
	TALKCMD      opcode = iota // CLIENT - <PLACEHOLDER> Player initiated talk command (with npc).
	ATTACKCMD    opcode = iota // CLIENT - Player initiated attack command (with npc or player).
	TRADECMD     opcode = iota // CLIENT - Player initiated trade command (with player).
	INVITECMD    opcode = iota // CLIENT - Player initiated invite command (with player).
	GINVITECMD   opcode = iota // CLIENT - Player initiated guild invite command (with player).
	GKICK        opcode = iota // CLIENT - Player initiated guild kick command (with player).
	GPROMOTE     opcode = iota // CLIENT - Player initiated a guild officer promotion command (with player).
	SAYCMD       opcode = iota // CLIENT - Player said something with /s command.
	YELLCMD      opcode = iota // CLIENT - Player said something with /y command.
	OOCCMD       opcode = iota // CLIENT - Player said something with /ooc command.
	HELPCMD      opcode = iota // CLIENT - Player said something with /h command.
	GCHATCMD     opcode = iota // CLIENT - Player said something with /g command.
	WHISPERCMD   opcode = iota // CLIENT - Player said something with /w command (with player).
	RELAYSAY     opcode = iota // SERVER - Relay a say command to proper clients.
	RELAYYELL    opcode = iota // SERVER - Relay a yell command to proper clients.
	RELAYOOC     opcode = iota // SERVER - Relay an ooc command to proper clients.
	RELAYHELP    opcode = iota // SERVER - Relay a help command to proper clients.
	RELAYGCHAT   opcode = iota // SERVER - Relay a guild chat command to proper clients.
	RELAYWHISPER opcode = iota // SERVER - Relay a whisper command to proper client.
	ACTIVATECMD  opcode = iota // CLIENT - Player initiated game object activation command (with door/chest/switch).
	ENVUPDATE    opcode = iota // SERVER - Send a flag to appropriate clients for an environemnt variable (door/chest/switch).
	DIALOGTEXT   opcode = iota // SERVER - <PLACEHOLDER> Send dialog + options to client.
	DIALOGCMD    opcode = iota // PLAYER - <PLACEHOLDER> Send dialog response from player.
	SENDITEM     opcode = iota // SERVER - Server successfully awards a given item to a designated player.
	INITSHOP     opcode = iota // SERVER - <PLACEHOLDER> Server has started a shop window.
	SHOPITEM     opcode = iota // SERVER - <PLACEHOLDER> Send item to shop inventory.
	BUYITEM      opcode = iota // CLIENT - <PLACEHOLDER> Player tries to purchase an item.
	INITLOOT     opcode = iota // SERVER - <PLACEHOLDER> Server has started a loot window.
	LOOTITEM     opcode = iota // SERVER - <PLACEHOLDER> Send item to loot inventory.
	TAKELOOT     opcode = iota // CLIENT - <PLACEHOLDER> Player tried to take a loot item.
	INITTRADE    opcode = iota // SERVER - <PLACEHOLDER> Server has started a trade window.
	OFFERITEM    opcode = iota // CLIENT - <PLACEHOLDER> Player has offered an item for trade.
	PULLITEM     opcode = iota // CLIENT - <PLACEHOLDER> Player has removed an item for trade.
	TRADEITEM    opcode = iota // SERVER - <PLACEHOLDER> Server communicates item to trade window.
	REMITEM      opcode = iota // SERVER - <PLACEHOLDER> Server removes item from trade window.
	ACCTRADE     opcode = iota // CLIENT - <PLACEHOLDER> Player has accepted a trade.
	UNACCTRADE   opcode = iota // CLIENT - <PLACEHOLDER> Player has unaccepted a trade..
	COMMTRADE    opcode = iota // SERVER - <PLACEHOLDER> Communicate trade acceptance status to trade window..
	FINTRADE     opcode = iota // SERVER - <PLACEHOLDER> Close trade window and inform player trade was accepted..
	INITCOMABT   opcode = iota // SERVER - Initialize a combat session on client.
	ADDNPCCOMBAT opcode = iota // SERVER - Add an NPC to a combat session on client.
	ADDPCCOMABT  opcode = iota // SERVER - Add a PC to a combat session on client.
	REMNPCCOMBAT opcode = iota // SERVER - Remove an NPC from a combat session on client.
	REMPCCOMBAT  opcode = iota // SERVER - Remove a PC from a combat session on client.
	// Need to continue adding here...
	// CASTSPELL opcode = , // CLIENT -
)

func init() {
	flag.IntVar(&sport, "sport", 0, "Port used for dedicated game server.")
	flag.StringVar(&sadd, "sadd", "", "Address/ip used for dedicated game server.")
	rand.Seed(time.Now().UTC().UnixNano())
}

func main() {
	// Extract command line input.
	flag.Parse()
	fmt.Println("Server Configurations from command line:")
	fmt.Println("port:", sport)
	fmt.Println("add:", sadd)
	if sport == 0 {
		log.Fatal("Please provide a game port with the command line flag -sport=<number>")
	}
	if sadd == "" {
		log.Fatal("Please provide the server address/ip with the command line flag -sadd=<www.address.domain>")
	}
	fmt.Println("Starting Oldentide pressure tester!")

	// Create udp socket description struct.
	server_connection, err := net.Dial("udp", sadd+":"+strconv.Itoa(sport))
	checkErr(err)

	opcodes := []opcode{EMPTY, GENERIC, ACK, ERROR, REQCLIST, SENDCLIST, CONNECT, DISCONNECT, SENDPLAYER, SENDPC, SENDNPC, MOVEPLAYER, SPENDDP, TALKCMD, ATTACKCMD, TRADECMD, INVITECMD, GINVITECMD, GKICK, GPROMOTE, SAYCMD, YELLCMD, OOCCMD, HELPCMD, GCHATCMD, WHISPERCMD, RELAYSAY, RELAYYELL, RELAYOOC, RELAYHELP, RELAYGCHAT, RELAYWHISPER, ACTIVATECMD, ENVUPDATE, DIALOGTEXT, DIALOGCMD, SENDITEM, INITSHOP, SHOPITEM, BUYITEM, INITLOOT, LOOTITEM, TAKELOOT, INITTRADE, OFFERITEM, PULLITEM, TRADEITEM, REMITEM, ACCTRADE, UNACCTRADE, COMMTRADE, FINTRADE, INITCOMABT, ADDNPCCOMBAT, ADDPCCOMABT, REMNPCCOMBAT, REMPCCOMBAT}

	for _, op := range opcodes {
		// Build a test packet.
		p, err := msgpack.Marshal(&OpPacket{Opcode: op})
		checkErr(err)

		// Fire it off to our server!
		server_connection.Write(p)
	}
}

// Simple function to check the error status of an operation.
func checkErr(err error) {
	if err != nil {
		log.Fatal(err)
	}
}
