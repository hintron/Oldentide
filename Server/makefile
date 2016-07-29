BIN = mkdir database server client

all : $(BIN)

mkdir : 
	mkdir -p bin db

database : mkdir
	sqlite3 db/Oldentide.db < InitializeDb.sql

server : mkdir
	g++ -g AdminShell.cpp Character.cpp GameState.cpp Main.cpp Npc.cpp GameObject.cpp OldentideServer.cpp Player.cpp SQLConnector.cpp Utils.cpp AccountManager.cpp -std=c++11 -ldl -lpthread -lsqlite3 -lcrypto -pthread -o bin/Server

client : mkdir
	g++ -g TestClient.cpp Utils.cpp -std=c++11 -o bin/Client

clean :
	rm -f bin/Server bin/Client

.PHONY: All, Clean
