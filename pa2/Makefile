#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make FindPath          makes FindPath
# make GraphClient       makes GraphClient
# make clean             removes all binaries
# make checkTest       checks GraphTest for memory errors
# make checkPath          checks FindPath for memory errors
#------------------------------------------------------------------------------

GraphTest : GraphTest.o Graph.o List.o
	gcc -std=c11 -Wall -o GraphTest GraphTest.o Graph.o List.o

GraphTest.o : GraphTest.c Graph.h List.h
	gcc -std=c11 -Wall -c GraphTest.c

FindPath : FindPath.o Graph.o List.o
	gcc -std=c11 -Wall -o FindPath FindPath.o Graph.o List.o

FindPath.o : FindPath.c Graph.h List.h
	gcc -std=c11 -Wall -c FindPath.c

GraphClient : GraphClient.o Graph.o List.o
	gcc -std=c11 -Wall -o GraphClient GraphClient.o Graph.o List.o

GraphClient.o : GraphClient.c Graph.h List.h
	gcc -std=c11 -Wall -c GraphClient.c

Graph.o : Graph.c Graph.h List.h
	gcc -std=c11 -Wall -c Graph.c

List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c

clean :
	rm -f FindPath GraphTest GraphClient GraphClient.o GraphTest.o FindPath.o Graph.o List.o

checkTest : 
	valgrind --leak-check=full --track-origins=yes GraphTest

checkPath :
	valgrind --leak-check=full --track-origins=yes FindPath in3 blah3
