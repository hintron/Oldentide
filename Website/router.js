// Filename:    router.js
// Author:      Joseph DeVictoria
// Date:        Apr_8_2017
// Purpose:     Main router for Oldentide on express.

// Web App Path Requests:
module.exports = function(app, domain, bcrypt, db, emailer) {

    // Get Handlers and Callbacks
    app.get('/', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = ?", [req.cookies.session_id], function(err, row) {
            if (row) {
                res.render('home');
            }
            else {
                res.render('home', { loggedout: true });
            }
        });
        console.log('User at ' + req.connection.remoteAddress + ' requested the Home page!');
    });

    app.get('/about', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = ?", [req.cookies.session_id], function(err, row) {
            if (row) {
                res.render('about');
            }
            else {
                res.render('about', { loggedout: true });
            }
        });
        console.log('User at ' + req.connection.remoteAddress + ' requested the About page!');
    });

    app.get('/login', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = ?", [req.cookies.session_id], function(err, row) {
            if (row) {
                res.render('login', { loggedin: true });
            }
            else {
                res.render('login', { loggedout: true });
            }
        });
        console.log('User at ' + req.connection.remoteAddress + ' requested the Login page!');
    });

    app.get('/logout', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = ?", [req.cookies.session_id], function(err, row) {
            if (row) {
                db.run("UPDATE accounts SET session = 'null' WHERE accountname = '" + row.accountname + "';");
                res.render('logout', { loggedin: true });
            }
            else {
                res.render('logout', { loggedin: false, loggedout: true });
            }
        });
        console.log('User at ' + req.connection.remoteAddress + ' requested the Logout page!');
    });

    app.get('/profile', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = ?", [req.cookies.session_id], function(err, row) {
            if (row) {
                res.render('profile', { loggedin: true, username: row.accountname });
            }
            else {
                res.render('profile', { loggedout: true });
            }
        });
        console.log('User at ' + req.connection.remoteAddress + ' requested the Profile page!');
    });

    app.get('/register', function(req, res) {
        db.get("SELECT * FROM accounts WHERE session = ?", [req.cookies.session_id], function(err, row) {
            if (row) {
                res.render('login', { loggedin: true });
            }
            else {
                res.render('register', { get: true, loggedout: true });
            }
        });
        console.log('User at ' + req.connection.remoteAddress + ' requested the Registration page!');
    });

    app.get('/register/verify/:salt', function(req, res) {
        var salt = req.params.salt;
        db.get("SELECT * FROM accounts WHERE salt = ?", [salt], function(err, row) {
            if (row) {
                db.run("UPDATE accounts SET valid = 1 WHERE salt = ?", [salt]);
                res.render('verify', { flag: true, user: row.accountname });
                console.log('User at ' + req.headers['x-forwarded-for'] + ' successfully verified the account "' + row.accountname + '"!');
            }
            else {
                res.render('verify', { flag: false, loggedout: true });
                console.log('User at ' + req.connection.remoteAddress + ' failed to verify the salt ' + salt + '!');
            }
        });
    });

    // Post handlers.
    app.post('/login', function(req, res) {
        db.get("SELECT * FROM accounts WHERE accountname = ?", [req.body.login_username], function(err, row) {
            if (row) {
                if(bcrypt.compareSync(req.body.login_password, row.key)) {
                    console.log("User " + row.accountname + " supplied the correct password for login!");
                    var sid = bcrypt.genSaltSync(1);
                    db.run("UPDATE accounts SET session = ? WHERE accountname = ?", [sid, req.body.login_username]);
                    res.cookie('session_id', sid, {maxAge : 86400000});
                    res.render('login', { loggedin: true });
                    return;
                }
                else {
                    console.log("User " + row.accountname + " supplied an incorrect password for login!");
                    res.render('login', { loggedout: true, incorrect: true });
                    return;
                }
            }
            else
            {
                console.log("User " + req.body.login_username + " not found for login...");
                //dummy hash compare to harden against timing attacks
                bcrypt.compareSync("wrongpassword", '$2a$10$8mvBexXt/N2OmVNR39kPXewnOyPG2Hc6MCrAfIjb33EZ.uhvW5lH6');
                res.render('login', { loggedout: true, incorrect: true });
            }
        });
        console.log('User at ' + req.connection.remoteAddress + ' posted data to the Login page! (Login attempt)');
    });

    app.post('/register', function(req, res) {
        req.checkBody('registration_username', "Username can only contain letters and numbers").isAlphanumeric().isLength({min:3});
        req.checkBody('registration_email', "Email needs to be an email").isEmail();
        req.checkBody('registration_password_first', "Password needs to be at least 6 characters long").isLength({min:6});
        req.checkBody('registration_password_first', "Password needs to matches confirmation password").equals(req.body.registration_password_second);
        req.sanitizeBody('registration_email').normalizeEmail();
        req.getValidationResult().then(function(result) {
            if (!result.isEmpty()) {
                res.status(400).send('There have been validation errors');
                console.log('Validation error');
                return;
            }
            var username = req.body.registration_username;
            var email = req.body.registration_email;
            var salt = bcrypt.genSaltSync(10);
            while ((salt.split('/').length - 1) > 0) {
                salt = bcrypt.genSaltSync(10);
            }
            var key = bcrypt.hashSync(req.body.registration_password_first, salt);
            var query = "INSERT INTO accounts (valid, accountname, email, session, playing, key, salt) " +
                        "VALUES (0, $username, $email, " + null + ", 0, $key, $salt)";
            db.get("SELECT * FROM accounts WHERE accountname = ? OR email = ?",[username, email], function(err, row) {
                if (row) {
                    res.render('register', { get: true, exists: true, loggedout: true });
                }
                else {
                    emailer.sendMail({
                        from: '"Oldentide Server", <' + emailer.options.auth.user + '>',
                        to: email,
                        subject: "Verify Your Oldentide Account!",
                        text: ("Hello " + username + ",\r\n\r\nPlease verify your Oldentide account by clicking the following link:\r\n" +
                                domain + "/register/verify/" + salt + " \r\n\r\nRegards,\r\nOldentide Team")
                    }, function(error, response) {
                        if (error) {
                            console.log(error);
                        }
                        else {
                            console.log("Sucessfully sent a verification email to " + email);
                        }
                    });
                    db.run(
                        query, 
                        { 
                            $username: username,
                            $email: email,
                            $key: key,
                            $salt: salt
                        });
                    res.render('register', { post: true, loggedout: true });
                }
            });
            console.log('User at ' + req.connection.remoteAddress + ' posted data to the Register page!');
        });
    });

    // Error handlers
    app.use(function(req, res) {
        res.status(404);
        res.render('404', { page: req.originalUrl, loggout: true });
        console.log('User at ' + req.connection.remoteAddress + ' generated a 404 error requesting "' + req.originalUrl + '"!');
    });

    app.use(function(error, req, res, next) {
        if (error.status == 500) {
            res.status(500);
            res.render('505', { loggedout: true });
            console.log('User at ' + req.connection.remoteAddress + ' generated a 500 error requesting "' + req.originalUrl + '"!');
        }
    });
}
