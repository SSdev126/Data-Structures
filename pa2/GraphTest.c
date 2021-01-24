//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              1/20/2021
//
//             GraphTest.c
// Assignment: Pa2: Breadth first search
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Tests all Graph ADT functions in isolation.
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main (){
  int i, n = 35;
  List A = newList();
  Graph G = NULL;
  G = newGraph(n); 
  // building the graph
  for( i = 1; i <= n; i++){
    if( i%7!=0 ) addEdge(G, i , i+1);
    if ( i <= 28 ) addEdge(G, i , i+7);

  }
  addEdge(G, 9, 31);
  addEdge(G, 17, 13);
  addEdge(G, 14, 33);
  addArc(G, 6, 9);
  addArc(G, 12, 6);
  addArc(G, 7, 13);
  // testing BFS and paths 
  printGraph(stdout, G);
  BFS( G, 7);
  getPath(A, G, 20);
  printList( stdout, A);
  printf("\n");
  BFS( G, 6);
  getPath(A, G, 31);
  printList( stdout, A);
  printf("\n");
  // testing access functions and makeNull
  printf("parent of 7 is %d (should be 6)\n", getParent( G, 7));

  printf("Graph Order is %d (should be 35)\n", getOrder(G));
  printf("size of Graph is %d \n", getSize(G));
  printf("dist from 6 to 31 is %d (should be 2)\n", getDist(G, 31));
  printf("source of graph is %d (should be 6)\n", getSource(G));
  makeNull(G);
  printf("size of Graph after makeNull is %d (should be 0 )\n", getSize(G));
  freeGraph(&G);
  freeList(&A);
  

  return(0);
}
