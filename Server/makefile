BIN = mkdir sqlite3 server client

all : $(BIN)

mkdir : 
	mkdir -p bin db

sqlite3 : mkdir
	gcc -c lib/sqlite3/sqlite3.c -o lib/sqlite3/sqlite3.o 

server : mkdir
	g++ -g Account.cc Character.cc Main.cc Npc.cc Object.cc OldentideServer.cc Player.cc SQLConnector.cc lib/sqlite3/sqlite3.o -std=c++11 -ldl -lpthread -pthread -o bin/Server 

client : mkdir
	g++ -g TestClient.cc -std=c++11 -o bin/Client

clean :
	rm -f lib/sqlite3/sqlite3.o bin/Server bin/Client

.PHONY: All, Clean
