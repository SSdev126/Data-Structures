//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//              
//
//             Dictionary.c
// Assignment: Pa5: lex tree
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Implementation file for list ADT
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

// structs ------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
  KEY_TYPE key;
  VAL_TYPE data;
  struct NodeObj* parent;
  struct NodeObj* left;
  struct NodeObj* right;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private DictionaryObj
typedef struct DictionaryObj{
  Node root;
  Node NIL;
  Node cursor;
  int unique;
  int size;
} DictionaryObj;

// Constructors-Destructors --------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode( KEY_TYPE key, VAL_TYPE data){
  Node N = malloc(sizeof(NodeObj));
  N->parent = N->left = N->right = NULL;
  N->key = key;
  N->data = data;
  return(N);

}

// freeNode()
// Frees heap memory by setting everything to NULL
void freeNode(Node* pN){
  if( pN!=NULL && *pN!=NULL){
    free(*pN);
    *pN = NULL;
  }
}

// newDictionary()
// Creates a new empty Dictionary. if unique==false (0), then Dictionary
// will accept duplicate keys, i.e. distinct pairs  with identical keys. if
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted. In this case, the operation insert(D, k) will enforce the
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
  Dictionary D;
  D = malloc(sizeof(DictionaryObj));
  D->NIL = newNode(KEY_UNDEF, VAL_UNDEF);
  D->root = D->NIL;
  D->cursor = D->NIL;
  D->unique = unique;
  D->size = 0;
  return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
  if(pD != NULL && *pD != NULL){
    makeEmpty(*pD);
    freeNode(&((*pD)->NIL));
    free(*pD);
    *pD = NULL;
  }
}


// Access functions ----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
  if( D != NULL){
    return D->size;
  } else {
    printf("Dictionary Error: calling size() on NULL reference.\n");
    return -1;
  }

}

// getUnique()
// Returns ture (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
  //fprintf(stdout, "made it to getUnique\n");
  if( D != NULL){
    if( D->unique != 0){
      return 1;
    }else{
      return 0;
    }

  } else {
    printf("Dictionary Error: calling getUnique() on NULL reference.\n");
    return -1;
  }

}

// TreeSearch()
// helper function for lookup that finds the node with key k
Node TreeSearch( Node x, KEY_TYPE k){
  if(x->key == KEY_UNDEF){
    return x;
  }
  int temp = KEY_CMP( k, x->key);
  if( temp == 0){
    return x;
  } else if( temp > 0){
    return TreeSearch( x->right, k);
  } else{
    return TreeSearch( x->left, k);
  }
  
}


// lookup()
// if Dictionary D contains a (key, value) pair matches k ( i.e. if
// KEY_CMP(key, k) == 0 ), then returns value. if D contains no such pair,
// then returns VAL_UNDEF
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
  //fprintf(stdout, "made it to lookup\n");
  if( D != NULL){
    Node temp = D->root;
    //fprintf(stdout, "made it to TreeSearch\n");
     temp = TreeSearch( temp, k);
     // fprintf(stdout, "about to leave lookup\n");
    return temp->data;
  } else {
    printf("Dictionary Error: calling lookup() on NULL reference.\n");
    return VAL_UNDEF;
  }
  
}

Node TreeMinimum(Node x){
  while( x->left->key != KEY_UNDEF){
    x = x->left;
  }
  return x;
}


Node TreeMaximum(Node x){
  while( x->right->key != KEY_UNDEF){
    x = x->right;
  }
  return x;
}

// Manipulation procedures ----------------------------------------------------

// insert()
// insert the pair (k,v) into Dictionary D.
// if getUnique(D) is false (0), then there are no preconditions.
// if getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
  if( D == NULL){
    printf("Dictionary Error: calling insert() on NULL reference.\n");
    return;
  }
  //fprintf( stdout, "hmmmmm\n");
  if( getUnique(D) == 1 && lookup(D, k) != VAL_UNDEF){
    //fprintf( stdout, "MMMmM\n");
    return;
  } 
  //fprintf( stdout, " made it into insertion loop\n");
  Node y = D->NIL;
  Node x = D->root;
  Node z = newNode(k,v);
  z->left = z->right = z->parent = D->NIL;
  while( x != D->NIL){
    y = x;
    if ( KEY_CMP(z->key, x->key) < 0){
      x = x->left;
      }else{
      x = x->right;
    }
  }
  //fprintf(stdout, "made it out of insertion position loop\n");
  z->parent = y;
  if (y == D->NIL){
    D->root = z;  // empty case
  }else if(KEY_CMP(z->key, y->key) < 0){
    y->left = z;
  }else{
    y->right = z;
  }
  D->size++;
  
}
// helper function for delete
void Transplant( Dictionary D, Node u , Node v){
  if( u->parent == D->NIL){
    D->root = v;
  }else if( u == u->parent->left){
    u->parent->left = v;
  }else{
    u->parent->right = v;
  }
  if( v != D->NIL){
    v->parent = u->parent;
  }
  
}
// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k) != VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
  if( lookup(D, k) != VAL_UNDEF){
    Node temp = D->root;
      temp = TreeSearch( temp, k);
      if (temp == D->cursor){
	D->cursor = D->NIL;
      }
    if ( temp->left == D->NIL){
      Transplant(D, temp, temp->right);
      freeNode(&temp);
    }else if (temp->right == D->NIL){
      Transplant(D, temp, temp->left);
      freeNode(&temp);
    }else {
      Node y = temp->right;
	y = TreeMinimum(y);
      if( y->parent != temp){
	Transplant(D, y, y->right);
	y->right = temp->right;
	y->right->parent = y;
      }
      Transplant( D, temp, y);
      y->left = temp->left;
      y->left->parent = y;
      freeNode(&temp);
    }
    D->size--;
  }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs 
void makeEmpty(Dictionary D){
  while( D->size != 0){
    delete(D, D->root->key);
  }
  D->cursor = D->NIL;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operation KEY_CMP()), then returns the first
// value. if D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D){
  if( D->size == 0 ){
    return VAL_UNDEF;
  }else{
    Node temp = D->root;
   D->cursor = TreeMinimum(temp);
    return D->cursor->data;
  }
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the first key
// (as defined by the order operation KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
  if( D->size == 0){
    return VAL_UNDEF;
  }else{
    Node temp = D->root;
    D->cursor = TreeMaximum(temp);
    return D->cursor->data;
  }
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. if no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
  return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
  return D->cursor->data;
}
// TreeSuccessor is a helper function for next() that locates the next 
// highest key
Node TreeSuccessor(Node x){
  if( x->right->key != KEY_UNDEF){
    Node tempNode = x->right;
    return TreeMinimum(tempNode);
  }
  Node temp = x; 
  Node y = x->parent;
  while( y->key != KEY_UNDEF && temp == y->right){
    temp = y;
    y = y->parent;
  }
  return y;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, move to the next key in D (as defined by the
// order operation KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started and has not reached the last pair,
// ends the iterataion and returns VAL_UNDEF. if no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
  if(D->cursor == D->NIL){
    return VAL_UNDEF;
  }
  
  Node temp = D->cursor;
  temp  = TreeSuccessor(temp);
  D->cursor = temp;
  
  return temp->data;
}

// TreePredecessor()
// helper function for prev() that returns the node with the key before x 
Node TreePredecessor(Node x){
  if( x->left->key != KEY_UNDEF){
    Node tempNode = x->left;
    return TreeMaximum(tempNode);
  }
  Node temp = x, y = x->parent;
  while( y->key != KEY_UNDEF && temp == y->left){
    temp = y;
    y = y->parent;
  }
  return y;
}

// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. if no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D){
  if(D->cursor == D->NIL){
    return VAL_UNDEF;
  }
  Node temp = D->cursor;
  temp = TreePredecessor(temp);
  D->cursor = temp;
  return temp->data;
}

// other operations 

void InOrderTreeWalk(FILE* fileOut,Node x){
  if ( fileOut == NULL) { return;}
  if ( x->key != KEY_UNDEF){
    InOrderTreeWalk( fileOut, x->left);
    fprintf( fileOut, ""KEY_FORMAT"  "VAL_FORMAT"\n", x->key, x->data);
    InOrderTreeWalk( fileOut, x->right);
      
  }
  
}

void PreOrderTreeWalk(FILE* fileOut, Node x){
  if ( fileOut == NULL){ return;}
  if ( x->key != KEY_UNDEF){
    fprintf( fileOut, ""KEY_FORMAT"  "VAL_FORMAT"\n", x->key, x->data);
    PreOrderTreeWalk( fileOut, x->left);
    PreOrderTreeWalk( fileOut, x->right);
  }
}

void PostOrderTreeWalk(FILE* fileOut, Node x){
  if ( fileOut == NULL){ return;}
  if ( x->key != KEY_UNDEF){
    PostOrderTreeWalk(fileOut, x->left);
    PostOrderTreeWalk(fileOut, x->right);
    fprintf( fileOut, ""KEY_FORMAT" "VAL_FORMAT"\n", x->key, x->data);
  }
}

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items seperated by a 
// single space. The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
  if( out != NULL && D != NULL){
    Node temp = D->root;
    InOrderTreeWalk(out, temp);
  }
}
