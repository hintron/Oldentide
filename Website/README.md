# Oldentide

#####Web Server for Account Registration and Login.

==================================

###Project Information:

**Project name**: Oldentide Website<br>
**Initial Starting Date**: 4/8/2017<br>
**Principal Authors**: Joseph DeVictoria<br>
**Platform**: Node.js running Express, Handlebars, and sqlite3<br>
**Languages**: JavaScript, Handlebars, HTML, CSS, and SQLite3<br>
**Project Website**: http://*.oldentide.com<br>
**Contact**: jldevictoria@gmail.com

==================================

###Directories:

**public**:             Public files such as images, icons and style sheets.<br>
**views**:              Location for Express.js views (rendered via handlebars).<br>

==================================

###How To Install and Run:

Install:

* curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
* sudo apt-get install -y nodejs
* sudo ln -s /usr/bin/nodejs /usr/bin/node
* sudo apt-get install npm
* npm install

Run:

* sudo npm start
or
* ./run.sh
or
you can globally install the forever node module:
* npm install forever -g
Then run:
* forever start oldentide.js
To stop, run:
* forever stopall
To see running processes with forever, run:
*forever list



####Installing HTTPS using Let's Encrypt:

First, you need to have your website publicly up and running.
All Let's Encrypt does is prove that you are in control of a domain, and then gives you a certificate.
The following assumes:
-that the non-HTTPS version of the Oldentide webserver is currently running
-that the Oldentide directory is at ~/Oldentide.
-that the Oldentide webserver is running on domain example.com (i.e. the example.com/ webroot is ~/Oldentide/Website/public/)

##Install certbot

Go to https://certbot.eff.org/
For software, select None of the above.
For system, select your OS - e.g. Ubuntu 16.04 (xenial), Debian 8 (jesse).
Follow the instructions to install the certbot command line utility

##Create a certificate

Run the following certbot command:
* sudo certbot certonly --webroot -w ~/Oldentide/Website/public -d example.com -d www.example.com
This will create a single certificate that can be used for https://example.com and https://www.example.com.
The certificates are stored at /etc/letsencrypt/live/$domain.
$domain is the first domain listed in the command.
See https://certbot.eff.org/docs/using.html#where-are-my-certificates.
To double check that the certificates look ok, run this command:
* openssl x509 -text -noout -inform pem -in /etc/letsencrypt/live/example.com/cert.pem
The key thing to check here is that "X509v3 Subject Alternate Name" shows both example.com and www.example.com.

##Setup certificate auto-renewal

Let's Encrypt certs last for only 90 days, so run certbot renew [--dry-run] to renew the certs.
Add it to crontab to automate it and renew certs when they expire (while logged into root):
* crontab -e
Then edit the file to include the following line, which will do a renewal check every day at 5 am:
0 5 * * * certbot renew -q
(See https://help.ubuntu.com/community/CronHowto)


## Local development

Copy the /etc/letsencrypt/ folder to a local machine to test.
Make oldentide.js create an https server that listens on port 443 (the default HTTPS port)
Read in the copied cert files.
See http://stackoverflow.com/questions/11804202/how-do-i-setup-a-ssl-certs-for-an-express-js-server
See http://stackoverflow.com/questions/11744975/enabling-https-on-express-js
In the browser, type https://localhost to see if the https server is working.
It should complain that the certificate is insecure because of error ERR_CERT_COMMON_NAME_INVALID.
This is because the certificate was for a domain called example.com and www.example.com, not localhost.
To test out these certs on a local machine, make sure example.com is used locally in the browser url instead of localhost.
So I need to edit the hosts file (C:\Windows\system32\drivers\etc\hosts in Windows 10 or /etc/hosts or /etc/cloud/templates/hosts.debian.tmpl in Debian)
Edit it in notepad++ on Windows to get past permissions automatically.
Add these two lines:
    127.0.0.1 example.com
    127.0.0.1 www.example.com
Note that there is only a SINGLE space between them (or single tab) - it is white-space sensitive!
This is just temporary to test out HTTPS locally! Comment it out once done.
Be sure to check that it worked by turning off the local express server and then try to access example.com - it should say it can't access, even if it was before editing the hosts file.
Now that example.com is pointing to localhost, the browser should see that it matches the certificate, and it will show a green lock with a valid certificate!


TODO: Implement this automatically in oldentide.js

To redirect users to automatically connect via HTTPS when they just type in "example.com," follow instructions here:
http://stackoverflow.com/questions/7450940/automatic-https-connection-redirect-with-node-js-express
To redirect all HTTP requests to HTTPS, add this code:
    const DOMAIN = "example.com"
    var app_http = express();
    app_http.get('*', function (req, res) {
        res.redirect('https://' + DOMAIN + req.url);
    });
    // redirect http request to https
    http.createServer(app_http).listen(80);

Test to make sure "example.com" redirects to "https://example.com."

To make sure that Android Chrome accepts the certification, you also need to pass in chain.pem file into the "ca" HTTPS server config.
See https://community.letsencrypt.org/t/android-doesnt-trust-the-certificate/16498/16
See http://stackoverflow.com/questions/19104215/node-js-express-js-chain-certificate-not-working
NOTE: Even after the chain.pem is passed to the ca option and the server restarts,
Chrome on Android may still show a red lock and "your connection isn't private" messages!
You might need to close the original tab and re-open it in a new tab for it to show properly.

You can test the site using this tool:
    https://www.ssllabs.com/ssltest/analyze.html

