#### Installing HTTPS using Let's Encrypt - Long Description:

Before anything, you need to have a public domain name pointing to the IP address associated with your server.
Then you need to have the Oldentide server up and running. See instructions above to run.
This is important, because certbot expects a webserver on port 80 to serve up static files where you specify -
i.e. ~/Oldentide/Website/public - to prove that you are in control of the domain.
All the Let's Encrypt certbot does is issue challenges and receive reponses to prove that you are
in control of the domain, and then gives you an HTTPS certificate for that domain.

These instructions assume that:
-the Oldentide webserver is currently running
(NOTE: example.com/ webroot should now be pointed to ~/Oldentide/Website/public/)
-the Oldentide directory is at ~/Oldentide.
-the Oldentide webserver is running under domain example.com on port 80
-no other webservers or services are running on port 80
-both example.com and www.example.com are pointed to your server's IP address.


## Install certbot

Go to https://certbot.eff.org/
For software, select None of the above.
For system, select your OS - e.g. Ubuntu 16.04 (xenial), Debian 8 (jesse).
Follow the instructions to install the certbot command line utility


## Create a certificate

Once certbot is installed, simply run the following command:
* sudo certbot certonly --webroot -w ~/Oldentide/Website/public -d example.com -d www.example.com
This will create a single certificate that can be used for domains https://example.com and https://www.example.com.
If you don't want the www version of the domain to be included in the cert, simply remove it from the command.
The certificates will be stored in /etc/letsencrypt/live/$domain/.
The $domain folder is just the FIRST domain listed in the command (example.com).
See https://certbot.eff.org/docs/using.html#where-are-my-certificates.
To double check that the certificates were generated properly, run this command:
* openssl x509 -text -noout -inform pem -in /etc/letsencrypt/live/example.com/cert.pem
The key thing to check here is that "X509v3 Subject Alternate Name" shows both example.com and www.example.com.


## Setup certificate auto-renewal

Let's Encrypt certs last for only 90 days, so we need to automate the renewal of the certificates in the future.
First, test to see if autorenewal works:
* certbot renew --dry-run
Edit the crontab file in order to automate renewal when certs expire:
* sudo crontab -e
Add the following line, which will do a renewal check every day at 5 am:
0 5 * * * certbot renew -q
Again, this assumes that the Oldentide webserver is running and serving static files from the same place.
(See https://help.ubuntu.com/community/CronHowto)


## Enable HTTPS

To enable HTTPS, first make a copy of config.env.example and call it config.env
Edit config.env and set the domain of the Oldentide webserver
(this should be the same as the first domain ($domain) specified in the HTTPS certificate).
Then uncomment the line #OLDENTIDE_ENABLE_HTTPS=1 to turn on the HTTPS webserver.
Save the file and restart the Oldentide webserver.
HTTPS should now be enabled and running! You are done!

Want to test HTTPS but don't want to run it on a public server right now? Read on...


## Developer notes: Local development and testing with HTTPS

Copy the /etc/letsencrypt/ folder with all your certificates to a local machine to test.
Make sure the webserver is running with HTTPS enabled, and make sure the
webserver is reading in the certificates properly.
In the browser, type https://localhost to see if the https server is working.
It should complain that the certificate is insecure because of error ERR_CERT_COMMON_NAME_INVALID.
This is because the certificate was for a domain called "example.com" and "www.example.com", not "localhost".
We need the browser to think it is connecting to example.com for it to like the certs it sees.
To do this, make example.com point to 127.0.0.1 by sudo editing the hosts file.
On Windows: C:\Windows\system32\drivers\etc\hosts in Windows 10
On Linux: /etc/hosts
Add these two lines to the hosts file:
    127.0.0.1 example.com
    127.0.0.1 www.example.com
Note that there is only a SINGLE space between them (or single tab) - it is white-space sensitive!
This is just temporary to test out HTTPS locally. Comment it out once you are done testing.
Now, when you reload example.com, it should be actually pointing to localhost!
Be sure to check that it worked by turning off the local express server and then trying to access example.com -
it should say it can't access the webpage, even if it could before editing the hosts file.
Now that example.com is pointing to localhost, the browser should see that the URL matches the domain name
in the certificate, and it will show a green lock with a valid certificate!
You can further test your site using this tool:
    https://www.ssllabs.com/ssltest/analyze.html


### Forever: Alternative way of starting the Oldentide webserver:

Globally install the forever node module:
* npm install forever -g
Then run:
* sudo forever start oldentide.js
To stop, run:
* sudo forever stopall
To see running processes (including where the logfile is), run:
* sudo forever list