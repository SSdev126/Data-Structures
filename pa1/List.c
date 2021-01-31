//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              1/16/2021
//
//             List.c
// Assignment: Pa1: lex list
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Implementation file for list ADT
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
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
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index; // represents the distance of cursor from the front of the list
} ListObj;

// Constructors-Destructors -------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data ){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->previous = NULL;
  
  return(N);
  
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
  return (L);  
}

// freeList()
// Frees all heap memory associated with *pL and sets *pL to NULL.
void freeList(List* pL){
  if(pL!=NULL && *pL!=NULL){
    while( length(*pL) != 0) {
      deleteFront( *pL);
      
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
  if(length(L) <= 0){
    printf("List Error: calling front on empty list\n");
    exit(EXIT_FAILURE);
  }
  return(L->front->data);
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L){
  if(length(L) <= 0){
    printf("List Error: calling back on empty list\n");
    exit(EXIT_FAILURE);
  }
  return(L->back->data);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
  if(length(L) <= 0){
    printf("List Error: calling get on empty list\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0){
    printf("List Error: calling get on list with undefine index\n");
    exit(EXIT_FAILURE);
  }
  return(L->cursor->data);
}

// equals
// Returns true(1) if Lists A and B are in same state,
// and returns false(0) otherwise
int equals(List A, List B){
  if(length(A) != length(B)){ // if their lengths aren't the same 
    return(0);                // obviously they aren't equal
  }
  int i;
  List tempA = copyList(A); // copy this list cause we need
  List tempB = copyList(B); // preserve the indexes of the other lists
  moveFront(tempA); // intialize both the new lists
  moveFront(tempB);
  for( i = 0; i < length(A); i++){// read through the lists if something doesn't
    if( get(tempA) != get(tempB)){// match we're done time to free and drop out
      freeList(&tempA);
      freeList(&tempB);
      return(0);                  // return failure.
    }
    moveNext(tempA);
    moveNext(tempB);
  }
  freeList(&tempA);
  freeList(&tempB);
  return(1);                      // if we made it here it's true.
}


// Manipulation procedures ----------------------------------------
// clear()
// Resets L to its original empty state.
void clear(List L){
  while( length(L) != 0){
    deleteFront(L);
  }
  
}

// set()
// Overwrites the cursor element's data with x.
void set(List L, int x){
  if(length(L) <= 0){
    printf("List Error: calling set on empty list\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0){
    printf("List Error: calling set on list with undefined index\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
  
}

// moveFront()
// if L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
  if(length(L) <= 0){
    printf("List Error: calling moveFront on empty List\n");
    //exit(EXIT_FAILURE);
    return;
  }
  L->cursor = L->front;
  L->index = 0;
}

// moveBack()
// if L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveBack(List L){
  if(length(L) <= 0){
    printf("List Error: calling moveBack on empty List\n");
    exit(EXIT_FAILURE);
  }
  L->cursor = L->back;
  L->index = (L->length-1);
}


// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L: if cursor is defined and at
// front, cursor becomes undefined: if cursor is undefined 
// do nothing
void movePrev(List L){
  if(index(L) == -1){
    return;
  }
  if (get(L) == front(L)){ // if we're moving off the list 
    L->index = -1;         // set index and cursor to undefined state
    L->cursor = NULL;
    return;
  }else if(get(L) != front(L)){
    L->cursor = L->cursor->previous;
    L->index--;
  }
}

// moveNext()
// if cursor is defined and not at back, move cursor one
// step towards the back of L: if cursor is defined and at
// back, cursor becomes undefined: if cursor is undefined
// do nothing
void moveNext(List L){
  if(index(L) == -1){
    return;
  }
  if(get(L) == back(L)){ // if we're moving off the back of the list
    L->index = -1;       // set index and cursor to undefined state
    L->cursor = NULL;
    return;

  }else if(get(L)!= back(L)){
    L->cursor = L->cursor->next;
    L->index++;
  }
}

// prepend()
// Insert new element into L. if L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x){
  Node N = newNode(x);
  if( L==NULL){
    printf("List Error: calling prepend() on NULL List reference");
    exit(EXIT_FAILURE);
  }
  if(length(L) == 0){ // empty list N becomes new front and back
    L->front = L->back = N;
  } else{
    L->front->previous = N;
    N->next = L->front;
    L->front = N;
  }
  if(index(L) != -1){ // move the index up because we're putting stuff behind it
    L->index++;
  }
  L->length++;
}

// append()
// Insert new element into L. if L is non-empty,
// insertion takes place after back element.
void append(List L, int x){
  Node N = newNode(x);
  if( L==NULL){
    printf("List Error: calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  if(length(L) == 0){ // if L is an empty list N becomes its front and back
    L->front = L->back = N;
  } else{
    L->back->next = N;
    N->previous = L->back;
    L->back = N;
  }
  L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
  if( length(L) <= 0){
    printf("List Error: calling insertBefore on empty List.\n");
    exit(EXIT_FAILURE);
  }
  if( index(L) < 0){
    printf("List Error: called insertBefore with an undefined index.\n");
    exit(EXIT_FAILURE);
  }
  Node N = newNode(x);
  if( get(L) == front(L)){  // if its front we don't have a previous to perserve
    L->front->previous = N;
    N->next = L->front;
    L->front = N;
  }else {
    (((L->cursor)->previous)->next) = N;
    N->previous = ((L->cursor)->previous);
    N->next = L->cursor;
    L->cursor->previous = N;
  }
  
  L->length++;
}

// insertAfter()
// insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
  if( length(L) <=0){
    printf("List Error: calling insertAfter on a empty List.\n");
    exit(EXIT_FAILURE);
  }
  if( index(L) < 0){
    printf("List Error: called insertAfter with an undefined index.\n");
    exit(EXIT_FAILURE);
  }
  Node N = newNode(x);
  if( get(L) == back(L)){ // if its back we don't have a next to perserve 
    L->back->next = N;
    N->previous = L->back;
    L->back = N;
  }else {
    (((L->cursor)->next)->previous) = N;
    N->next = ((L->cursor)->next);
    N->previous = L->cursor;
    L->cursor->next = N;
  }
  L->length++;
}

// deleteFront()
// delete the front element. Pre: length()>0
void deleteFront(List L){
  if ( L == NULL){
    printf("List Error: calling deletefront() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling deleteFront on empty List.\n");
    exit(EXIT_FAILURE);
  }
  Node N = NULL;
  N = L->front;
  if(index(L) == 0){
    L->index = -1;
    L->cursor = NULL;
  }else{L->index--;}
  if( length(L) > 1){
    L->front = L->front->next;
    L->front->previous = NULL;
  }else {
    L->front = L->back = NULL;
  }
  L->length--;
  freeNode(&N);
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L){
  if( length(L) <= 0){
    printf("List Error: calling deleteBack on empty List.\n");
    exit(EXIT_FAILURE);
  }
  Node N = NULL;
  N = L->back;
  if( index(L) == (length(L)-1)){
    L->index = -1;
    L->cursor = NULL;
  }
  if( length(L) > 1){
    L->back = L->back->previous;
    L->back->next = NULL;
  }else {
    L->back = L->front = NULL;
  }
  L->length--;
  freeNode(&N);
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
  if( length(L) <=0){
    printf("List Error: calling delete on empty List.\n");
    exit(EXIT_FAILURE);
  }
  if( index(L) < 0){
    printf("List Error: called delete with undefined index.\n");
    return;
  }
  if( length(L) > 0){
    if( index(L) == 0){ // delete is being called on the front element
      deleteFront(L);
      return;
    }else if( index(L) == (length(L)-1)) { // delete is being called on the back element
      deleteBack(L);
      return;
    }else {
      Node N = NULL;
      N = L->cursor;
      L->cursor->next->previous = L->cursor->previous;
      L->cursor->previous->next = L->cursor->next;
      L->cursor->next = NULL;
      L->cursor->previous = NULL;
      L->length--;
      freeNode(&N);
      L->index = -1;
      L->cursor = NULL;
    }
  }
}

// other operations------------------------------------------------------

// printList()
// Prints to the file point to by out, a
// string representation of L consisting
// of a space separated sequence of intergers,
// with front on left.
void printList(FILE *out, List L){
  
  if( L==NULL){
    printf("List Error: calling printList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  Node N = NULL;
  //FILE *fileWrite = fopen( out, "w");
  for(N = L->front; N != NULL; N = N->next){
    fprintf(out,"%d " ,N->data);
  }
  //fclose(fileWrite);
  freeNode(&N);
}

// copyList()
// Returns a new List representing the same integers
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. the state 
// of L is unchanged.
List copyList(List L){
  if( L == NULL){
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  List NL = newList();
  Node N = NULL;
  
  for(N = L->front; N != NULL; N = N->next){
    append( NL, N->data); 
    
  }
  freeNode(&N);
  return(NL);
}

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B){
  List L = copyList(A);
  Node N = B->front;
  while( N != NULL){
    append(L, N->data);
    N = N->next;
  }
  return(L);
  
}
