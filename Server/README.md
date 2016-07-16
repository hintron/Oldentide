#####Prerequisites:<br><br>

Currently the development for the Oldentide dedicated server is being done in the Linux environment.  

All provided makefiles and libraries used are meant to be seen through those eyes (Linux development environment).

* g++ compiler

Any Linux distribution should be able to compile this widely standard library based code, granted you have the following libries for SQLite3.

* libsqlite3-dev

And SQLite3 installed on your machine.

==================================

###Server and Test Client Usage:

In linux, cd into Oldentide/Server/ and run

    make 

In order for the server to properly build, you will need to make sure that these packages are installed:

    sqlite3
    libsqlite3-dev

If everything built properly, run

    bin/Server <Port>

where <Port> is the port the server is using.

To test that the server is running, in a separate terminal, run

    bin/Client <IP> <Port>

Where <IP> is the address of the server and <Port> is the port of the server.


==================================

Windows (cmake) compiling may be implemented in further releases.
