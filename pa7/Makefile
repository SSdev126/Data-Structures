#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 7
#
#  make                     makes Arithmetic
#  make BigIntegerTest      makes BigIntegerTest
#  make clean               removes all binaries
#  make memcheck            tests for memory leaks
#------------------------------------------------------------------------------

CLIENT         = Arithmetic
ADT1           = BigInteger
ADT2           = List
TEST           = $(ADT1)Test
TEST_SRC       = $(TEST).c
TEST_OBJ       = $(TEST).o
LIST           = $(ADT2)Test
LIST_SRC       = $(LIST).c
LIST_OBJ       = $(LIST).o
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = gcc -c -std=c11 -Wall
LINK           = gcc -lm -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(TEST) : $(TEST_OBJ) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(TEST) $(TEST_OBJ) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(TEST_OBJ) : $(TEST_SRC) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(TEST_SRC)

$(LIST) : $(LIST_OBJ)  $(ADT2_OBJECT)
	$(LINK) $(LIST) $(LIST_OBJ) $(ADT2_OBJECT)

$(LIST_OBJ) : $(LIST_SRC) $(ADT2_HEADER)
	$(COMPILE) $(LIST_SRC)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) $(TEST) $(TEST_OBJ) $(LIST) $(LIST_OBJ)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT) in3 myout3
