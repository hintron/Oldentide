###############################################################################
#                             Oldentide Makefile                              #
#                              Joseph DeVictoria                              #
#                                     2014                                    #
###############################################################################

oldentide: source/oldentide.cpp source/character.cpp source/packet.cpp
	g++ -g source/oldentide.cpp source/character.cpp source/packet.cpp -o oldentide

oldentide_server: source/oldentide_server.cpp source/character.cpp source/packet.cpp
	g++ -g source/oldentide_server.cpp source/character.cpp source/packet.cpp -o oldentide_server

test_client: dev/test_client.cpp
	g++ -g dev/test_client.cpp -o test_client

clean:
	rm oldentide oldentide_server test_client 
