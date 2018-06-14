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
    "net/http"
    "os"
    "runtime"
    "strconv"
)

func main() {
    fmt.Println("Starting Oldentide dedicated server!")

    // Opening database.
    db, err := sql.Open("sqlite3", "../../db/Oldentide.db")
    checkErr(err)

    // Kick off html server for registration page.
    mux := http.NewServeMux()
    mux.HandleFunc("/", homePage)
    mux.HandleFunc("/register", registerPage)
    go http.ListenAndServe(":8080", mux)

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


// HTTP Handlers:
func homePage(w http.ResponseWriter, r *http.Request) {
    hn, err := os.Hostname()
    checkErr(err)
    fmt.Fprintf(w, "<html>")
    fmt.Fprintf(w, "<p>Welcome to the Oldentide dedicated server running on %s.</p>", hn)
    fmt.Fprintf(w, "<p>Account Registration:</p>")
    fmt.Fprintf(w, "<form name=\"registration\" method=\"post\" action=\"/register\" role=\"form\">")
    fmt.Fprintf(w, "<label for=\"registration_username\">Username (min 3)</label><br>")
    fmt.Fprintf(w, "<input type=\"text\" id=\"registration_username\" name=\"registration_username\" " +
                   "placeholder=\"User\" required=\"required\" maxlength=\"30\" pattern=\"[A-Za-z0-9]{3,}\"><br>")
    fmt.Fprintf(w, "<label for=\"registration_email\">Email</label><br>")
    fmt.Fprintf(w, "<input type=\"email\" id=\"registration_email\" name=\"registration_email\" " +
                   "placeholder=\"user@domain.com\" required=\"required\"><br>")
    fmt.Fprintf(w, "<label for=\"registration_password_first\">Password (min 6)</label><br>")
    fmt.Fprintf(w, "<input type=\"password\" id=\"registration_password_first\" name=\"registration_password_first\" " +
                   "placeholder=\"******\" required=\"required\" maxlength=\"30\" pattern=\".{6,}\"><br>")
    fmt.Fprintf(w, "<label for=\"registration_password_second\">Confirm (min 6)</label><br>")
    fmt.Fprintf(w, "<input type=\"password\" id=\"registration_password_second\" name=\"registration_password_second\" " +
                   "placeholder=\"******\" required=\"required\" maxlength=\"30\" pattern=\".{6,}\" oninput=\"check(this)\"><br><br>")
    fmt.Fprintf(w, "<script language='javascript' type='text/javascript'> function check(input) { " +
                   "    if (input.value != document.getElementById('registration_password_first').value) " +
                   "        { input.setCustomValidity('Password Must be Matching.'); " +
                   "    } else { input.setCustomValidity(''); }	} </script>")
    fmt.Fprintf(w, "<input class=\"button-primary\" type=\"submit\" value=\"Register\">")
    fmt.Fprintf(w, "</form>")
    fmt.Fprintf(w, "</html>")
}

func registerPage(w http.ResponseWriter, r *http.Request) {
    if r.Method == "POST" {
        r.ParseForm()
        registration_username := r.Form["registration_username"][0]
        registration_email := r.Form["registration_email"][0]
        registration_password_first := r.Form["registration_password_first"][0]
        registration_password_second := r.Form["registration_password_second"][0]
        if registration_password_first == registration_password_second {
            fmt.Fprintf(w, "You posted data to the register page.\n\n")
            fmt.Fprintf(w, "Username: %s\n", registration_username)
            fmt.Fprintf(w, "Email: %s\n", registration_email)
        } else {
            fmt.Fprintf(w, "Your passwords did not match...")
        }
	} else {
		http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
	}
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
