//-----------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//
//
//              Lex.C
// Assignment: Pa5: Lex tree
//             CSE 101, Indroduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description: This program creates a Dictionary that stores the Lexographical order
//              of the input strings.
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 300

int main(int argc, char* argv[]){

  FILE *fileIn, *fileOut;
  char line[MAX_LEN];
  int totalLines = 0;
  int j = 0;
  int i = 0;
  int *k = 0;
  Dictionary myDict = newDictionary(0);
  if ( argc != 3){
    printf("Error: too few inputs\n");
    exit(1);
  }

  fileIn = fopen(argv[1], "r"); // open our files
  fileOut = fopen(argv[2], "w");

  if( fileIn == NULL){ // check if fileIn opened
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  if( fileOut == NULL){ // check if fileOut opened
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }
  
  while( fgets(line, sizeof(line), fileIn)){
    totalLines++;
  }
  
  char *myArr[totalLines];
  rewind(fileIn);

  while( fgets(line, sizeof(line), fileIn)){ // reading the file in until fgets fails
    size_t length = strlen(line);
    if(line[length-1] == '\n'){
      line[--length] = 0;
    }
    if(( myArr[i] = malloc(length + 1))){

      strcpy(myArr[i], line);
      insert(myDict, myArr[i], k);
      i++;
      k++;
    }
  }

  printDictionary(fileOut, myDict, "pre");
  printDictionary(fileOut, myDict, "in");
  printDictionary(fileOut, myDict, "post");

  fclose(fileIn);
  fclose(fileOut);
  freeDictionary(&myDict);
  for( j = 0; j < i ; j++){
    free(myArr[j]);
  }

  return(0);
}
