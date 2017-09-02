BIN = mkdir database server client unittest

all : $(BIN)

mkdir :
	mkdir -p bin db

database : mkdir
	sqlite3 db/Oldentide.db < db/InitializeDb.sql; \
    bash db/InitializeNpcs.sh

server : mkdir msgpack
	g++ -g Main.cpp AdminShell.cpp Character.cpp GameState.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp -std=c++11 -ldl -lpthread -lsqlite3 -o bin/Server

client : mkdir msgpack
	g++ -g TestClient.cpp Utils.cpp -std=c++11 -lpthread -o bin/Client

unittest : mkdir
	g++ -g UnitTest.cpp AdminShell.cpp Character.cpp GameState.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp -std=c++11 -ldl -lpthread -lsqlite3 -o bin/UnitTest

clean :
	rm -f bin/Server bin/Client bin/UnitTest

# TODO: It appears that msgpack-c is a header-only library. This means that once the header files are in place,
# I could probably delete the msgpack-c/ folder to keep things tidy.
# But... if the user exits out when they see sudo password prompt, it would be nice to restart without redownloading it.

# Download msgpack-c v2.1.1 and do a one-time build
msgpck_build :
	@if [ -d "msgpack-c" ]; \
	then \
		echo "msgpack-c should already be built. If not, run \"make clean-m\" and then \"make msgpack\""; \
	else \
		echo "Downloading msgpack-c..."; \
		git clone https://github.com/msgpack/msgpack-c.git; \
		cd msgpack-c; \
		git checkout -b cpp-2.1.1; \
		echo "Building msgpack-c..."; \
		cmake .; \
		make; \
	fi

# Do a one-time installation of headers to /usr/local/include/
msgpack msgpck : msgpck_build
	@if [ -d "/usr/local/include/msgpack" ]; \
	then \
		echo "msgpack-c headers should already be installed at /usr/local/include/. If not, run \"make clean-m\" and then \"make msgpack\""; \
	else \
		cd msgpack-c; \
		sudo make install; \
	fi

# Uninstalls msgpack - deletes repo and removes headers from /usr/local/include/
clean-m :
	sudo rm -rf msgpack-c/;
	sudo rm -rf /usr/local/include/msgpack*;

.PHONY: All, Clean
