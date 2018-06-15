// Filename:    dedicated_server.go
// Author:      Joseph DeVictoria
// Date:        June_15_2018
// Purpose:     The dedicated game server for Oldentide written in Go.

package main

import (
    "crypto/sha256"
    "database/sql"
    "encoding/base64"
    "flag"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
    "log"
    "math/rand"
    "net"
    "net/http"
    "net/smtp"
    "os"
    "regexp"
    "runtime"
)

// Global program variables.
var err error
var port int
var everify bool
var webaddress string
var email string
var epass string
var eauth smtp.Auth
var db *sql.DB
var homereg = regexp.MustCompile("^/$")
var regireg = regexp.MustCompile("/register")
var verireg = regexp.MustCompile("/verify/[a-z,A-Z]{20}")

func init() {
    flag.IntVar(&port, "port", 0, "Port used for dedicated game server.")
    flag.BoolVar(&everify, "everify", false, "Use an emailer to verify accounts?")
    flag.StringVar(&webaddress, "webaddress", "", "Public website root address where accounts will be created.")
    flag.StringVar(&email, "email", "", "Gmail email address used to send verification emails.")
    flag.StringVar(&epass, "epass", "", "Gmail email password used to send verification emails.")
}

func main() {
    // Extract command line input.
    flag.Parse()
    fmt.Println("Server Configurations from command line:")
    fmt.Println("port:", port)
    fmt.Println("everify:", everify)
    fmt.Println("webaddress:", webaddress)
    fmt.Println("email:", email)
    fmt.Println("epass:", epass)

    if port == 0 {
        log.Fatal("Please provide a port with the command line flag -port=<number>")
    }
    if everify {
        if webaddress == "" {
            log.Fatal("Please provide the website address with the command line flag -webaddress=<www.address.domain>")
        }
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
    db, err = sql.Open("sqlite3", "../../db/Oldentide.db")
    checkErr(err)

    // Kick off html server for registration page.
    mux := http.NewServeMux()
    mux.HandleFunc("/", routeWebTraffic)
    go http.ListenAndServe(":8080", mux)

    // Create udp socket description struct.
    server_address := net.UDPAddr {
        IP: net.IP {0, 0, 0, 0},
        Port: port,
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

// Router for web traffic.
func routeWebTraffic(w http.ResponseWriter, r *http.Request) {
    switch {
    case homereg.MatchString(r.URL.Path):
        homePage(w, r)
    case regireg.MatchString(r.URL.Path):
        registerPage(w, r)
    case verireg.MatchString(r.URL.Path):
        verifyPage(w, r)
    default:
        fmt.Fprintf(w, "Unknown Path.")
    }
}

// Web handler that loads the home page.
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

// Web handler that uses the results of the registration POST to initiate a new player account registration.
func registerPage(w http.ResponseWriter, r *http.Request) {
    if r.Method == "POST" {
        r.ParseForm()
        registration_username := r.Form["registration_username"][0]
        registration_email := r.Form["registration_email"][0]
        registration_password_first := r.Form["registration_password_first"][0]
        registration_password_second := r.Form["registration_password_second"][0]
        if accountExists(registration_username) {
            fmt.Fprintf(w, "An account with this username already exists.\n\nPlease go back and choose another.")
        } else if emailExists(registration_email) {
            fmt.Fprintf(w, "An account is already associated with this email.\n\nPlease use a unique email.")
        } else if registration_password_first == registration_password_second {
            // Generate a unique random verification key.
            //findKey := true

            verify_key := generateUniqueVerify(20)
            salt_key := generateUniqueSalt(40)
            hashed_key := saltAndHash(registration_password_first, salt_key)

            // Create email message to send to user.
            msg := []byte("Hello " + registration_username +
                          "\n\nPlease verify your Oldentide account by clicking the following link: " +
                          "http://" + webaddress + ":8080" + "/verify/" + verify_key +
                          " \n\nRegards,\nOldentide Server Admin")
            to := []string { registration_email }

            // Store user account information in the database!
            // Prepare insert statement.

            insert, err := db.Prepare("INSERT INTO accounts(valid, accountname, email, gamesession, playing, verify, hash, salt) values(?, ?, ?, ?, ?, ?, ?, ?)")
            checkErr(err)

            // Try to populate and execute an SQL statment.
            _, err = insert.Exec("0", registration_username, registration_email, "0", "0", verify_key, hashed_key, salt_key)
            checkErr(err)

            // Send registration email using 
            err = smtp.SendMail("smtp.gmail.com:587", eauth, email, to, msg)
            checkErr(err)
            fmt.Fprintf(w, "<html>You posted data to the register page.<br><br>")
            fmt.Fprintf(w, "An email has been sent to verify this information:<br><br>")
            fmt.Fprintf(w, "Username: %s<br>", registration_username)
            fmt.Fprintf(w, "Email: %s<br><br>", registration_email)
            fmt.Fprintf(w, "<b>It may take up to 5 minutes for this email to arrive.</b></html>")
        } else {
            fmt.Fprintf(w, "Your passwords did not match...")
        }
	} else {
		http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
	}
}

// Web handler that uses the url key to validate email for an account.
func verifyPage(w http.ResponseWriter, r *http.Request) {
    verify_key := r.URL.Path[8:]
    var accountname string = ""
    rows, err := db.Query("SELECT accountname FROM accounts WHERE verify=\"" + verify_key + "\"")
    if err == nil {
        for rows.Next() {
            rows.Scan(&accountname)
            rows.Close()
            update, err := db.Prepare("UPDATE accounts SET valid=? WHERE accountname=?")
            checkErr(err)
            _, err = update.Exec("1", accountname)
            if err == nil {
                fmt.Fprintf(w, "Successfully verified account " + accountname + ".")
            } else {
                fmt.Println(err)
            }
        }
    } else {
        fmt.Println(err)
    }
}

// Function that takes in a password and salt and hashes them together into a db safe key.
func saltAndHash(password string, salt string) string {
    hasher := sha256.New()
    saltpass := password + salt
    hasher.Write([]byte(saltpass))
    hash := base64.URLEncoding.EncodeToString(hasher.Sum(nil))
    return hash
}

// Check if the account name is already taken in the database.
func accountExists(a string) bool {
    _, err := db.Query("SELECT * FROM accounts WHERE accountname=" + a)
    if err == nil {
        return false
    } else {
        return true
    }
}

// Check if this email already has an account associated with it in the database.
func emailExists(e string) bool {
    _, err := db.Query("SELECT * FROM accounts WHERE email=" + e)
    if err == nil {
        return false
    } else {
        return true
    }
}

// Queries the db to make sure that we are generating a truly unique verify key.
func generateUniqueVerify(n int) string {
    findKey := true
    for findKey {
        verify_key := generateRandomLetters(n)
        _, err := db.Query("SELECT accountname FROM accounts WHERE verify=" + verify_key)
        if err != nil {
            return verify_key
        }
    }
    return ""
}

// Queries the db to make sure that we are generating a truly unique salt.
func generateUniqueSalt(n int) string {
    findKey := true
    for findKey {
        salt_key := generateRandomLetters(n)
        _, err := db.Query("SELECT accountname FROM accounts WHERE salt=" + salt_key)
        if err != nil {
            return salt_key
        }
    }
    return ""
}

// Util used to generate a string of lower and upper case letters.
func generateRandomLetters(n int) string {
    var letters = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
    key := make([]rune, n)
    for i := range key {
        key[i] = letters[rand.Intn(len(letters))]
    }
    return string(key)
}

// Util used to generate a string of lowe and upper case letters and numbers.
func generateRandomAlnums(n int) string {
    var alnums = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
    key := make([]rune, n)
    for i := range key {
        key[i] = alnums[rand.Intn(len(alnums))]
    }
    return string(key)
}
