//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              1/20/2021
//
//              List.h
// Assignment: Pa2: lex list
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Header file for graph ADT
//----------------------------------------------------------------------------


#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"
#include <stdio.h>
#define INF -8
#define NIL -1
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define UNDEF -1
// Export type----------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors---------------------------------------------------
Graph newGraph(int n);               // Creates and returns a new graph with vertices n.
void freeGraph(Graph* pG);           // Frees all heap memory associated with *pG and sets
                                     // *pG to NULL.

// Access functions-----------------------------------------------------------
int getOrder(Graph G);               // returns the Order of Graph G.
int getSize(Graph G);                // returns the Size of Graph G.
int getSource(Graph G);              // returns the source vertex most recently used in BFS() 
                                     // or NIL if BFS() has not been called
int getParent(Graph G, int u);       // returns the parent of the vertex
                                     // Pre: 1 <= u <= getOrder(G) 
int getDist(Graph G, int u);         // returns the distance from the most recent BFS source to vertex u
                                     // Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);// appends to the List L the vertices of a shortest path in G
                                     // from source to u or appends to L the value NIL if no such path exists
                                     // Pre: 1 <= u <= getOrder(G) and getSource(G) !=NIL
int getDiscover(Graph G, int u);    // returns the discovery time of the vertex u if DFS has ran else returns undefined
                                     // Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u);       // returns the finish time of the vertex u if DFS has raan else returns undfined
                                     // Pre: 1 <= u <= n = getOrder(G)
// Manipulation procedures----------------------------------------------------
void makeNull (Graph G);             // deletes all edges of G restoring it to its original state
void addEdge (Graph G, int u, int v);// inserts a new edge joining u to v. Pre: 1 <= (u and v) <= getOrder(G)
void addArc (Graph G, int u, int v); // inserts a new directed edge from u to v. Pre: 1 <= (u and v) <= getOrder(G)
void BFS(Graph G, int s);            // runs the BFS algorithm on Graph G with source s, setting the color, distance
                                     // parent and source fields of G accordingly
void DFS(Graph G, List s);           // runs the DFS algorithm on Graph G and using List s to define the search order and
                                     // function as a stack  to store the vertices 
                                     // Pre: length(S) == getOrder(G)
// Other operations-----------------------------------------------------------
Graph transpose(Graph G);            // returns a reference to a new graph object representing the transpose of G
Graph copyGraph(Graph G);            // returns a reference to a new graph that is a copy of G.
void printGraph(FILE* out, Graph G); // prints the adjacency list representation of G to the file.


#endif
