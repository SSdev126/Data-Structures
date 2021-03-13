//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              3/03/2021
//
//              BigInteger.c
// Assignment: Pa7:  BigIntegers
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Header file for doubly linked list ADT
//----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "BigInteger.h"
#include "List.h"
#define POWER  9

// Structs
typedef struct BigIntegerObj{
  int sign;
  List ints;
  //int pwr;
} BigIntegerObj;




// Constructors-Destructors-------------------------------------------

// new BigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
  BigInteger B;
  B = malloc(sizeof(BigIntegerObj));
  B->sign = 0;
  //B->pwr = 0;
  B->ints = newList();
  return(B);
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
  freeList(&((*pN)->ints));
  (*pN)->sign = 0;
  free(*pN);
  *pN = NULL;
}


// Access functions --------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive and 0 if N is in the zero
// state.
int sign(BigInteger N){
  return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
  
  if( A->sign == B->sign){
    if(A->sign == 0){ return 0;}
    if(length(A->ints) > length(B->ints)){
      return 1;
    }else if(length(A->ints) < length(B->ints)){
      return -1;
    }
  }
  if( A->sign < B->sign ){
    return -1;
  }else if( A->sign > B->sign){
    return 1;
  }else{
    if(length(A->ints) !=0){
      moveFront(A->ints);
    }
    if(length(B->ints) != 0){
    moveFront(B->ints);
    }
    int a, b;
    while(index(A->ints) != length(A->ints) && index(B->ints) != length(B->ints) 
	  && index(A->ints) != -1 && index(B->ints) != -1){
      a = get(A->ints);
      b = get(B->ints);
      moveNext(A->ints);
      moveNext(B->ints);
      if( a > b){
	if( A->sign != -1){
	  return 1;
	}else{
	  return -1;
	}
      }else if ( a < b){
	if( B->sign != -1){
	  return -1;
	} else{
	  return 1;
	}
      }
    }
    return 0;
  }
}

// equals()
// Returns true (1) if A and B are equals, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
  //printf(" A sign: %d B sign: %d \n", A->sign, B->sign);
  if(A->sign != B->sign){
    return 0;
  }else{
    return ListEquals(A->ints, B->ints);
  }
}


// Manipulation procedures ------------------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
  N->sign = 0;
  if(length(N->ints) != 0 ){
    clear(N->ints);
  }
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate( BigInteger N){
  if (N->sign != 0){
    N->sign = N->sign * -1;
  }
}

// BigInteger Arithmetic operations ---------------------------------------------------


void carry(List L, int x){
  movePrev(L);
  if( x > 0){
    set(L, (get(L) + x));
  }else{
    set(L, (get(L) + x));
  }
  moveNext(L);
}
void removeZeroes(List L){
  if(length(L) > 0){

    moveFront(L);
    while(front(L) == 0){
      deleteFront(L);
      if(length(L) > 0){
        moveFront(L);
      }
    }
  }   
}

int normalize(List L){
  int oldIndex, tempIndex = index(L);
  oldIndex = tempIndex;
  moveBack(L);
  int newSign = 1;
  long div;
  long base = pow(10, POWER);
  while(index(L) != -1){
    if( index(L) != -1 && get(L) >= base){

        if(index(L) == 0 ){
	  div = get(L) / base;
          prepend(L, div);
          tempIndex++;
          set(L, (get(L) - (div*base)));
        }else{
	  div = get(L) / base;
          carry(L, div);
          set(L, (get(L) - (div*base)));
        }

    }else if(index(L) != -1 && get(L) < 0){

      while( get(L) < 0){

        if( index(L) == 0){

          while(index(L) != -1){

            set(L, (get(L)*-1));
            moveNext(L);
          }

          newSign = normalize(L);
          return -1;

        }else {
	  div = get(L) / base;

	  if( div == 0){

	    carry(L, -1);
	    set(L, (get(L) + base));
	  }else{
	    carry(L, div);
	    set(L,  (get(L) + (div*base)));
	  }
        }
      }
    }
    movePrev(L);
  }
  moveFront(L);
  if(length(L) > 0){
    //printf("tempIndex: %d\n", tempIndex);
  //moveFront(L)
  //if(front(L) == 0){
    while(get(L) == 0){
      deleteFront(L);
      if(oldIndex < tempIndex){
      tempIndex--;
      }
      if(length(L) > 0){
	moveFront(L);
      }
    }
  }
  //}
  if(length(L) >0 ){
    while(index(L) != tempIndex){ 
      
      moveNext(L);
    }
  }
  //printf("index at end of normalize: %d\n", index(L));
  if(length(L) == 0){
    newSign = 0;
  }
  //}
  //printList(stdout, L);
  //printf("\n");
  return newSign;
}




// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits (0,1,2,3,4,5,6,7,8,9)
// and an optional sign (+, -) prefix.
BigInteger stringToBigInteger(char* s){
  int i = 0, j = 0;
  LIST_ELEMENT temp = 0;
  int base = POWER;
  //printf("%s\n", s);
  char *tempStr = s;
  char tempChar;
  
  //printf(" in to string :%s\n", tempStr);
  int sign = 0, signCheck = 0;
  for(i = 0; i < strlen(s)-1; i++){
    if( i == 0){
      if( isdigit(*tempStr) == 0){
	if(*tempStr != '+' && *tempStr != '-'){
	  //printf("invalid input was %s\n", tempStr);
	   printf("Invalid input\n");
	  exit(EXIT_FAILURE);
	}else if(*tempStr == '-'){
	  
	  sign = -1;
	}else{
	  sign = 1;
	}
      }
    }else{
      if( isdigit(*tempStr) == 0){
	printf("invalid input was %s\n", tempStr);
	printf("Invalid input\n");
	exit(EXIT_FAILURE);
      }
    }
    tempStr++;
  }
  tempStr = s;
  //printf("atoi of temStr: %ld\n", temp);
  BigInteger B = newBigInteger();
  if ( sign != 0 ){
    tempStr++;
    signCheck = 1;
    B->sign = sign;
  }else {
    B->sign = 1;
  }
  for( i = (strlen(s)- 1 - signCheck) ; i > signCheck ; ){
    
    if( (i - (base )) >  signCheck){
      temp = 0;
      for( j = 0; j < base; j++){ 
	tempChar = tempStr[i];
	temp += ( atoi(&tempChar) *pow(10, j));
	//tempStr++;
	//printf("%c\n", tempChar);
	i--;
      }
      //fprintf(stdout, "temps%ld\n", temp);
      prepend(B->ints, temp); 
    }else{
      temp = 0;
      int k = i + 2;
      for( j = 0; j <= k; j++){
	//temp += (strtol(tempStr, &tempStr, 10))*pow(10, j));
	if( i >= 0) {
	tempChar = tempStr[i];
	temp += ( atoi(&tempChar) * pow(10, j));
	i--;
	}
	//tempStr++;
	//printf("%c\n", tempChar);
      }
      //fprintf(stdout, "temps:%ld\n", temp);
      prepend(B->ints, temp);
    }
  }
  printBigInteger(stdout, B);
  sign = normalize(B->ints);
  return B;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
  BigInteger B = newBigInteger();
  B->ints = copyList(N->ints);
  B->sign = N->sign;
  if(index(N->ints) != -1){
    moveFront(B->ints);
    while(index(B->ints) != index(N->ints)){
      moveNext(B->ints);
    }
  }
  return B;
}

void addition( BigInteger S, BigInteger A, BigInteger B){
  LIST_ELEMENT tempListElement;
  List tempA = A->ints , tempB = B->ints;
  //printf("made it to addition\n");
  while(index(tempA) != -1 || index(tempB) != -1){
    tempListElement = 0;
    if(index(tempA) != -1){
      //printf("%ld\n", get(tempA));
      tempListElement += get(tempA);
      movePrev(tempA);
    }
    if(index(tempB) != -1){
      //printf("%ld\n", get(tempB));
      tempListElement += get(tempB);
      movePrev(tempB);
    }
    //printf("%ld\n", tempListElement);
    prepend(S->ints, tempListElement);
  }
  S->sign = A->sign;
  removeZeroes(S->ints);
}

void sub( BigInteger D, BigInteger A, BigInteger B){
  LIST_ELEMENT tempListElement;
  //printf("made it to sub\n");
  while(index(A->ints) != -1 || index(B->ints) != -1){
    tempListElement = 0;
    if(index(A->ints) != -1){
      //printf("%ld\n", get(A->ints));
      tempListElement +=get(A->ints);
      movePrev(A->ints);
    }
    if(index(B->ints) != -1){
      //printf("%ld\n", get(B->ints));
      tempListElement -= get(B->ints);
      movePrev(B->ints);
    }
    //printf("%ld\n", tempListElement);
    prepend(D->ints , tempListElement);
  }
  
  removeZeroes(D->ints);
}

// add()
// Places the sum of A and B into the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
  BigInteger tempA = copy(A), tempB = copy(B);
  moveBack(tempA->ints);
  moveBack(tempB->ints);
  makeZero(S);
  if( tempA->sign == tempB->sign || tempA->sign == 0 || tempB->sign == 0){
    addition( S, tempA, tempB);
    
    normalize(S->ints);
  }else if( tempA->sign == -1){
    sub( S, tempB , tempA);
    S->sign = normalize(S->ints);
  }else{
    sub( S, tempA, tempB);
    S->sign = normalize(S->ints);
  }
  freeBigInteger(&tempA);
  freeBigInteger(&tempB);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
  
  BigInteger S = newBigInteger();
  
  moveBack(A->ints);
  moveBack(B->ints);
  if( A->sign == B->sign || A->sign == 0 || B->sign == 0){
    addition( S, A, B);
    normalize(S->ints);
  }else if( A->sign == -1){
    sub( S, B , A);
    S->sign = normalize(S->ints);
  }else{
    sub( S, A, B);
    S->sign = normalize(S->ints);
  }
  return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
  BigInteger tempA = copy(A), tempB = copy(B);
  moveBack(tempA->ints);
  moveBack(tempB->ints);
  makeZero(D);
  
  if( tempA->sign == tempB->sign || (tempA->sign == 0 && tempB->sign != -1) || tempB->sign == 0){
    sub(D, tempA, tempB);
    D->sign = normalize(D->ints);
  }else{
    addition( D, tempA, tempB);
    normalize(D->ints);
    D->sign = A->sign;
  }
  freeBigInteger(&tempA);
  freeBigInteger(&tempB);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff( BigInteger A, BigInteger B){
  BigInteger S = newBigInteger();
  moveBack(A->ints);
  moveBack(B->ints);
  int temp = compare(A, B);
  if( A->sign == B->sign || (A->sign == 0 && B->sign != -1) || B->sign == 0){
    sub(S, A, B);
    
    normalize(S->ints);
    S->sign = temp;
      
  }else{
    addition( S, A, B);
    normalize(S->ints);
    S->sign = A->sign;
  }
  return S;
}



void multi(BigInteger P, BigInteger A, BigInteger B){
  long tempListElement = 0;
  //long test;
  int firstPass = 0, sign = 1, i;
  //int growth = 0, preNormalizeLength, pass = 0;
  
  moveBack(A->ints);
  moveBack(B->ints);
  if(A->sign != B->sign){
    sign = -1;
  }
  //firstPass++;
  //for(i = length(A->ints)*length(B->ints); i >= 0; i--){
  //  prepend(P->ints, 0);
  //}
  moveBack(P->ints);
  if( A->sign != 0 && B->sign != 0){
    while(index(A->ints) != -1){
      if(get(A->ints) != 0){
	while(index(B->ints) != -1){
	  //printf("broke at A*B get\n");
	  tempListElement = (get(A->ints)) * get(B->ints);
	  //printf(" multi results: %ld x %ld = %ld\n", get(A->ints), get(B->ints), tempListElement);
	  if( firstPass == 0){
	    
	  prepend(P->ints, tempListElement); 
	  firstPass++;
	  //printBigInteger(stdout, P);
	  normalize(P->ints);
	  //printBigInteger(stdout, P);
	  movePrev(B->ints);
	  
	  }else{
	  set(P->ints, (get(P->ints) + tempListElement));
	  //printBigInteger(stdout, P);
	  normalize(P->ints);
	  //printBigInteger(stdout, P);
	  //printf("post normalize index: %d post normalize length: %d\n", index(P->ints));
	  movePrev(B->ints);
	  //if(preNormalizeLength < length(P->ints)){
	  //  growth = 1;
	  // }else{
	  //  growth = 0;
	  //}
	  if(index(P->ints) == 0  && index(B->ints) != -1){
	  //  for(i = 0; i <= index(B->ints)+1; i++){
	     prepend(P->ints, 0);
	  //    printf("made it to prepend loop\n\n");
	  
	  }
	  //}
	 
	  movePrev(P->ints);
	  // printf("inloop P index:%d P length: %d B index: %d\n", index(P->ints), length(P->ints), index(B->ints));
	  }
	}
      }
      
      //printf(" while loop: %d\n", (length(A->ints) -1 - index(A->ints)));
      moveBack(P->ints);
      moveBack(B->ints);
      movePrev(A->ints);
      // printf("A index: %d A length: %d\n", index(A->ints), length(A->ints));
      //printf("B index: %d B length: %d\n", index(B->ints), length(B->ints));
      //printf("P index: %d P length: %d\n", index(P->ints), length(P->ints));
      
      if( index(A->ints) != -1){
	//printf("P index: %d\n", index(P->ints));
	for( i = 0; i < length(A->ints)- 1 - index(A->ints); i++){ 
	  movePrev(P->ints);
	}
	//if(index(P->ints) - length(B->ints) <= 0){
	  //for(i = length(B->ints); i >=0; i--){
	    //prepend(P->ints, 0);
	    // }
	  //}
	//printf("B length: %d\nP index: %d\n", length(B->ints), index(P->ints));
	//while( index(P->ints) < length(B->ints)){
	//  prepend(P->ints, 0);
	  // printf("P length: %d \n", length(P->ints));  
	//}
	//printf("post length loop P index: %d\n", index(P->ints));
      }
    }
  } else{ 
    makeZero(P);
  }
  if(A->sign != 0 && B->sign != 0){
    P->sign = sign;
  }
  removeZeroes(P->ints);
}



// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
  BigInteger tempA = copy(A), tempB = copy(B);
  //moveBack(tempA->ints);
  //moveBack(tempB->ints);
  makeZero(P);
  multi( P, tempA, tempB);
  //printf("finished multi \n");
  //P->sign = normalize(P->ints);
  if(sign(A) != sign(B)){
    if(sign(A) == 0 || sign(B) == 0){
      P->sign = 0;
    } else {
      P->sign = -1;
    }
  }else{
    P->sign = 1;
  }
  freeBigInteger(&tempA);
  freeBigInteger(&tempB);
  

}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod( BigInteger A, BigInteger B){
  BigInteger P = newBigInteger();
  
  multi(P, A, B);
  //printf("finished multi \n");
  //P->sign = normalize(P->ints);
  
  if(sign(A) != sign(B)){
    if(sign(A) == 0 || sign(B) == 0){
      P->sign = 0;
    } else {
      P->sign = -1;
    }
  }else{
    P->sign = 1;
  }


  return P;

}

// Other operations ---------------------------------------------------------

// printBigInteger()
// Prints A base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
  if(length(N->ints) != 0){
    if(N->sign == -1){
      fprintf(out, "-");
    }
  
    printList(out, N->ints);
    
    fprintf(out, "\n");
  }else{
    fprintf(out, "0");
  }
}
