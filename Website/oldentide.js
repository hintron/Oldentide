// Filename:    oldentide.js
// Author:      Joseph DeVictoria
// Date:        Apr_8_2016
// Purpose:     Main Express file for Oldentide Account registration and login.
// Includes:
var bcrypt          = require('bcrypt');
var bodyParser      = require('body-parser');
var cookieParser    = require('cookie-parser');
var express         = require('express');
var handlebars      = require('express-handlebars');
var http            = require('http');
var mailer          = require('nodemailer');
var path            = require('path');
var sqlite3         = require('sqlite3').verbose();

// Application Setup:
var app = express();
app.set('port', 80);
// Set handlebars as our template engine.
app.engine('handlebars', handlebars());
app.set('views', __dirname + '/views');
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

// Launch App Listening on Public Port 80.
var server = app.listen(app.get('port'), function() {
    console.log('Listening on port ' + app.get('port') + '...');
});

var emailer = mailer.createTransport({
    service: 'gmail',
    auth: {
        user: 'oldentide@gmail.com',
        pass: 'PhoenixL1ves'
    }
});

// Set up external router file.
require('./router')(app, bcrypt, db, emailer);
