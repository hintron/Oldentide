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
* npm install       # may need sudo

Run:

* sudo npm start
or
* ./run.sh

####Installing and enabling HTTPS

Install certbot from https://certbot.eff.org/
Make sure Oldentide webserver is running.
* sudo certbot certonly --webroot -w ~/Oldentide/Website/public -d example.com -d www.example.com
Edit the crontab file to automate cert renewal:
* sudo crontab -e
Add the following line, which will do a renewal check every day at 5 am:
0 5 * * * certbot renew -q
Make a copy of config.env.example and rename it config.env
In config.env,
-uncomment #OLDENTIDE_ENABLE_HTTPS=1
-uncomment and set #OLDENTIDE_DOMAIN=yourdomain.com
Save the file and restart the Oldentide server. HTTPS should now be enabled.