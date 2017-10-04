BIN = mkdir database server client unittest

# If you don't have sudo access, you can put your local lib and header files here!
LOCAL_LIBS = lib_local
LOCAL_HEADERS = include_local

# Keep message pack files local, to simplify life (no sudo or messing with os files)
MSGPACK_HEADER = -I msgpack
CATCH_HEADER = -I catch
SQLITECPP_HEADER = -I sqlitecpp
SQLITECPP_LIB = -L sqlitecpp -lSQLiteCpp


SERVER_FILES = 		Main.cpp AdminShell.cpp Character.cpp GameState.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp
CLIENT_FILES = 		TestClient.cpp Utils.cpp
UNITTEST_FILES = 	UnitTest.cpp AdminShell.cpp Character.cpp GameState.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp


all : $(BIN)

mkdir :
	mkdir -p bin db


database : mkdir
	sqlite3 db/Oldentide.db < db/InitializeDb.sql; \
	bash db/InitializeNpcs.sh

# NOTE: Dependent libraries need to be specified BEFORE the library it depends on (sqlitecpp, then sqlite)
# -DSQLITE_USE_LEGACY_STRUCT is needed for sqlitecpp to work if sqlite is < v3.19
server : mkdir msgpack sqlitecpp
	g++ -g $(SERVER_FILES) -std=c++11 -L $(LOCAL_LIBS) -I $(LOCAL_HEADERS) $(MSGPACK_HEADER) $(SQLITECPP_HEADER) $(SQLITECPP_LIB) -ldl -lpthread -lsqlite3 -o bin/Server -DSQLITE_USE_LEGACY_STRUCT

client : mkdir msgpack
	g++ -g $(CLIENT_FILES) -std=c++11 -L $(LOCAL_LIBS) -I $(LOCAL_HEADERS) $(MSGPACK_HEADER) -lpthread -o bin/Client

unittest : mkdir msgpack catch sqlitecpp
	g++ -g $(UNITTEST_FILES) -std=c++11 -L $(LOCAL_LIBS) -I $(LOCAL_HEADERS) $(CATCH_HEADER) $(MSGPACK_HEADER) $(SQLITECPP_HEADER) $(SQLITECPP_LIB) -ldl -lpthread -lsqlite3 -o bin/UnitTest -DSQLITE_USE_LEGACY_STRUCT

clean :
	rm -f bin/Server bin/Client bin/UnitTest;

cleanall : clean
	rm -rf msgpack;
	rm -rf catch;
	rm -rf sqlitecpp;

cleansql :
	rm -rf sqlitecpp;
	rm -rf sqlitecpp_temp;

# Download msgpack-c and set it to v2.1.1 if needed
# Delete the rest of the files and only keep the headers (c++ version is a header-only library)
msgpack :
	@if [ ! -d "msgpack" ]; \
	then \
		echo "Downloading Message Pack..."; \
		git clone https://github.com/msgpack/msgpack-c.git msgpack_temp; \
		cd msgpack_temp; \
		echo "Setting msgpack to v2.1.1"; \
		git checkout cpp-2.1.1 -q; \
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
		git checkout v1.10.0 -q; \
		cd ..; \
		mv catch_temp/single_include catch; \
		rm -rf catch_temp; \
	fi

# Download the SQLiteCpp
sqlitecpp :
	@if [ ! -d "sqlitecpp" ]; \
	then \
		echo "Downloading SQLiteCpp test framework..."; \
		git clone https://github.com/SRombauts/SQLiteCpp.git sqlitecpp_temp; \
		cd sqlitecpp_temp; \
		echo "Setting SQLiteCpp to 2.2.0"; \
		git checkout 2.2.0 -q; \
		rm -rf sqlite3; \
		mkdir -p build; \
		cd build; \
		cmake -DSQLITE_USE_LEGACY_STRUCT=ON -DSQLITECPP_INTERNAL_SQLITE=OFF ..; \
		make; \
		cd ../..; \
		mkdir -p sqlitecpp; \
		cp -r sqlitecpp_temp/include/SQLiteCpp sqlitecpp/; \
		cp sqlitecpp_temp/build/libSQLiteCpp.a sqlitecpp/; \
		rm -rf sqlitecpp_temp; \
	fi

		# Uninstall libsqlite3-dev and use the following to use the version of sqlite that comes with sqlitecpp...
		# cmake ..; \
		# cp sqlitecpp_temp/build/sqlite3/libsqlite3.a sqlitecpp/; \
		# cp sqlitecpp_temp/sqlite3/sqlite3.h sqlitecpp/; \


.PHONY: all, clean, cleanall, cleansql, mkdir, database, server, client, unittest, msgpack, catch, sqlitecpp



# References:
# How to make a conditional make variable based on files:
# https://stackoverflow.com/questions/1077676/how-to-conditional-set-up-a-makefile-variable-by-testing-if-a-file-exists
# https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html