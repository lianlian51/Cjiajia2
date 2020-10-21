all:udp_cli udp_srv
udp_srv:udp_srv.cpp
	g++ -std=c++11 $^ -o $@
udp_cli:udp_cli.c
	gcc $^ -o $@
