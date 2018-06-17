// Filename:    sql_connector.go
// Author:      Joseph DeVictoria
// Date:        June_16_2018
// Purpose:     Definition of packets to be used in Oldentide.

package main

import (
    "fmt"
    _ "github.com/mattn/go-sqlite3"
    "net/http"
    "net/smtp"
    "os"
    "regexp"
)

var homereg = regexp.MustCompile("^/$")
var regireg = regexp.MustCompile("/register")
var verireg = regexp.MustCompile("/verify/[a-z,A-Z]{20}")

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
            fmt.Fprintf(w, "An account with the username " + registration_username +
                           " already exists.\n\nPlease go back and choose another.")
        } else if emailExists(registration_email) {
            fmt.Fprintf(w, "An account is already associated with the email " +
                           registration_email + "\n\nPlease use a unique email.")
        } else if registration_password_first == registration_password_second {
            // Generate a unique random verification key.
            //findKey := true

            verify_key := generateUniqueVerify(20)
            salt_key := generateUniqueSalt(40)
            fmt.Println(verify_key)
            fmt.Println(salt_key)
            hashed_key := saltAndHash(registration_password_first, salt_key)

            // Create email message to send to user.
            msg := []byte("Hello " + registration_username +
                          "\n\nPlease verify your Oldentide account by clicking the following link: " +
                          "http://" + webaddress + ":8080" + "/verify/" + verify_key +
                          " \n\nRegards,\nOldentide Server Admin")
            to := []string { registration_email }

            // Store user account information in the database!
            createAccount(registration_username, registration_email, verify_key, hashed_key, salt_key)

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
    accountname := getAccountnameFromVerifyKey(verify_key)
    if accountname == "" {
        fmt.Fprintf(w, "No account found for verify key " + verify_key + ".")
    } else {
        if activateAccount(accountname) {
            fmt.Fprintf(w, "Successfully verified account " + accountname + ".")
        } else {
            fmt.Println(w, "Found account " + accountname + " but couldn't activate for some reason.")
        }
    }
}
