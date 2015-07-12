#!/usr/bin/python
#Dedicated server for Oldentide.
#Joseph DeVictoria - 2014

# -- External Modules --
import socket
import select
import signal
import MySQLdb
import getpass
import hashlib
import time
import sys
import asyncore
import string

# -- Oldentide Modules --
import character

def main():
    print 'Starting Oldentide Dedicated Server.'
    
    # Initializing server object.
    if len(sys.argv) > 1 and sys.argv[1].isdigit():
        print sys.argv[1]
        dedicated_server = o_server(sys.argv[1])
    else:
        dedicated_server = o_server(32000)
   
    # Create empty array of client objects.
    connected_clients = []

    # Connect MySQL Database using database.txt file.
    dedicated_server.connect_database()
    
    test_char = character.character('test','poopstain','oldentide')
    test_char.create_in_database(dedicated_server)

    # Begin actual server operation loop.
    dedicated_server.run_server()
    dedicated_server.database.close()

class o_server:
    def __init__(self, user_port):
        self.o_address = ('0.0.0.0', user_port)
        self.o_port = user_port
        self.build_socket()

    def build_socket(self):
        try:
            self.o_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        except:
            sys.exit('Unable to create socket.')
        try:
            self.o_socket.bind((self.o_address))
        except:
            sys.exit('Unable to bind socket to port.')

    def run_server(self):
        inputs = [ self.o_socket ]
        outputs = []
        errors = []
        running = 1
        inbound_packets = {}
        outbound_packets = {}
        #self.o_socket.listen(1)

        # Main listening loop.
        while running:
            r_in, r_out, r_ex = select.select(inputs, outputs, errors)

            for s in r_in:
                if s is self.o_socket:
                    # Socket is ready to accept connection. 
                    print s
                    print self.o_socket

    def send_message(self, mesg):
        totalsent = 0
        while totalsent < MSGLEN:
            sent = self.o_socket.send(mesg[totalsent:])
            if sent == 0:
                raise RuntimeError("socket connection lost")
            totalsent = totalsent + sent
    
    #def receive_message():

    def connect_database(self):
        self.dbfile = open('../text/database.txt', 'r')
        self.mysql_hostname = self.dbfile.readline().split(' ')[1].rstrip()
        self.mysql_username = self.dbfile.readline().split(' ')[1].rstrip()
        self.mysql_database = self.dbfile.readline().split(' ')[1].rstrip()
        print "Enter the password for account '%s' on database '%s' at '%s'." \
        % (self.mysql_username, self.mysql_database, self.mysql_hostname)
        self.mysql_password = getpass.getpass()
        try:
            self.database = MySQLdb.connect( host=self.mysql_hostname, \
                                             user=self.mysql_username, \
                                             passwd=self.mysql_password, \
                                             db=self.mysql_database )
        except:
            sys.exit('Unable to connect to MySQL database.')
        self.mysql_cursor = self.database.cursor()
        self.mysql_cursor.execute("USE oldentide")
        print 'Connection to database established.'


class o_client:
    def __init__(self, ds, client_socket):
        self.oc_ds = ds;
        self.oc_socket = client_socket
        self.oc_account = ''
        self.oc_character = ''
        self.oc_status = 0
        self.oc_messages = []
    
    def check_login(self, client_account, client_password):
        try:
            self.oc_ds.mysql_cursor.execute( \
                "SELECT password FROM `accounts` WHERE account = \"%s\";" \
                % client_account)
        except:
            sys.exit('Account does not exist.')
        pass_check = self.oc_ds.mysql_cursor.fetchall()[0][0]
        if (pass_check == client_password):
            return 1
        else:
            return 0

    def set_account(self, client_account):
        self.oc_account = client_account

class o_account:
    def __init__(self, account_name):
        self.account = account_name
        self.retrieve_characters()

    def retrieve_characters(self):
        dedicated_server.mysql_cursor.execute( \
            "SELECT name FROM `characters` WHERE account = \"%s\";" \
            % self.account)
        for row in dedicated_server.mysql_cursor.fetchall():
            print row[0]

if __name__ == "__main__":
    main()
