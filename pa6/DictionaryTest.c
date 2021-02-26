//-----------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//
//
//              DictionaryTest.c
// Assignment: Pa6: RB tree
//             CSE 101, Indroduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description: This program test the functions declared in Dictionary.h
//              
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"


int main(){
  int j = 69;
  int *k = &j;
  Dictionary myDict = newDictionary(0);
  Dictionary uniqueDict = newDictionary(1);
  printf( "is  myDict unique?  %d\n", getUnique(myDict));
  printf( "is  uniqueDict unique?  %d\n", getUnique(uniqueDict));
  printf( "empty lookup results should be "VAL_FORMAT" results are "VAL_FORMAT"\n", VAL_UNDEF, lookup(myDict, "z"));
  insert(myDict, "a", k);
  insert(myDict, "b", k);
  insert(myDict, "c", k);
  insert(myDict, "d", k);
  insert(myDict, "e", k);

  insert(uniqueDict, "a", k);
  insert(uniqueDict, "b", k);
  insert(uniqueDict, "c", k);
  insert(uniqueDict, "d", k);
  insert(uniqueDict, "e", k);
  insert(uniqueDict, "a", k);
  printDictionary(stdout, uniqueDict, "in");
  printDictionary(stdout, uniqueDict, "pre");
  printDictionary(stdout, uniqueDict, "post");
  delete(myDict, "a");
  if(size(myDict) != 4) printf("failed first test %d \n", size(myDict));
  insert(myDict, "f", k);
  delete(myDict, "e");
  if (size(myDict) != 4) printf("failed second test %d \n", size(myDict));
  printf("forward myDict:\n");
  for( k = beginForward(myDict); currentVal(myDict) != VAL_UNDEF; k = next(myDict)){
    printf("key: "KEY_FORMAT"\n", currentKey(myDict));
  }
  printf("reverse myDict:\n");
  for( k = beginReverse(myDict); currentVal(myDict) != VAL_UNDEF; k = prev(myDict)){
    printf("key: "KEY_FORMAT"\n", currentKey(myDict));
  }
  makeEmpty(myDict);
  printf("makeEmpty and empty printDictionary tests\n");
  printDictionary(stdout,myDict, "in");
  freeDictionary(&myDict);
  freeDictionary(&uniqueDict);
  return(0);
}
