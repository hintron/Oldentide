// Filename:    server.go
// Author:      Joseph DeVictoria
// Date:        June_15_2018
// Purpose:     Game Server for Oldentide written in Go lang.

package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
    "log"
    "net"
    "os"
    "runtime"
    "strconv"
)

func main() {
    fmt.Println("Starting Oldentide Go Server!!!")

    // Opening database.
    db, err := sql.Open("sqlite3", "../../db/Oldentide.db")
    checkErr(err)

    // Extract port from command line.
    server_port, err := strconv.Atoi(os.Args[1])
    checkErr(err)

    // Create udp socket description struct.
    server_address := net.UDPAddr {
        IP: net.IP {0, 0, 0, 0},
        Port: server_port,
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

// Simple function to check the error status of an operation.
func checkErr(err error) {
    if err != nil {
        log.Fatal(err)
    }
}

// Concurrent listener function:
//     Wait for a packet to arrive.
//     if no error, print contents.
//     repeat. (6 parallel go routines)
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

/*
// Create an insert statement tool.
insert, err := db.Prepare("INSERT INTO accounts(valid, accountname, email, session, playing, key, salt) values(?, ?, ?, ?, ?, ?, ?)")
checkErr(err)

// Try to populate and execute an SQL statment.
_, err = insert.Exec(0, "Joseph", "jldevictoria@gmail.com", 0, 0, "test", "123")
fmt.Println(err)
//checkErr(err)

// Lets try to extract an entry from the database.
rows, err := db.Query("SELECT * FROM accounts")
checkErr(err)

var uid int
var valid int
var accountname string
var email string
var session int
var playing int
var key string
var salt string

for rows.Next() {
    err = rows.Scan(&uid, &valid, &accountname, &email, &session, &playing, &key, &salt)
    checkErr(err)
    fmt.Println(uid, valid, accountname, email, session, playing, key, salt)
}

rows.Close() //good habit to close
*/
