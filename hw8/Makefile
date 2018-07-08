neville: neville.o polint.o nrutil.o
	g++ neville.o polint.o nrutil.o -o neville

neville.o: neville.cc
	g++ -c neville.cc
polint.o: polint.c nrutil.o nrutil.h nr.h
	g++ -c polint.c
nrutil.o: nrutil.c
	g++ -c nrutil.c

