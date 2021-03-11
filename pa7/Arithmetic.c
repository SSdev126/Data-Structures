//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              3/03/2021
//
//              Arithmetic.c
// Assignment: Pa7:  BigIntegers
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Header file for doubly linked list ADT
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "BigInteger.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]){

  
  FILE *fileIn, *fileOut;
  
  int totalLines = 0;
  char line[MAX_LEN];
  int j = 0;
  int i = 0;
  //int *k = 0;
  BigInteger A, B, C, D, E;
  //char *myArr[2];
  //Dictionary myDict = newDictionary(0);
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
  
  fgets(line, sizeof(line), fileIn);
  j = atoi(line);
  fgets(line, sizeof(line), fileIn);
  //size_t length = strlen(line);
  A = stringToBigInteger(line);
  //if((myArr[0] = malloc(length +1))){
  //    strcpy(myArr[0], line);
  //}   
  
  fgets(line, sizeof(line), fileIn);
  i = atoi(line);
  fgets(line, sizeof(line), fileIn);
  B = stringToBigInteger(line);
  //length = strlen(line);
  //if((myArr[1] = malloc(length +1))){
  //  strcpy(myArr[1], line);
  //}
  //A = stringToBigInteger(myArr[0]);

  printBigInteger(fileOut, A);
  fprintf(fileOut, "\n");

  printBigInteger(fileOut, B);
  fprintf(fileOut, "\n");
  
  C = newBigInteger();
  
  add(C, A, B);
  printBigInteger(fileOut, C);
  fprintf(fileOut, "\n");
  
  subtract(C, A, B);
  printBigInteger(fileOut, C);
  fprintf(fileOut, "\n");

  subtract(C, A, A);
  printBigInteger(fileOut, C);
  fprintf(fileOut, "\n");

  D = sum( A, A);

  add(D, D, A); // D = 3A

  E = sum( B, B); // E = 2B
  
  subtract(C, D, E); // C = 3A - 2B
  printBigInteger(fileOut, C);
  fprintf(fileOut, "\n");

  multiply(C, A, B); // C = AB
  printBigInteger(fileOut, C);
  fprintf(fileOut, "\n");
  
  multiply(D, A, A); // D = A^2
  printBigInteger(fileOut, D);
  fprintf(fileOut, "\n");
  
  multiply(E, B, B); // E = B^2
  printBigInteger(fileOut, D);
  fprintf(fileOut, "\n");

  multiply(D, D, D); // D = A^4
  multiply(E, E, E); // E = B^4
  multiply(E, E, B); // E = B^5
  
  for( i = 0; i <15; i++){
    if( i < 8){
      add(D, D, D);
    }
    add(E, E, E);
  }		       
  add(C, D, E);

  printBigInteger(fileOut, C);
  
  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);
  freeBigInteger(&E);
  



  return(EXIT_SUCCESS);
}
