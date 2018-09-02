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
	CREATEPLAYER opcode = iota // CLIENT - Player sends the data for his newly created character.
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

type pc struct {
	Id             int32
	Account_id     int32
	Firstname      string
	Lastname       string
	Guild          string
	Race           string
	Gender         string
	Face           string
	Skin           string
	Profession     string
	Alive          bool
	Plevel         int32
	Dp             int32
	Hp             int32
	Maxhp          int32
	Bp             int32
	Maxbp          int32
	Mp             int32
	Maxmp          int32
	Ep             int32
	Maxep          int32
	Strength       int32
	Constitution   int32
	Intelligence   int32
	Dexterity      int32
	Axe            int32
	Dagger         int32
	Unarmed        int32
	Hammer         int32
	Polearm        int32
	Spear          int32
	Staff          int32
	Sword          int32
	Archery        int32
	Crossbow       int32
	Sling          int32
	Thrown         int32
	Armor          int32
	Dualweapon     int32
	Shield         int32
	Bardic         int32
	Conjuring      int32
	Druidic        int32
	Illusion       int32
	Necromancy     int32
	Sorcery        int32
	Shamanic       int32
	Spellcraft     int32
	Summoning      int32
	Focus          int32
	Armorsmithing  int32
	Tailoring      int32
	Fletching      int32
	Weaponsmithing int32
	Alchemy        int32
	Lapidary       int32
	Calligraphy    int32
	Enchanting     int32
	Herbalism      int32
	Hunting        int32
	Mining         int32
	Bargaining     int32
	Camping        int32
	Firstaid       int32
	Lore           int32
	Picklocks      int32
	Scouting       int32
	Search         int32
	Stealth        int32
	Traps          int32
	Aeolandis      int32
	Hieroform      int32
	Highgundis     int32
	Oldpraxic      int32
	Praxic         int32
	Runic          int32
	Head           string
	Chest          string
	Arms           string
	Hands          string
	Legs           string
	Feet           string
	Cloak          string
	Necklace       string
	Ringone        string
	Ringtwo        string
	Righthand      string
	Lefthand       string
	Zone           string
	X              float32
	Y              float32
	Z              float32
	Direction      float32
}

type create_player_packet struct {
    Opcode opcode
    Pc pc
}

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

	//opcodes := []opcode{EMPTY, GENERIC, ACK, ERROR, REQCLIST, SENDCLIST, CONNECT, DISCONNECT, SENDPLAYER, SENDPC, SENDNPC, MOVEPLAYER, SPENDDP, TALKCMD, ATTACKCMD, TRADECMD, INVITECMD, GINVITECMD, GKICK, GPROMOTE, SAYCMD, YELLCMD, OOCCMD, HELPCMD, GCHATCMD, WHISPERCMD, RELAYSAY, RELAYYELL, RELAYOOC, RELAYHELP, RELAYGCHAT, RELAYWHISPER, ACTIVATECMD, ENVUPDATE, DIALOGTEXT, DIALOGCMD, SENDITEM, INITSHOP, SHOPITEM, BUYITEM, INITLOOT, LOOTITEM, TAKELOOT, INITTRADE, OFFERITEM, PULLITEM, TRADEITEM, REMITEM, ACCTRADE, UNACCTRADE, COMMTRADE, FINTRADE, INITCOMABT, ADDNPCCOMBAT, ADDPCCOMABT, REMNPCCOMBAT, REMPCCOMBAT}

	/*for _, op := range opcodes {
		// Build a test packet.
		p, err := msgpack.Marshal(&OpPacket{Opcode: op})
		checkErr(err)

		// Fire it off to our server!
		server_connection.Write(p)
	}*/

    p := pc{Id: 0,Account_id: 0,Firstname: "Joseph",Lastname: "DeVictoria",Guild: "Gremlins",Race: "Human",Gender: "Male",Face: "White",Skin: "White",Profession: "Engineer",Alive: true,Plevel: 51,Dp: 12000,Hp: 450,Maxhp: 450,Bp: 250,Maxbp: 250,Mp: 300,Maxmp: 300,Ep: 150,Maxep: 150,Strength: 65,Constitution: 45,Intelligence: 50,Dexterity: 50,Axe: 0,Dagger: 0,Unarmed: 499,Hammer: 0,Polearm: 0,Spear: 0,Staff: 0,Sword: 0,Archery: 0,Crossbow: 0,Sling: 0,Thrown: 0,Armor: 300,Dualweapon: 499,Shield: 0,Bardic: 0,Conjuring: 0,Druidic: 0,Illusion: 0,Necromancy: 0,Sorcery: 0,Shamanic: 0,Spellcraft: 0,Summoning: 0,Focus: 0,Armorsmithing: 0,Tailoring: 0,Fletching: 0,Weaponsmithing: 0,Alchemy: 0,Lapidary: 0,Calligraphy: 0,Enchanting: 0,Herbalism: 0,Hunting: 0,Mining: 0,Bargaining: 0,Camping: 0,Firstaid: 0,Lore: 0,Picklocks: 0,Scouting: 0,Search: 0,Stealth: 0,Traps: 0,Aeolandis: 0,Hieroform: 0,Highgundis: 0,Oldpraxic: 100,Praxic: 100,Runic: 0,Head: "None",Chest: "None",Arms: "None",Hands: "None",Legs: "None",Feet: "None",Cloak: "None",Necklace: "None",Ringone: "None",Ringtwo: "None",Righthand: "None",Lefthand: "None",Zone: "Iskirrian Plains",X: 0,Y: 0,Z: 0,Direction: 47.3,}

    cpp := create_player_packet{Opcode: CREATEPLAYER, Pc: p}

    pac, err := msgpack.Marshal(cpp)
    checkErr(err)

    server_connection.Write(pac)
}

// Simple function to check the error status of an operation.
func checkErr(err error) {
	if err != nil {
		log.Fatal(err)
	}
}
