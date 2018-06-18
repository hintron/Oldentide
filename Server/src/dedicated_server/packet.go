// Filename:    packet.go
// Author:      Joseph DeVictoria
// Date:        June_16_2018
// Purpose:     Definition of packets to be used in Oldentide.

package main

import (
    _ "fmt"
    _ "github.com/vmihailenco/msgpack"
)

// Packet types. - These will probably need some tweaking in the future.
type ptype int

const (
    EMPTY ptype = iota // BOTH - Ignore these.
    GENERIC ptype = iota // BOTH - Used for debug.
    ACK ptype = iota // BOTH - Acknoledge that packet was received.
    ERROR ptype = iota // BOTH - Pass error message.
    REQCLIST ptype = iota // CLIENT - Client requests character list.
    SENDCLIST ptype = iota // SERVER - Server sends character list.
    CONNECT ptype = iota // CLIENT - Player selects a character and connects to server..
    DISCONNECT ptype = iota // CLIENT - Player disconnects from the server.
    SENDPLAYER ptype = iota // SERVER - Send all of the information to fully update the main player.
    SENDPC ptype = iota // SERVER - Send all the needed information to set up or uptade another PC.
    SENDNPC ptype = iota // SERVER - Send all the needed information to set up & update an NPC.
    MOVEPLAYER ptype = iota // CLIENT - Send position information based on player input/actions.
    SPENDDP ptype = iota // CLIENT - Send a request of dp expenditures for validation.
    TALKCMD ptype = iota // CLIENT - <PLACEHOLDER> Player initiated talk command (with npc).
    SHOPCMD ptype = iota // CLIENT - Player initiated shop command (with npc). 
    ATTACKCMD ptype = iota // CLIENT - Player initiated attack command (with npc or player).
    TRADECMD ptype = iota // CLIENT - Player initiated trade command (with player).
    INVITECMD ptype = iota // CLIENT - Player initiated invite command (with player).
    GINVITECMD ptype = iota // CLIENT - Player initiated guild invite command (with player).
    GKICK ptype = iota // CLIENT - Player initiated guild kick command (with player).
    GPROMOTE ptype = iota // CLIENT - Player initiated a guild officer promotion command (with player).
    SAYCMD ptype = iota // CLIENT - Player said something with /s command.
    YELLCMD ptype = iota // CLIENT - Player said something with /y command.
    OOCCMD ptype = iota // CLIENT - Player said something with /ooc command.
    HELPCMD ptype = iota // CLIENT - Player said something with /h command.
    GCHATCMD ptype = iota // CLIENT - Player said something with /g command.
    WHISPERCMD ptype = iota // CLIENT - Player said something with /w command (with player).
    RELAYSAY ptype = iota // SERVER - Relay a say command to proper clients.
    RELAYYELL ptype = iota // SERVER - Relay a yell command to proper clients.
    RELAYOOC ptype = iota // SERVER - Relay an ooc command to proper clients.
    RELAYHELP ptype = iota // SERVER - Relay a help command to proper clients.
    RELAYGCHAT ptype = iota // SERVER - Relay a guild chat command to proper clients.
    RELAYWHISPER ptype = iota // SERVER - Relay a whisper command to proper client.
    ACTIVATECMD ptype = iota // CLIENT - Player initiated game object activation command (with door/chest/switch).
    ENVUPDATE ptype = iota // SERVER - Send a flag to appropriate clients for an environemnt variable (door/chest/switch).
    DIALOGTEXT ptype = iota // SERVER - <PLACEHOLDER> Send dialog + options to client.
    DIALOGCMD ptype = iota // PLAYER - <PLACEHOLDER> Send dialog response from player.
    SENDITEM ptype = iota // SERVER - Server successfully awards a given item to a designated player.
    INITSHOP ptype = iota // SERVER - <PLACEHOLDER> Server has started a shop window.
    SHOPITEM ptype = iota // SERVER - <PLACEHOLDER> Send item to shop inventory.
    BUYITEM ptype = iota // CLIENT - <PLACEHOLDER> Player tries to purchase an item.
    INITLOOT ptype = iota // SERVER - <PLACEHOLDER> Server has started a loot window.
    LOOTITEM ptype = iota // SERVER - <PLACEHOLDER> Send item to loot inventory.
    TAKELOOT ptype = iota // CLIENT - <PLACEHOLDER> Player tried to take a loot item.
    INITTRADE ptype = iota // SERVER - <PLACEHOLDER> Server has started a trade window.
    OFFERITEM ptype = iota // CLIENT - <PLACEHOLDER> Player has offered an item for trade.
    PULLITEM ptype = iota // CLIENT - <PLACEHOLDER> Player has removed an item for trade.
    TRADEITEM ptype = iota // SERVER - <PLACEHOLDER> Server communicates item to trade window.
    REMITEM ptype = iota // SERVER - <PLACEHOLDER> Server removes item from trade window.
    ACCTRADE ptype = iota // CLIENT - <PLACEHOLDER> Player has accepted a trade.
    UNACCTRADE ptype = iota // CLIENT - <PLACEHOLDER> Player has unaccepted a trade..
    COMMTRADE ptype = iota // SERVER - <PLACEHOLDER> Communicate trade acceptance status to trade window..
    FINTRADE ptype = iota // SERVER - <PLACEHOLDER> Close trade window and inform player trade was accepted..
    INITCOMABT ptype = iota // SERVER - Initialize a combat session on client.
    ADDNPCCOMBAT ptype = iota // SERVER - Add an NPC to a combat session on client.
    ADDPCCOMABT ptype = iota // SERVER - Add a PC to a combat session on client.
    REMNPCCOMBAT ptype = iota // SERVER - Remove an NPC from a combat session on client.
    REMPCCOMBAT ptype = iota // SERVER - Remove a PC from a combat session on client.
    // Need to continue adding here...
    // CASTSPELL ptype = , // CLIENT - 
)

//type packet struct {
//    
//}
