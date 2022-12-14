//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              
//
//             FindPath.c
// Assignment: Pa3: Breadth first search
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  reads in input from a file and uses the Graph ADT to find SSSP
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


#define MAX_LEN 10000

int main(int argc, char* argv[]){
  
  FILE *fileIn, *fileOut;
  List myList = newList();
  char line[MAX_LEN];
  int first, second;
  char *split = " ";
  int x, i, j, y;
  if( argc != 3){
    printf("Error: too few arguments.\n");
    exit(1);
  }
  fileIn = fopen(argv[1], "r");
  fileOut = fopen(argv[2], "w");
 
  if( fileIn == NULL){
   printf("Unable to open file %s.\n", argv[1]);
   exit(1);
  }
  if( fileOut == NULL){
    printf("Unable to open file %s.\n", argv[2]);
    exit(1);
  }
  fgets( line, sizeof(line), fileIn);
  Graph myGraph = newGraph( atoi( line ));
  for( i = 1; i<= atoi(line); i++){
    append(myList, i);
  }
  while( fgets( line, sizeof(line), fileIn)){
    if( !strncmp(line, "0 0", 3)){
      break;
    }
    first = atoi( strtok(line, split));
    second = atoi( strtok(NULL, split));
    addArc( myGraph, first, second);
    // fprintf( stdout, " created arc from %d to %d\n", first , second);
  }
  
  fprintf(fileOut,"Adjacency list representation of G:\n");
  printGraph(fileOut, myGraph);
  Graph myGraphT = transpose(myGraph);
  DFS( myGraph, myList);
  //fprintf(stdout, "made it out of first DFS.\n");
  DFS( myGraphT, myList);
  //fprintf(stdout, "made it out of second DFS.\n");
  x = 0;
  for( i = 1; i <= length(myList); i++){
    if( getParent(myGraphT, i) == NIL){
      x++;
    }
  }
  fprintf(fileOut,"\nG contains %d strongly connected components:\n", x);
  i = 0;
  y = 0;
  //printList(fileOut, myList);
  //  fprintf(fileOut, "\n");
  moveBack(myList);
  //fprintf(stdout,"made it into strongly connected loop\n");
  while( i != x){
    if( getParent(myGraphT, get(myList)) == NIL){
      i++;
      //printf(" found %d\n", get(myList));
      fprintf(fileOut,"Component %d: %d", i, get(myList));
      if( length(myList) != 1 ){
	moveNext(myList);
      
	for( j = 0; j < y; j++){
	  fprintf(fileOut," %d", get(myList));
	  moveNext(myList);
	}
	fprintf(fileOut, "\n");
	j = 0;
	while( j != 1){
	  if( getParent(myGraphT, back(myList)) == NIL){
	    j++;
	  }
	  if( back(myList) != front(myList)){
	    deleteBack(myList);
	  }
	}
	
	y = 0;
	moveBack(myList);
      }else{ fprintf(fileOut, "\n");}
    }else{
      y++;
      if( get(myList) != front(myList)){
	movePrev(myList);
      }
    }
  }

  freeGraph(&myGraph);
  freeGraph(&myGraphT);
  freeList(&myList);

  return 0;
}
