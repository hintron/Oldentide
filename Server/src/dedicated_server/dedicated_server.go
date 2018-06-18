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

    // Opening database.
    db, err = sql.Open("sqlite3", "../../../Server/db/Oldentide.db")
    checkErr(err)

    // Kick off http server for registration page.
    mux := http.NewServeMux()
    mux.HandleFunc("/", routeWebTraffic)
    go http.ListenAndServe(":" + strconv.Itoa(wport), mux)

    // Create udp socket description struct.
    server_address := net.UDPAddr {
        IP: net.IP {0, 0, 0, 0},
        Port: gport,
    }

    // Bind a udp socket.
    socket, err := net.ListenUDP("udp", &server_address)
    checkErr(err)

    // Create go channel for listeners go routines communication.
    quit := make(chan struct{})

    // Start as many listener go routines as we have processors.
    // Should result in non-thrashing listener thread concurrency.
    for i := 0; i < runtime.NumCPU(); i++ {
        go listen(socket, quit)
    }
    <-quit

    // Close database.
    db.Close()
}

// Concurrent listener function:
func listen(connection *net.UDPConn, quit chan struct{}) {
    buffer := make([]byte, 65507) // Max IPv4 UDP packet size.
    n, remote_address, err := 0, new(net.UDPAddr), error(nil)
    for err == nil {
        n, remote_address, err = connection.ReadFromUDP(buffer)
        fmt.Println("From:", remote_address, buffer[:n])
    }
    fmt.Println("Listener failed - ", err)
    quit <- struct{}{}
}
