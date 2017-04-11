# Oldentide

##### Web Server for Account Registration and Login.

==================================

### Project Information:

**Project name**: Oldentide Website<br>
**Initial Starting Date**: 4/8/2017<br>
**Principal Authors**: Joseph DeVictoria<br>
**Platform**: Node.js running Express, Handlebars, and sqlite3<br>
**Languages**: JavaScript, Handlebars, HTML, CSS, and SQLite3<br>
**Project Website**: http://*.oldentide.com<br>
**Contact**: jldevictoria@gmail.com

==================================

### Directories:

**public**:             Public files such as images, icons and style sheets.<br>
**views**:              Location for Express.js views (rendered via handlebars).<br>

==================================

### How To Install and Run:

Install:

* curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
* sudo apt-get install -y nodejs
* sudo ln -s /usr/bin/nodejs /usr/bin/node
* sudo apt-get install npm
* sudo npm install

Run:

* sudo npm start
or
* ./run.sh

==================================

#### Installing and enabling HTTPS

Install certbot from https://certbot.eff.org/:

* sudo add-apt-repository ppa:certbot/certbot
* sudo apt-get update
* sudo apt-get install certbot

Generate certbot certificate:

* sudo npm start &
* sudo certbot certonly --webroot -w ~/Oldentide/Website/public -d example.com -d www.example.com
* ( sudo crontab -l; echo "0 5 * * * certbot renew -q" ) | sudo crontab -
* cp config.env.example config.env.
* Edit config.env and make the following changes:
1. Uncomment #OLDENTIDE_ENABLE_HTTPS=1
2. Uncomment and set #OLDENTIDE_DOMAIN=yourdomain.com

Restart the Oldentide server and HTTPS should now be enabled.
