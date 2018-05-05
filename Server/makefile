BIN = mkdir database server client unittest

# If you don't have sudo access, you can put your local lib and header files here!
LOCAL_LIBS = lib_local
LOCAL_HEADERS = include_local

# Keep 3rd party files local, to simplify life (no sudo or messing with os files)
MSGPACK_HEADER = -I src/lib/msgpack
CATCH_HEADER = -I src/lib/catch
SQLITE_HEADERS = -I src/lib/sqlitecpp
SQLITE_LIBS = -L src/lib/sqlitecpp


SERVER_FILES = 		src/Main.cpp src/AdminShell.cpp src/Character.cpp src/GameState.cpp src/Npc.cpp src/Item.cpp src/Server.cpp src/Player.cpp src/SQLConnector.cpp src/Utils.cpp
CLIENT_FILES = 		src/TestClient.cpp src/Utils.cpp
UNITTEST_FILES = 	src/UnitTest.cpp src/AdminShell.cpp src/Character.cpp src/GameState.cpp src/Npc.cpp src/Item.cpp src/Server.cpp src/Player.cpp src/SQLConnector.cpp src/Utils.cpp

# Enable sqlitecpp to use query.getColumnOriginName() via -DSQLITE_ENABLE_COLUMN_METADATA
# Add -DSQLITE_USE_LEGACY_STRUCT to make sqlitecpp only work with sqlite versions <= 3.18
DEFS = -DSQLITE_ENABLE_COLUMN_METADATA


all : $(BIN)

mkdir :
	mkdir -p bin db src/lib


database db : mkdir
	sqlite3 db/Oldentide.db < db/InitializeDb.sql

npc npcs : mkdir
	bash db/InitializeNpcs.sh

# NOTE: With gcc/g++, dependent libraries need to be specified BEFORE the library it depends on
server : mkdir msgpack sqlitecpp
	g++ -g $(SERVER_FILES) -std=c++17 -L $(LOCAL_LIBS) -I $(LOCAL_HEADERS) $(MSGPACK_HEADER) $(SQLITE_HEADERS) $(SQLITE_LIBS) -lSQLiteCpp -lsqlite3 -ldl -lpthread -o bin/Server $(DEFS)

client : mkdir msgpack
	g++ -g $(CLIENT_FILES) -std=c++17 -L $(LOCAL_LIBS) -I $(LOCAL_HEADERS) $(MSGPACK_HEADER) -lpthread -o bin/Client

unittest : mkdir msgpack catch sqlitecpp
	g++ -g $(UNITTEST_FILES) -std=c++17 -L $(LOCAL_LIBS) -I $(LOCAL_HEADERS) $(CATCH_HEADER) $(MSGPACK_HEADER) $(SQLITE_HEADERS) $(SQLITE_LIBS) -lSQLiteCpp -lsqlite3 -ldl -lpthread -o bin/UnitTest $(DEFS)

clean :
	rm -rf bin/Server bin/Client bin/UnitTest db/Oldentide.db

cleanall : clean
	rm -rf src/lib/msgpack;
	rm -rf src/lib/catch;
	rm -rf src/lib/sqlitecpp;

cleansql :
	rm -rf src/lib/sqlitecpp;
	rm -rf src/lib/sqlitecpp_temp;

# Download msgpack-c and set it to v2.1.1 if needed
# Delete the rest of the files and only keep the headers (c++ version is a header-only library)
msgpack :
	@if [ ! -d "src/lib/msgpack" ]; \
	then \
		echo "Downloading Message Pack..."; \
		git clone https://github.com/msgpack/msgpack-c.git msgpack_temp; \
		cd msgpack_temp; \
		echo "Setting msgpack to v2.1.1"; \
		git checkout cpp-2.1.1 -q; \
		cd ..; \
		mv msgpack_temp/include src/lib/msgpack; \
		rm -rf msgpack_temp; \
	fi


# Download the Catch testing framework
catch :
	@if [ ! -d "src/lib/catch" ]; \
	then \
		echo "Downloading Catch test framework..."; \
		git clone https://github.com/philsquared/Catch.git catch_temp; \
		cd catch_temp; \
		echo "Setting catch to v1.10.0"; \
		git checkout v1.10.0 -q; \
		cd ..; \
		mv catch_temp/single_include src/lib/catch; \
		rm -rf catch_temp; \
	fi

# Download the SQLiteCpp and sqlite3 libraries and headers
sqlitecpp :
	@if [ ! -d "src/lib/sqlitecpp" ]; \
	then \
		echo "Downloading SQLiteCpp test framework..."; \
		git clone https://github.com/SRombauts/SQLiteCpp.git sqlitecpp_temp; \
		cd sqlitecpp_temp; \
		echo "Setting SQLiteCpp to 2.2.0"; \
		git checkout 2.2.0 -q; \
		mkdir -p build; \
		cd build; \
		cmake ..; \
		make; \
		cd ../..; \
		mkdir -p src/lib/sqlitecpp; \
		cp -r sqlitecpp_temp/include/SQLiteCpp src/lib/sqlitecpp/; \
		cp sqlitecpp_temp/build/libSQLiteCpp.a src/lib/sqlitecpp/; \
		cp sqlitecpp_temp/build/sqlite3/libsqlite3.a src/lib/sqlitecpp/; \
		cp sqlitecpp_temp/sqlite3/sqlite3.h src/lib/sqlitecpp/; \
		rm -rf sqlitecpp_temp; \
	fi

# NOTES:
# To NOT use the internal sqlite version that comes with sqlitecpp (e.g. libsqlite3-dev), add the following flag to the cmake command above:
# 		-DSQLITECPP_INTERNAL_SQLITE=OFF
# To use an external version of sqlite that is < 3.19, add the following flag to the cmake command above:
# 		-DSQLITE_USE_LEGACY_STRUCT=ON
# and be sure to also add -DSQLITE_USE_LEGACY_STRUCT to the g++ DEFS make variable above, or you'll get some errors in the headers





.PHONY: all, clean, cleanall, cleansql, mkdir, database, db, npc, npcs, server, client, unittest, msgpack, catch, sqlitecpp



# References:
# How to make a conditional make variable based on files:
# https://stackoverflow.com/questions/1077676/how-to-conditional-set-up-a-makefile-variable-by-testing-if-a-file-exists
# https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
