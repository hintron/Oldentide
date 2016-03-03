BIN = mkdir database sqlite3 server client

all : $(BIN)

mkdir : 
	mkdir -p bin db

database : mkdir
	sqlite3 db/Oldentide.db < InitializeDb.sql

sqlite3 : mkdir
	gcc -c lib/sqlite3/sqlite3.c -o lib/sqlite3/sqlite3.o 

server : mkdir
	g++ -g Account.cc Character.cc Main.cc Npc.cc Object.cc OldentideServer.cc Player.cc SQLConnector.cc GameState.cc lib/sqlite3/sqlite3.o -std=c++11 -ldl -lpthread -pthread -o bin/Server 

client : mkdir
	g++ -g TestClient.cc -std=c++11 -o bin/Client

clean :
	rm -f lib/sqlite3/sqlite3.o bin/Server bin/Client

.PHONY: All, Clean
