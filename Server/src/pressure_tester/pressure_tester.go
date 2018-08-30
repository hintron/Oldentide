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

type TestPacket struct {
    Payload string
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
    server_connection, err := net.Dial("udp", sadd + ":" + strconv.Itoa(sport))
    checkErr(err)

    for i := 0; i < 100; i++ {
        // Build a test packet.
        p, err := msgpack.Marshal(&TestPacket{Payload: "This is a test ---- " + strconv.Itoa(i)})
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
