// Filename:    oldentide.js
// Author:      Joseph DeVictoria
// Date:        Apr_8_2016
// Purpose:     Main Express file for Oldentide Account registration and login.
// Includes:
var bcrypt          = require('bcryptjs');
var bodyParser      = require('body-parser');
var cookieParser    = require('cookie-parser');
var express         = require('express');
var handlebars      = require('express-handlebars');
var http            = require('http');
var https           = require('https');
var mailer          = require('nodemailer');
var path            = require('path');
var sqlite3         = require('sqlite3').verbose();
var fs              = require('fs');
var dotenv          = require('dotenv');
var helmet          = require('helmet');


dotenv.config({path: './config.env'});
const ENABLE_HTTPS = process.env.OLDENTIDE_ENABLE_HTTPS;
const DOMAIN_NAME = process.env.OLDENTIDE_DOMAIN;
const EMAIL_SERVICE = process.env.OLDENTIDE_EMAIL_SERVICE;
const EMAIL_USER = process.env.OLDENTIDE_EMAIL_USER;
const EMAIL_PASSWORD = process.env.OLDENTIDE_EMAIL_PASSWORD;
const HTTP_PORT = 80;
const HTTPS_PORT = 443;

var domain;
if(DOMAIN_NAME){
    if(ENABLE_HTTPS){
        console.log("HTTPS enabled");
        domain = "https://" + DOMAIN_NAME;
    }
    else {
        domain = "http://" + DOMAIN_NAME;
    }
}
else {
    domain = "localhost";
}
console.log("Webserver running on domain \"" + domain + "\"");

// Application Setup:
var app = express();
// Use the helmet middleware to shore up sundry attack vectors
app.use(helmet());
// Set handlebars as our template engine.
app.engine('handlebars', handlebars({defaultLayout: 'main'}));
app.set('views', __dirname + '/views');
app.set('layouts', __dirname + '/views/layouts');
app.set('view engine', 'handlebars');
// Set the public folder as static and viewable by anyone.
app.use(express.static('public'));
// Enable Body-parser for all requests.
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
// Enable Cookie-parser for all requests.
app.use(cookieParser());

// Open database:
var db = new sqlite3.Database('../Server/db/Oldentide.db', function() {
    console.log('Successfully opened Oldentide.db!');
});


var emailer;
if(EMAIL_SERVICE && EMAIL_USER && EMAIL_PASSWORD){
    emailer = mailer.createTransport({
        service: EMAIL_SERVICE,
        auth: {
            user: EMAIL_USER,
            pass: EMAIL_PASSWORD,
        }
    });
}


// Set up external router file.
require('./router')(app, domain, bcrypt, db, emailer);

// Set up HTTP and HTTPS
if(ENABLE_HTTPS){
    // See http://stackoverflow.com/questions/11804202/how-do-i-setup-a-ssl-certs-for-an-express-js-server
    // See http://stackoverflow.com/questions/11744975/enabling-https-on-express-js
    // See https://community.letsencrypt.org/t/android-doesnt-trust-the-certificate/16498/16
    // See http://stackoverflow.com/questions/19104215/node-js-express-js-chain-certificate-not-working

    // Get the HTTPS certificate
    var cert_base_path = "/etc/letsencrypt/live/" + DOMAIN_NAME + "/"
    var privkey_path = cert_base_path + "privkey.pem";
    var cert_path = cert_base_path + "cert.pem";
    var chain_path = cert_base_path + "chain.pem";

    var privateKey  = fs.readFileSync(privkey_path, 'utf8');
    var certificate = fs.readFileSync(cert_path, 'utf8');
    var chain_cert = fs.readFileSync(chain_path, 'utf8');

    var credentials = {
        key: privateKey,
        cert: certificate,
        ca: chain_cert,
    };

    // Create the https server
    https.createServer(credentials, app).listen(HTTPS_PORT, function(){
        console.log('Listening on port ' + HTTPS_PORT + '...');
    });

    // Set up an http server and redirect all http requests to https by default
    var app_http = express();
    app_http.get('*', function (req, res) {
        console.log("redirecting http to https! " + req.headers['host'] + req.url);
        if(HTTPS_PORT != 443){
            // Redirect to non-standard, custom HTTPS port
            //console.log("redirecting port " + HTTP_PORT + " to " + HTTPS_PORT);
            res.redirect('https://' + (req.headers['host'].slice(0, -HTTP_PORT.toString().length)) + HTTPS_PORT + req.url);
        }
        else {
            res.redirect('https://' + req.headers['host'] + req.url);
        }
    });
    http.createServer(app_http).listen(HTTP_PORT, function() {
        console.log('Listening on port ' + HTTP_PORT + '...');
    });

}
else {
    // HTTP only
    var server = app.listen(HTTP_PORT, function() {
        console.log('Listening on port ' + HTTP_PORT + '...');
    });
}
