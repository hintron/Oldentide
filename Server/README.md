Oldentide Dedicated Server
==
The *Oldentide Dedicated Server* is an open source project, built in [Go][1], to implement the
backend game state for the multiplayer online role-playing game [*Oldentide*][2].  This
directory contains all of the code necessary to build and run the dedicated server.

The "from scratch" build process breaks down into three main steps, with an additional
step used during the development process:

1. Create the database and generate all of the needed tables.
2. Populate the database with NPC information.
3. Compile the dedicated server.
4. Compile the test client. <IP>

Requirements
------------
The *Oldentide Dedicated Server* currently supports a Linux development and runtime environment. (Although it should work on Windows with some hacking)

Operating Systems
------------
All development and testing is currently done on a 64-Bit linux environment.
[Ubuntu 18.04 LTS][3] is recommended (being used by the primary developer).
Other distributions should work as long as you can run Go and Git.

Compilers
------------
Building *Oldentide Dedicated Server* is consistent with the standard ["Go" build/install tools][4]

Dependencies
------------
* [git][5] - Needed for revision control, and for downloading and installing msgpack and go-sqlite3.
    * **sudo apt install -y git-all**
* [sqlite3][6] - The sqlite3 command-line tool, used to initialize and manage our sqlite databases.
    * **sudo apt install -y sqlite3 libsqlite3-dev**
    * **go get github.com/mattn/go-sqlite3**
* [msgpack-go][7] is used for data serialization for transmitting packets between server and client.
    * Msgpack recommends the Vmihailenco implementation of msgpack for go.
    * **go get github.com/vmihailenco/msgpack**

Server and Test Client Usage
------------
In linux:

Switch to the db directory and initialize the Oldentide DB:

    sqlite3 Oldentide.db < init_db.sql

Update your GOPATH to point to our working directory:

    echo "export GOPATH=<path to Oldentide/Server/> >> ~/.bashrc"
    source ~/.bashrc

or

    export GOPATH=<path to Oldentide/Server/>

Download necessary dependencies (see above)

    go get <...>

cd into the src/server folder and run

    go install

If everything built properly, cd back to the Oldentide/Server directory and run

    <Oldentide_Base_Path>/Server/bin/dedicated_server <Port>

where \<Port\> is the port the server is using.

[1]: http://golang.org/ "The Go Language"
[2]: http://www.oldentide.com/ "Oldentide, a game where you can be anyone!"
[3]: http://www.ubuntu.com/ "Ubuntu · The world's most popular free OS"
[4]: https://golang.org/cmd/go/ "Go Cmd Documentation"
[5]: https://git-scm.com/ "Git"
[6]: https://www.sqlite.org/ "SQLite 3"
[7]: https://github.com/msgpack/msgpack-go/ "msgpack-go"
[7]: https://github.com/mattn/go-sqlite3 "go-sqlite3"
