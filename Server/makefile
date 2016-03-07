BIN = mkdir sqlite3 database server client

all : $(BIN)

mkdir : 
	mkdir -p bin db

sqlite3 : mkdir
	gcc -c lib/sqlite3/sqlite3.c -o lib/sqlite3/sqlite3.o 

database : mkdir
	sqlite3 db/Oldentide.db < InitializeDb.sql

server : mkdir
	g++ -g Account.cpp Character.cpp Main.cpp Npc.cpp Object.cpp OldentideServer.cpp Player.cpp SQLConnector.cpp GameState.cpp AdminShell.cpp lib/sqlite3/sqlite3.o -std=c++11 -ldl -lpthread -pthread -o bin/Server 

client : mkdir
	g++ -g TestClient.cpp -std=c++11 -o bin/Client

clean :
	rm -f lib/sqlite3/sqlite3.o bin/Server bin/Client

.PHONY: All, Clean
