//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              3/03/2021
//
//              BigIntegerTest.c
// Assignment: Pa7:  BigIntegers
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  unit test for BigInteger ADT PA7
//----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

     
int main(){
  BigInteger A, B, C, S, D, E, F, G, H, P, T;
  char str1[] = "2276000000000000000513164964964";
  char str2[] = "-999999999999999999999";
  char str3[] = "11111111111111111111111111111111111";
  char str4[] = "999999999999999999999";
  A = stringToBigInteger(str1);
  printf("A = ");
  printBigInteger(stdout, A);
  printf("\n");

  B = stringToBigInteger(str2);
  printf("B = ");
  printBigInteger(stdout, B);
  printf("\n");
  printf("the sign of B is %d\n", sign(B));
  printf("A is bigger than B: %s\n", compare(A,B)?"true":"false");
  C = stringToBigInteger(str3);
  printf("C = ");
  printBigInteger(stdout, C);
  printf("\n");

  D = stringToBigInteger(str4);
  printf("D = ");
  printBigInteger(stdout, D);
  printf("\n");
  
  printf("C equals B %s\n", equals(C, B)?"true":"false");
  
  E = copy(D);
  printf("E = ");
  printBigInteger(stdout, E);
  printf("\n");
  negate(E);
  printf(" E negated = ");
  printBigInteger(stdout, E);
  printf("\n");
  printf("E equals B %s\n", equals(E,B)?"true":"false");

  F = newBigInteger();
  add(F, B, D);
  printf("B + D = ");
  printBigInteger(stdout, F);
  printf("\n");

  G = sum(E, B);
  printf("B + E = ");
  printBigInteger(stdout, G);
  printf("\n");

  H = newBigInteger();
  subtract(H, C, B);
  printf("C - B = ");
  printBigInteger(stdout, H);
  printf("\n");

  P = diff(B, D);
  printf("B - D = ");
  printBigInteger(stdout, P);
  printf("\n");
  
  T = newBigInteger();
  multiply(T, B, C);
  printf("B*C = ");
  printBigInteger(stdout, T);
  printf("\n");

  S = prod(A, C);
  printf("A*C = ");
  printBigInteger(stdout, S);
  printf("\n");

  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);
  freeBigInteger(&E);
  freeBigInteger(&F);
  freeBigInteger(&G);
  freeBigInteger(&H);
  freeBigInteger(&P);
  freeBigInteger(&T);
  freeBigInteger(&S);


  return(EXIT_SUCCESS);
}
