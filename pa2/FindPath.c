//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              1/20/2021
//
//             FindPath.c
// Assignment: Pa2: Breadth first search
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
  int x;
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
  while( fgets( line, sizeof(line), fileIn)){
    if( !strncmp(line, "0 0", 3)){
      break;
    }
    first = atoi( strtok(line, split));
    second = atoi( strtok(NULL, split));
    addEdge( myGraph, first, second);
  }

  printGraph(fileOut, myGraph);

  while( fgets( line, sizeof(line), fileIn)){
    if( !strncmp(line, "0 0", 3)){
      break;
    }
    first = atoi ( strtok(line, split));
    second = atoi ( strtok(NULL, split));
    BFS( myGraph, first);
    getPath( myList, myGraph, second);
    x = getDist( myGraph, second);
    if( x == INF){
      fprintf(fileOut, "\nThe distance from %d to %d is infinity\n No %d-%d path exists\n", first, second, first, second);
      
    }else{
      fprintf(fileOut, "\nThe distance from %d to %d is %d\nA shortest %d-%d path is: ", first, second, x, first, second);
      printList(fileOut, myList);
      clear(myList);
    }
  }
  fclose(fileIn);
  fclose(fileOut);
  freeGraph(&myGraph);
  freeList(&myList);

  return 0;
}
