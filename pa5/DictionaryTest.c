//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//
//
//             DictionaryTest.c
// Assignment: Pa5: lex tree
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Implementation file for list ADT
//----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"

int main (int argc, char* argv[]){
  
  
  int i, n=26;
  Dictionary A = newDictionary(0);
  Dictionary B = newDictionary(1);
  char* word[] = { "n","z","w","k","i","c","l","d","t","a", 
		   "e","y","b","h","v","f","s","m","x","r",
		   "o","u","p","g","j","q" };
  VAL_TYPE x;
  VAL_TYPE y;
  


  // add pairs to A --------------------------------------
  for(i=0; i<n; i++){
    insert(A, word[i], i);
  }

  // add pairs to B
  for(i=n-1; i>=0; i--){
    insert(A, word[i], i);
    insert(B, word[i], i);
  }


  printf("Dictionary A's size is %d\n", size(A));
  printf("Dictionary B's size is %d\n", size(B));
  
  printf("Dictionary A only accept unique keys: %s\n", ((getUnique(A)!=0)?"true":"false"));
  printf("Dictionary B only accept unique keys: %s\n", ((getUnique(B)!=0)?"true":"false"));
  y = 99;
  insert(B, "zz", y);

  x = lookup( B, "zz");
  printf("lookup check returned "VAL_FORMAT" should be 99\n", x);
  printf("printDictionary before delete\n");
  printDictionary(stdout, B);
  delete(B, "zz");
  printf("printDictionary check\n");
  printDictionary(stdout, B);
  
  printf("forward A:\n");
  for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x = next(A)){
    printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
  }
  printf("\n\n");

  printf("reverse B:\n");
  for( y = beginReverse(B); currentVal(B) != VAL_UNDEF; y = prev(B)){
    printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(B), y);
  }
  printf("\n\n");
  
  makeEmpty(A);
  printDictionary(stdout, A);
  
  freeDictionary(&A);
  freeDictionary(&B);
  return(0);
}
