BIN = mkdir database server client unittest

# See if there are any local library files to include
# If you don't have sudo access, put your lib files here!
LOCAL_LIB = -L lib_local

# See if there are any local header files to include
# If you don't have sudo access, put your include files here!
LOCAL_HEADER = -I include_local

# Keep message pack files local, to simplify life (no sudo or messing with os files)
MSGPACK_HEADER = -I msgpack
CATCH_HEADER = -I catch


SERVER_FILES = 		Main.cpp AdminShell.cpp Character.cpp GameState.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp
CLIENT_FILES = 		TestClient.cpp Utils.cpp
UNITTEST_FILES = 	UnitTest.cpp AdminShell.cpp Character.cpp GameState.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp


all : $(BIN)

mkdir :
	mkdir -p bin db

database : mkdir
	sqlite3 db/Oldentide.db < db/InitializeDb.sql; \
	bash db/InitializeNpcs.sh

server : mkdir msgpack
	g++ -g $(SERVER_FILES) -std=c++11 $(LOCAL_LIB) $(LOCAL_HEADER) $(MSGPACK_HEADER) -ldl -lpthread -lsqlite3 -o bin/Server

client : mkdir msgpack
	g++ -g $(CLIENT_FILES) -std=c++11 $(LOCAL_LIB) $(LOCAL_HEADER) $(MSGPACK_HEADER) -lpthread -o bin/Client

unittest : mkdir msgpack catch
	g++ -g $(UNITTEST_FILES) -std=c++11 $(LOCAL_LIB) $(LOCAL_HEADER) $(CATCH_HEADER) $(MSGPACK_HEADER) -ldl -lpthread -lsqlite3 -o bin/UnitTest

clean :
	rm -f bin/Server bin/Client bin/UnitTest;

cleanall : clean
	rm -rf msgpack;
	rm -rf catch;


# Download msgpack-c and set it to v2.1.1 if needed
# Delete the rest of the files and only keep the headers (c++ version is a header-only library)
msgpack :
	@if [ ! -d "msgpack" ]; \
	then \
		echo "Downloading Message Pack..."; \
		git clone https://github.com/msgpack/msgpack-c.git msgpack_temp; \
		cd msgpack_temp; \
		echo "Setting msgpack to v2.1.1"; \
		git checkout -b cpp-2.1.1; \
		cd ..; \
		mv msgpack_temp/include msgpack; \
		rm -rf msgpack_temp; \
	fi


# Download the Catch testing framework
catch :
	@if [ ! -d "catch" ]; \
	then \
		echo "Downloading Catch test framework..."; \
		git clone https://github.com/philsquared/Catch.git catch_temp; \
		cd catch_temp; \
		echo "Setting catch to v1.10.0"; \
		git checkout -b v1.10.0; \
		cd ..; \
		mv catch_temp/single_include catch; \
		rm -rf catch_temp; \
	fi




.PHONY: all, clean, cleanall, mkdir, database, server, client, unittest, msgpack, catch



# References:
# How to make a conditional make variable based on files:
# https://stackoverflow.com/questions/1077676/how-to-conditional-set-up-a-makefile-variable-by-testing-if-a-file-exists
# https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html