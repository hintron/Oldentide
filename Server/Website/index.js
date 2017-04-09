var express = require('express');
var http = require('http');
var fs = require('fs');

// Header security improvements
var helmet = require('helmet');


// https://github.com/mapbox/node-sqlite3
// https://github.com/mapbox/node-sqlite3/wiki/API
var sqlite3 = require('sqlite3').verbose();

// For sessions and cookies
// var session = require('express-session');
// Sets the storage mechanism for the session
// var MongoStore = require('connect-mongo')(session);
// TODO: Create a session, use sqlite
// https://www.npmjs.com/package/connect-sqlite3

// To parse JSON data
// var bodyparser = require('body-parser');









var app = express();

// Use the helmet middleware to shore up some attack vectors
// See https://expressjs.com/en/advanced/best-practice-security.html
// https://www.npmjs.com/package/helmet
app.use(helmet());




app.get('/info', function (req, res, next) {
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
