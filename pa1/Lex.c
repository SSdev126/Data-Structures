//-----------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              1/14/2021
//
//              Lex.C
// Assignment: Pa1: lex List
//             CSE 101, Indroduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description: This program creates a List that stores the Lexographical order
//              of the input strings.
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 1000

int main(int argc, char* argv[]){
  
  FILE *fileIn, *fileOut;
  char line[MAX_LEN];
  
  char  *myArr[MAX_LEN] = { NULL};
  int previousElement = 0;
  int i = 0;
  int j = 0;
  List myList = newList();
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

  while( fgets(line, sizeof(line), fileIn)){ // reading the file in until fgets fails
    size_t length = strlen(line);            // getting the length of each line so we
    if(line[length-1] == '\n'){              // know how much memory to malloc
      line[--length] = 0;
    }
    if(( myArr[i] =  malloc(length + 1 ))){  // make sure we get the memory we need
      strcpy(myArr[i], line);                // copy our line into the array 
    }

    if( i == 0){                             // if i hasn't be incremented the list is empty
      append(myList, i);
    } else{
      moveFront(myList);                     // make sure the index is intialized 
      
      if( strcmp(myArr[i], myArr[front(myList)]) <= 0 ){ // if our item is the same or
	                                                 // before the front it becomes the new front
	prepend(myList, i);
	
      } else if ( strcmp(myArr[i], myArr[back(myList)]) > 0){ // if our item comes after our back
	                                                      // it becomes our new back
	append(myList, i);
	
      } else{
	previousElement = front(myList); // grab the front of the list 
	moveNext(myList);                // increment the index cause it pointing to the front
	                                 // and so is previousElement
	for ( j = 0; j < i; j++){        // search the list for a spot where myArr[i] goes between entries 
	  if ( strcmp(myArr[i], myArr[get(myList)]) <= 0 && strcmp(myArr[i], myArr[previousElement]) > 0 ){ 
	    insertBefore(myList, i);
	    break;
	    
	  }
	  previousElement = get(myList); // save the last thing we checked
	  moveNext(myList);              // increment the index to check the rest
	}
      }		       
    }
    i++;                                 //increment i cause i will be the number of entries total
  }
  moveFront(myList);                     // reset the index cause we're about to read through the whole list
  for(j = 0; j < (length(myList) ); j++ ){
    fprintf(fileOut, "%s\n", myArr[get(myList)]); // save list elements to output file
    moveNext(myList);                    // increment index
  }
  fclose(fileIn);                        // close our files
  fclose(fileOut);
  freeList(&myList);                     // free our lists allocated memory
  for(j = 0; j <= i; j++){               // increment through our array freeing each elements memory
    free(myArr[j]);
  }
 
  return(0);
}
