//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              1/20/2021
//
//             Graph.c
// Assignment: Pa2: Breadth first search
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Implementation file for Graph ADT
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// structs-----------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
  List* L;
  int* color;
  int* parents;
  int* distance;
  int order;
  int size;
  int source;
} GraphObj;

// Constructors-Destructors-------------------------------------------------
// Creates and returns a new graph with vertices n.
Graph newGraph(int n){
  int sizeFixed = n + 1;
  int i;
  Graph G = malloc(sizeof( GraphObj));
  G->L = malloc(sizeFixed * ( 4 + sizeof( List )));
  G->color = malloc(sizeFixed *( 4 + sizeof( int )));
  G->parents = malloc(sizeFixed *(4 + sizeof( int)));
  G->distance = malloc(sizeFixed * ( 4 + sizeof( int)));
  G->order = n;
  G->size = 0;
  G->source = NIL;
  for( i = 0; i <= sizeFixed; i++){
    G->L[i] = newList();
  }
  return(G);

}
// Frees all heap memory associated with *pG and sets *pG to NULL.
void freeGraph(Graph* pG){
  int i;
  if(pG != NULL && *pG != NULL){
    for( i = 0; i <= ((*pG)->order + 1); i++){
      freeList(&((*pG)->L[i])); // freeing all the lists we made
    }
    freeList((*pG)->L);
    free((*pG)->L);
    free((*pG)->color);
    free((*pG)->parents);
    free((*pG)->distance);
    (*pG)->size = 0;
    (*pG)->source = 0;
    (*pG)->order = 0;
    free(*pG);
    *pG = NULL;
  }

}

// Access funtions-------------------------------------------------
// returns the Order of Graph G.
int getOrder(Graph G){
  return(G->order);
}
// returns the Size of Graph G.
int getSize(Graph G){
  return(G->size);
}
// returns the Source vertex most recently used in BFS()
// or NIL if BFS() has not been called
int getSource(Graph G){
  return(G->source);
}
// returns the parent of vertex u in breadth-First tree
// or NIL if BFS() hasn't been called. pre 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
  if( u <= getOrder(G) && u >= 1){
    return(G->parents[u]);
  }else{
    printf("Graph Error: getParent() called with invalid argument.\n");
    exit(EXIT_FAILURE);
  }
}
// returns the distance from the most recent BFS source to vertex u
// Pre: 1 <= u <= getOrder(G) 
int getDist(Graph G, int u){
  if( u <= getOrder(G) && u >= 1){
    return(G->distance[u]);
  }else{
    printf("Graph Error: getDist() called with invalid argument.\n");
    exit(EXIT_FAILURE);
  }
}
// apends to the List L the vertices of a shortest path in G from
// source to u or aappends to L the value NIL if no such path exists
// Pre: 1<= u <= getOrder(G) and getSource(G) != NIL
void getPath(List L, Graph G, int u){
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: getPath() called on vertex outside of range.\n");
    exit(EXIT_FAILURE);
  }
  if( getSource(G) == NIL){
    printf("Graph Error: getPath() called on before BFS was called on Graph.\n");
    exit(EXIT_FAILURE);
  }
  if( getSource(G) == u){
    append(L, getSource(G));
  } else if ( G->parents[u] == NIL){
    append(L, INF);
  } else {
    getPath(L, G, G->parents[u]);
    append(L,u);
  }
}


// Manipulation procedures------------------------------------------------------
// deletes all edges aof G restoring it to its originals state
void makeNull(Graph G){
  int i;
  G->source = NIL;
  for( i = 1; i <= getOrder(G) ; i++){
    clear(G->L[i]);
    G->color[i] = WHITE;
    G->parents[i] = NIL;
    G->distance[i] = INF;
  }
  G->size = 0;
}
// inserts a new edge joining u to v. Pre: 1 <= (u and v) <= getOrder(G)
void addEdge (Graph G, int u, int v){
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: addEdge called with out of range input u.\n");
    exit(EXIT_FAILURE);
  }
  if( v < 1 || v > getOrder(G)){
    printf("Graph Error: addEdge called with out of range input v.\n");
    exit(EXIT_FAILURE);
  } 
  if( u == v){
    return;
  }
  addArc(G, u, v); 
  addArc(G, v, u);
  G->size--; // using addArc twice rather than doing it all in here 
             // would give us too large of a size so we fix that here.
}
// inserts a new directed edge from u to v. Pre: 1 <= (u and v) <= getOrder(G)
void addArc (Graph G, int u, int v){
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: addArc called with out of range input u.\n");
    exit(EXIT_FAILURE);
  }
  if( v < 1 || v > getOrder(G)){
    printf("Graph Error: addArc called with out of range input v.\n");
    exit(EXIT_FAILURE);
  }
  int i;
  if( u == v){
    return;
  }
  if( length(G->L[u]) == 0){  // if its the first element just throw it in the list
    append(G->L[u], v);
  } else if( v < front(G->L[u]) ){ // maintaining order for least to greatest 
    prepend(G->L[u], v);           // if it's less than the front it needs to be the new front
  } else if ( v > back(G->L[u])){  // if it's greater than the back it needs to be the new back
    append(G->L[u], v);
  } else {                         // else we need to search through the list to find where v belongs
    moveFront(G->L[u]);
    for( i = 0;  i <= length(G->L[u]); i++){
      moveNext(G->L[u]);
      if( v < get(G->L[u])){
        insertBefore(G->L[u], v);
        break;
      }
    }
  }
  G->size++; // increase size
}
// runs the BFS algorithm on Graph G with source s, setting the color, distance,
// parents, and source fields of G accordingly
void BFS(Graph G, int s){
  int i;
  int x, y;
  List L = newList();
  for( i = 1; i <= getOrder(G); i++){ // set everything to its undiscovered state
    G->color[i] = WHITE;
    G->parents[i]= NIL;
    G->distance[i] = INF;
  }
  G->source = s; // discover our source element
  G->color[s] = GRAY;
  G->distance[s] = 0;
  G->parents[s]  = NIL;
  prepend(L, s);
  while( length(L) != 0){ // while there are still unexplored elements
    x = front(L);
    deleteFront(L); // dequeue
    moveFront(G->L[x]);
    for( i = 1; i <=(  length(G->L[x])); i++){ 
      y = get(G->L[x]);
      moveNext(G->L[x]);
      if( G->color[y] == WHITE){ // if it's white we discover it 
	G->color[y] = GRAY;
	G->distance[y] = (G->distance[x]+1);
	G->parents[y] = x;
	append(L, y); // enque
      }
    }
    G->color[x] = BLACK; // x has been fully explored
  }
  freeList(&L);
}


// Other operations---------------------------------------------
// prints the adjacency list representaation of G to the file.
void printGraph(FILE *out, Graph G){
  if( G == NULL ){
    printf("Graph Error: calling printGraph() on NULL Graph reference.\n");
    exit(EXIT_FAILURE);
  }
  int i;
  for( i = 1; i <= getOrder(G); i++){
    fprintf(out ,"%d: ", i);
    if( length( G->L[i]) != 0){
      printList(out, G->L[i]);
      }
    fprintf(out ,"\n");
    moveFront(G->L[i]);
  }

}
