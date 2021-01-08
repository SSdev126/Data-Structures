//--------------------------------------------------
// List.C
// Implementation file for List ADT
//--------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs -----------------------------------------

// private NodeObj type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* previous;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj type{
	Node front:
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors -------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data ){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->previous = NULL;
	
	return(N)
	
}

// freeNode()
// Frees heap memory by setting everything to null
void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}

// newList(void)
// returns a new empty list
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back= L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	
}

// freeList()
// Frees all heap memory associated with *pL and sets *pL to NULL.
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL){
		while( length(*pL)!=0) {
			delete( *pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions ------------------------------------

// length()
// Returns the int value length of a List L
int length(List L){
	return(L->length);
}


// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
	return(L->index);
}

// front()
// Returns front element of L. Pre: length()>0
int front(List L){
	if(L->length <= 0){
		printf("List Error: calling front on empty list\n");
		exit(EXIT_FAILURE);
	}
	return(L->front);
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L){
	if(L->length <= 0){
		printf("List Error: calling back on empty list\n");
		exit(EXIT_FAILURE);
	}
	return(L->back);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
	if(L->length <= 0){
		printf("List Error: calling get on empty list\n");
		exit(EXIT_FAILURE);
	}
	if(L->index < 0){
		printf("List Error: calling get on empty list\n");
		exit(EXIT_FAILURE);
	}
	return((L->cursor)->data);
}