// Filename:    packet.go
// Author:      Joseph DeVictoria
// Date:        June_16_2018
// Purpose:     Definition of packets to be used in Oldentide.

package main

import (
	_ "fmt"
	_ "github.com/vmihailenco/msgpack"
	"net"
)

// Packet types. - These will probably need some tweaking in the future.
type opcode uint8

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
	SHOPCMD      opcode = iota // CLIENT - Player initiated shop command (with npc).
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

type RawPacket struct {
	Size    int
	Client  *net.UDPAddr
	Payload []byte
}

type TestPacket struct {
	Payload string
}
