BIN = mkdir database server client units

all : $(BIN)

mkdir : 
	mkdir -p bin db

database : mkdir
	sqlite3 db/Oldentide.db < InitializeDb.sql

server : mkdir
	g++ -g AdminShell.cpp Character.cpp GameState.cpp Main.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp AccountManager.cpp -std=c++11 -lcrypto -ldl -lpthread -lsqlite3 -o bin/Server

client : mkdir
	g++ -g TestClient.cpp Utils.cpp LoginManager.cpp -std=c++11 -lcrypto -lpthread -o bin/Client

units : mkdir
	g++ -g UnitTest.cpp AccountManager.cpp AdminShell.cpp Character.cpp GameState.cpp LoginManager.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp -std=c++11 -lcrypto -ldl -lpthread -lsqlite3 -o bin/UnitTest

clean :
	rm -f bin/Server bin/Client bin/UnitTest

.PHONY: All, Clean
