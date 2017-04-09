var express = require('express');
var http = require('http');

// Header security improvements
var helmet = require('helmet');


// https://github.com/mapbox/node-sqlite3
// https://github.com/mapbox/node-sqlite3/wiki/API
var sqlite3 = require('sqlite3').verbose();

// For sessions and cookies
var session = require('express-session');
// Sets the storage mechanism for the session
// https://www.npmjs.com/package/connect-sqlite3
var SQLiteStore = require('connect-sqlite3')(session);

// To parse JSON data
// var bodyparser = require('body-parser');

// Set the session to expire after 12 hours
const SESSION_EXPIRE_TIME = 12*60*60*1000;


var app = express();

// Use the helmet middleware to shore up some attack vectors
// See https://expressjs.com/en/advanced/best-practice-security.html
// https://www.npmjs.com/package/helmet
app.use(helmet());

// Boot up the session
app.use(session({
    // TODO: Pull this from an environmental variable so secrets aren't open source
    secret: 'thisismylittlesecret',
    name: "Oldentide",
    resave: false,
    // Don't save new sessions until they are modified (authenticated)
    saveUninitialized: false,
    cookie: {
        // secure: true, // Only send cookie if HTTPS
        httpOnly: true, // Do not let client browser js to access cookie (only http request)
        maxAge: SESSION_EXPIRE_TIME,
    },
    store: new SQLiteStore,
}));






app.get('/auth', function (req, res, next) {

    var sess = req.session;

    // Skip admin check if already authenticated
    if(sess.authenticated){
        res.send(JSON.stringify({
            success: true,
            already_authenticated: true,
            msg:'already authenticated...',
        }));
        return;
    }

    // TODO: Check user password to see if admin

    // TODO: Grab user credentials (should already be salted and stretched by the client by now)
    // TODO: Use bcrypt?

    // TODO: Compare passed key with key and salt on record


    // If admin, set them as admin
    sess.authenticated = true;
    res.send(JSON.stringify({
        success: true,
        msg:'You have now been bestowed admin powers',
    }));
});

app.get('/accounts', function (req, res, next) {

    // Check to make sure person is an admin
    var sess = req.session;
    if(!sess.authenticated){
        // console.log("Already authenticated...");
        res.send(JSON.stringify({
            success: false,
            msg:'You are not an admin!',
        }));
        return;
    }

    // TODO: Move this outside somewhere, so only happens once?
    var db = new sqlite3.Database('../db/Oldentide.db');

    db.serialize(function() {
        // db.run("CREATE TABLE lorem (info TEXT)");
        // var stmt = db.prepare("SELECT * FROM accounts");
        // for (var i = 0; i < 10; i++) {
        //     stmt.run("Ipsum " + i);
        // }
        // stmt.finalize();

        db.all("SELECT id, accountname, salt FROM accounts", function(err, rows) {
            // console.log(rows);
            res.send(JSON.stringify({
                success: true,
                msg:'Info',
                data: rows,
            }));
        });
    });

    db.close();
});

// Logout action for both bosses and users
app.get('/logout', function (req, res, next) {
    req.session.destroy();
    // Show the logged-out page
    res.status(200).sendFile(__dirname + '/public/logged_out.html');
});










// Serve public content - set it as the website root
app.use(express.static('public', {}));

// See https://expressjs.com/en/starter/faq.html
// static simply calls next() when it hits 404, so if nothing catches it, it is not found
app.use(function (req, res, next) {
    res.status(404).sendFile(__dirname + "/public/404.html");
    // Use the following erroneous code to temporarily test 500 errors
    // res.status(404).sendFile("./public/404.htffffff");
});

// Test this by trying to do sendFile with a bad path
// NOTE: If you don't handle this, it defaults to spitting out error info to the client, which can be bad!
app.use(function (err, req, res, next) {
    console.error(err.stack);
    res.status(500).sendFile(__dirname + "/public/500.html");
});

http.createServer(app).listen(80);
