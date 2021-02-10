#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     makes ListClient
#  make Test           makes ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with command line argument 35
#  make check3         runs valgrind on ListTest
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
	g++ -std=c++11 -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++11 -Wall -c Shuffle.cpp

ListClient : ListClient.o List.o
	g++ -std=c++11 -Wall -o ListClient ListClient.o List.o 

ListClient.o : List.h ListClient.cpp
	g++ -std=c++11 -Wall -c ListClient.cpp

ListTest : ListTest.o List.o
	g++ -std=c++11 -Wall -o ListTest ListTest.o List.o

ListTest.o : List.h ListTest.cpp
	g++ -std=c++11 -Wall -c ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++11 -Wall -c List.cpp

clean :
	rm -f Shuffle Shuffle.o ListClient ListClient.o List.o ListTest ListTest.o

check1 : ListClient
	valgrind --leak-check=full ListClient

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35

check3 : ListTest
	valgrind --leak-check=full ListTest
