BIN = sqlite3 server client

all: $(BIN)

sqlite3 : lib/sqlite3/sqlite3.c lib/sqlite3/sqlite3.h
	gcc -c -o bin/sqlite3.o lib/sqlite3/sqlite3.c
server : Account.cc Account.h Character.cc Character.h Main.cc Npc.cc Npc.h Object.cc Object.h OldentideServer.cc OldentideServer.h Player.cc Player.h SQLConnector.cc SQLConnector.h lib/sqlite3/sqlite3.h bin/sqlite3.o
	g++ -std=c++11 -pthread -o bin/Server -g Account.cc Character.cc Main.cc Npc.cc Object.cc OldentideServer.cc Player.cc SQLConnector.cc bin/sqlite3.o -ldl -lpthread 

client : TestClient.cc
	g++ -g TestClient.cc -std=c++11 -o bin/Client

clean :
	rm -f bin/sqlite3.o bin/Server bin/Client

.PHONY: All, Clean
