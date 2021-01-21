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
Graph newGraph(int n){
  int sizeFixed = n+1;
  int i;
  Graph G = malloc(sizeof(GraphObj));
  G->L = malloc((sizeFixed)*sizeof(List));
  G->color = malloc(sizeFixed*sizeof(int));
  G->parents = malloc(sizeFixed*sizeof(int));
  G->distance = malloc(sizeFixed*sizeof(int));
  G->order = n;
  G->size = 0;
  G->source = NIL;
  for( i = 1; i <= sizeFixed; i++){
    G->L[i]= newList();
  }
  return(G);

}

void freeGraph(Graph* pG){
  int i;
  if(pG !=NULL && *pL!=NULL){
    for( i = 0; i<= (G->order + 1); i++){
      free(G->L[i]);
      free(G->color[i]);
      free(G->parents[i]);
    }
    G->size = 0;
    G->source = 0;
    G->order = 0;
    free(*pG);
    *pG = NULL;
  }

}

// Access funtions-------------------------------------------------
int getOrder(Graph G){
  return(G->order);
}

int getSize(Graph G){
  return(G->size);
}
int getSource(Graph G){
  return(G->source)
}
int getParent(Graph G, int u){
  if( u <= getOrder(G) && u >= 1){
    return(G->parents[u]);
  }else{
    printf("Graph Error: getParent() called with invalid argument.\n");
    exit(EXIT_FAILURE);
  }
}

int getDist(Graph G, int u){
  if( u <= getOrder(G) && u >= 1){
    return(G->distance[u]);
  }else{
    printf("Graph Error: getDist() called with invalid argument.\n");
    exit(EXIT_FAILURE);
  }
}

void getPath(List L, Graph G, int u){
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: getPath() called on vertex outside of range.\n");
    exit(EXIT_FAILUR);
  }
  if( getSoure(G) == NIL){
    printf("Graph Error: getPath() called on before BFS was called on Graph.\n");
    exit(EXIT_FAILURE);
  }
  if( getSource(G) == u){
    appeand(L, getSource(G));
  } else if ( G->parents[u] == NIL){
    append(L, NIL);
  } else {
    getPath(L, G, G->parents[u]);
    append(L,u);
  }
}


// Manipulation procedures------------------------------------------------------
void makeNull(Graph G){
  int i;
  int size = getOrder(G)+1;
  G->size = 0;
  G->source = NIL;
  for( i = 1; i <= size; i++){
    clear(G->L[i]);
    G->color[i] = 0;
    G->parents[i] = NIL;
    G->distance[i] = INF;
  }
  
}

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
  
}

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
  if( length(G->L[u]) == 0){
    append(G->L[u], v);
  } else if( v < front(G->L[u]) ){
    prepend(G->L[u], v);
  } else if ( v > back(G->L[u])){
    append(G->L[u], v);
  } else {
    moveFront(G->L[u]);
    for( i = 0;  i <= length(G->L[u]); i++){
      moveNext(G->L[u]);
      if( v < get(G->L[u])){
        insertBefore(G->L[u], v);
        break;
      }
    }
  }
}

void BFS(Graph G, int s){
  int size = getOrder(G)+1;
  int i;
  int x, y;
  List L = newList();
  for( i = 1; i <= sizeFixed; i++){
    G->color[i] = WHITE;
    G->parents[i]= NIL;
    G->distance[i] = INF;
  }
  G->color[s] = GRAY;
  G->distance[s] = 0;
  G->parents[s]  = NIL;
  prepend(L, s);
  while( L !=NULL){
    x = front(L);
    deleteFront(L);
    moveFront(G->L[x]);
    for( i = 1; i <= length(G->L[x]); y++){
      y = get(G->L[x]);
      moveNext(G->L[x]);
      if( G->color[y] == WHITE){
	G->color[y] = GRAY;
	G->distance[y] = (G->distance[x]+1);
	G->parents[y] = x;
	append(L, y);
      }
    }
    G->color[x] = BLACK;
  }
}


// Other operations---------------------------------------------

void printGraph(FILE* out, Graph G){


}
