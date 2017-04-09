// Filename:    main.js
// Author:      Joseph DeVictoria
// Date:        Oct_3_2016
// Purpose:     Main router for Mutable on express.

// Web App Path Requests:
module.exports = function(app, bcrypt, db, emailer) {

    // Get Handlers and Callbacks
    app.get('/', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = '" + req.cookies.session_id + "';", function(err, row) {
            if (row) {
            }
            else {
            }
            res.render('main');
        });
        console.log('User at ' + req.headers['x-forwarded-for'] + ' requested the Home page!');
    });

    app.get('/about', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = '" + req.cookies.session_id + "';", function(err, row) {
            if (row) {
            }
            else {
                res.render('about');
            }
        });
        console.log('User at ' + req.headers['x-forwarded-for'] + ' requested the About page!');
    });

    app.get('/login', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = '" + req.cookies.session_id + "';", function(err, row) {
            if (row) {
                res.render('login', { loggedin: true });
            }
            else {
                res.render('login', { loggedout: true });
            }
        });
        console.log('User at ' + req.headers['x-forwarded-for'] + ' requested the Login page!');
    });

    app.get('/logout', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = '" + req.cookies.session_id + "';", function(err, row) {
            if (row) {
                db.run("UPDATE accounts SET session = 'null' WHERE accountname = '" + row.accountname + "';");
                res.render('logout', { loggedin: true });
            }
            else {
                res.render('logout', { loggedin: false });
            }
        });
        console.log('User at ' + req.headers['x-forwarded-for'] + ' requested the Logout page!');
    });
    
    app.get('/profile', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = '" + req.cookies.session_id + "';", function(err, row) {
            if (row) {
                res.render('profile', { loggedin: true, username: row.accountname });
            }
            else {
                res.render('profile', { loggedout: true });
            }
        });
        console.log('User at ' + req.headers['x-forwarded-for'] + ' requested the Profile page!');
    });

    app.get('/register', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = '" + req.cookies.session_id + "';", function(err, row) {
            if (row) {
                res.render('login', { loggedin: true });
            }
            else {
                res.render('register', { get: true });
            }
        });
        console.log('User at ' + req.headers['x-forwarded-for'] + ' requested the Registration page!');
    });

    app.get('/register/verify/:salt', function(req, res) {
        var salt = req.params.salt;
        db.get("SELECT * FROM accounts WHERE salt = '" + salt + "';", function(err, row) {
            if (row) {
                db.run("UPDATE accounts SET valid = 1 WHERE salt = '" + salt + "';");
                res.render('verify', { flag: true, user: row.accountname });
                console.log('User at ' + req.headers['x-forwarded-for'] + ' successfully verified the account "' + row.accountname + '"!');
            }
            else {
                res.render('verify', { flag: false });
                console.log('User at ' + req.headers['x-forwarded-for'] + ' failed to verify the salt ' + salt + '!');
            }
        });
    });

    // Post handlers.
    app.post('/login', function(req, res) {
        db.get("SELECT * FROM accounts WHERE accountname = '" + req.body.login_username + "';", function(err, row) {
            if (row) {
                var key = bcrypt.hashSync(req.body.login_password, row.salt);
                if (key == row.key) {
                    console.log("User " + row.accountname + " supplied the correct password for login!");
                    var sid = bcrypt.genSaltSync(1);
                    db.run("UPDATE accounts SET session = '" + sid + "' WHERE accountname = '" + req.body.login_username +"';")
                    res.cookie('session_id', sid, {maxAge : 86400000});
                    res.render('login', { loggedin: true });
                }
                else {
                    console.log("User " + row.accountname + " supplied an incorrect password for login!");
                    res.render('login', { loggedout: true, incorrect: true });
                }
            }
            else {
                console.log("User " + req.body.login_username + " not found for login...");
                res.render('login', { loggedout: true, incorrect: true });
            }
        });
        console.log('User at ' + req.headers['x-forwarded-for'] + ' posted data to the Login page! (Login attempt)');
    });

    app.post('/register', function(req, res) {
        var username = req.body.registration_username;
        var email = req.body.registration_email;
        var salt = bcrypt.genSaltSync(10);
        while ((salt.split('/').length - 1) > 0) {
            salt = bcrypt.genSaltSync(10);
        }
        var session = null;
        console.log(salt);
        var key = bcrypt.hashSync(req.body.registration_password_first, salt);
        var query = "INSERT INTO accounts (valid, accountname, email, session, key, salt) " +
                    "VALUES (0, '" + username + "', '" + email + "', " + session + ", '" + key + "', '" + salt + "');";
        db.get("SELECT * FROM accounts WHERE accountname = '" + username + "' OR email = '"  + email + "';", function(err, row) {
            if (row) {
                res.render('register', { get: true, exists: true });
            }    
            else {
                emailer.sendMail({
                    from: '"Oldentide Server", <oldentide@gmail.com>',
                    to: email,
                    subject: "Verify Your Oldentide Account!",
                    text: ("Hello " + username + ",\r\n\r\nPlease verify your Oldentide account by clicking the following link:\r\n" +
                          "https://login.oldentide.com/register/verify/" + salt + " \r\n\r\nRegards,\r\nMutable Team")
                }, function(error, response) {
                    if (error) {
                        console.log(error);
                    }
                    else {
                        console.log("Sucessfully sent a verification email to " + email);
                    }
                });
                db.run(query);
                res.render('register', { post: true });
            }
        }); 
        console.log('User at ' + req.headers['x-forwarded-for'] + ' posted data to the Register page!');
    });
    
    // Errorr handlers
    app.use(function(req, res) {
        res.status(404);
        res.render('404', {page: req.originalUrl});
        console.log('User at ' + req.headers['x-forwarded-for'] + ' generated a 404 error requesting "' + req.originalUrl + '"!');
    });

    app.use(function(error, req, res, next) {
        if (error.status == 500) {
            res.status(500);
            res.render('505');
            console.log('User at ' + req.headers['x-forwarded-for'] + ' generated a 500 error requesting "' + req.originalUrl + '"!');
        }
    });
}
