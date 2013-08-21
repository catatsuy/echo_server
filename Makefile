all:
	make compile
	make run

compile:
	g++ -O2 -Wall -W main.cc -o echo_server.out

run:
	./echo_server.out
