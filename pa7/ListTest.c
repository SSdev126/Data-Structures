//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              3/03/2021
//
//              ListTest.c
// Assignment: Pa7:  BigIntegers
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  unit test for List ADT
//----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

int main(){
  List A = newList();
  List B = newList();
  List C = newList();
  List D = NULL;
  int i, j, k;

  for( i = 0; i <= 20; i++){
    append(A, i);
    prepend(B, i);
    if( i % 2 == 0){
      append(C, i);
    }
    
  }

  printList(stdout, A);
  printf("\n");
  printList(stdout, B);
  printf("\n");
  printList(stdout, C);
  printf("\n");

  printf("length of A = %d\n", length(A));
  
  for(moveFront(A); index(A)>= 0; moveNext(A)){
    printf("%ld ", get(A));
  }
  printf("\n");

  for(moveBack(B); index(B)>= 0; movePrev(B)){
    printf("%ld ", get(B));
  }
  printf("\n");
  
  printf(" A == B: %s\n", ListEquals(A,B)?"true":"false");

  deleteFront(A);
  deleteBack(B);
  for(moveBack(B); index(B) >= 0; movePrev(B)){
    if(get(B) % 2 == 1){
      delete(B);
      moveBack(B);
    }
  }
  
  for(moveFront(A); index(A) >= 0; moveNext(A)){
    if(get(A) % 2 == 0){
      delete(A);
      moveFront(A);
    }
  }
  printList(stdout, A);
  printf("\n");
  printList(stdout, B);
  printf("\n");
  D = copyList(C);

  printList(stdout, D);
  printf("\n");
  
  for(moveFront(A); index(A) >= 0; moveNext(A)){
    set(A, 7);
    
  }
  printList(stdout, A);

  freeList(&A);
  freeList(&B);
  freeList(&C);
  freeList(&D);

  return(EXIT_SUCCESS);

}
