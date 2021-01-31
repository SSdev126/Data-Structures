//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              
//
//             GraphTest.c
// Assignment: Pa3: Depth first search
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  tests all Graph.c functions 
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
  int i, n = 10;
  List myList = newList();
  Graph myGraph = newGraph(n);
  Graph myGraphT = NULL, GraphCopy = NULL;

  for( i = 1; i<=n; i++){
    append(myList, i);
    if((i +1 ) <= n ){
      if( i != 8 && i != 9){
      addArc(myGraph, i, (i+1));
      }
      if( (i%2) == 0 ){
	addEdge(myGraph, i, 9);
      }else {
	addArc(myGraph, 9, i);
      }
    }
  }
  
  moveFront(myList);
  addArc(myGraph, 8, 1);
  printGraph(stdout, myGraph);
  fprintf(stdout, "Graph size is %d.\n", getSize(myGraph));
  myGraphT = transpose(myGraph);
  fprintf(stdout, "Transposed Graph size is %d.\n", getSize(myGraphT)); 
  fprintf(stdout,"\n");
  printGraph(stdout, myGraphT);
  fprintf(stdout,"\n");

  GraphCopy = copyGraph(myGraphT);
  fprintf(stdout, "Copy of transposed Graph's size is %d.\n", getSize(GraphCopy));
  printGraph(stdout, GraphCopy);
  freeGraph(&myGraphT);
  myGraphT = transpose(GraphCopy);
  fprintf(stdout, " transpose of transposed Graph's size is %d.\n", getSize(myGraphT));
  printGraph(stdout, myGraphT);
  fprintf(stdout,"\n");
  printGraph(stdout, myGraph);
  fprintf(stdout,"\n");
  DFS(myGraph, myList);
  printList(stdout, myList);
  fprintf(stdout, "\n");
  DFS(GraphCopy, myList);
  fprintf(stdout, "x: Discovery  Finish Time Parent \n");
  for(i = 1; i<=n; i++){
    fprintf(stdout, "%d:    %2d          %2d         %2d\n", i, getDiscover(myGraph, i), getFinish(myGraph, i), getParent(myGraph, i));
  }
  fprintf(stdout, "\n");

  fprintf(stdout, "x: Discovery  Finish Time Parent \n");

  for(i = 1; i<=n; i++){
    fprintf(stdout, "%d:    %2d          %2d         %2d\n", i, getDiscover(GraphCopy, i), getFinish(GraphCopy, i), getParent(GraphCopy, i));
  }
  fprintf(stdout, "\n");

  DFS(myGraph, myList);
  printList(stdout, myList);
  fprintf(stdout, "\n");

  fprintf(stdout, "x: Discovery  Finish Time Parent \n");
  for(i = 1; i<=n; i++){
    fprintf(stdout, "%d:    %2d          %2d         %2d\n", i, getDiscover(myGraph, i), getFinish(myGraph, i), getParent(myGraph, i));
  }
  fprintf(stdout, "\n");

  
  freeList(&myList);
  freeGraph(&myGraph);
  freeGraph(&GraphCopy);
  freeGraph(&myGraphT);



  return 0; 
}
