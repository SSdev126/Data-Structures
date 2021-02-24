//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//
//
//             Dictionary.c
// Assignment: Pa6: RB tree
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  Implementation file for list ADT
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"



// Structs -------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
  KEY_TYPE key;
  VAL_TYPE data;
  int color;
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
  N->color = 0;
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

// PostOrderDelete
// helper function for freeDictionary
void PostOrderDelete(Dictionary D, Node x){
  if ( x != D->NIL && D->size != 0){
    //if(x->left !=  D->NIL){
      PostOrderDelete( D, x->left);
      //}
    //if(x->right != D->NIL){
      PostOrderDelete( D, x->right);
      //}

    freeNode(&x);
    D->size--;
    x = NULL;
  }
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
  if(pD != NULL && *pD != NULL){
    PostOrderDelete(*pD, (*pD)->root);
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
    //fprintf(stdout, "about to leave lookup\n");
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

// LeftRotate
// helper function for insert fixup
void rotateLeft(Dictionary D, Node x){

  Node y = x->right;
  x->right = y->left;
  if( y->left != D->NIL){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if( x->parent == D->NIL){
    D->root = y;
  }else if ( x == x->parent->left){
    x->parent->left = y;
  }else{
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

//RightRotate
// helper function for insert fixup
void rotateRight(Dictionary D, Node x){
  Node y = x->left;
  
  x->left = y->right;
  
  if (y->right != D->NIL){
    y->right->parent = x;
  }
  
  y->parent = x->parent;
  if( x->parent == D->NIL){
    D->root = y;
  }else if ( x == x->parent->right){
    x->parent->right = y;
  }else{
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

// insertFixup()
// helper funtion for insert that handles most the RB tree logic
void insertFixUp(Dictionary D, Node z){
  while( z->parent->color == 1){
    if (z->parent == z->parent->parent->left){
     Node  y = z->parent->parent->right;
      if( y->color == 1){
	z->parent->color = 0;
	y->color = 0;
	z->parent->parent->color = 1;
	z = z->parent->parent;
      }else{
	if( z == z->parent->right){
	  z = z->parent;
	  rotateLeft(D, z);
	}
	z->parent->color = 0;
	z->parent->parent->color = 1;
	rotateRight(D, z->parent->parent);
      }
      
    }else{
    Node y = z->parent->parent->left;
      if(y->color == 1){
	z->parent->color = 0;
	y->color = 0;
	z->parent->parent->color = 1;
	z = z->parent->parent;
      }else{
	if( z == z->parent->left){
	  z = z->parent;
	  rotateRight(D, z);
	}
	z->parent->color = 0;
	z->parent->parent->color = 1;
	rotateLeft(D, z->parent->parent);
      }
    }
  }
  D->root->color = 0;
}

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
  if( D == NULL){
    printf("Dictionary Error: calling insert() on NULL reference.\n");
    return;
  }
 
  if( getUnique(D) == 1 && lookup(D, k) != VAL_UNDEF){
    return;
  }
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
  z->parent = y;
  if (y == D->NIL){
    D->root = z;  // empty case
  }else if(KEY_CMP(z->key, y->key) < 0){
    y->left = z;
  }else{
    y->right = z;
  }
  z->color = 1;
  D->size++;
  insertFixUp(D, z);

}

// Transplant()
// helper function for delete
void Transplant( Dictionary D, Node u , Node v){
  if( u->parent == D->NIL){
    D->root = v;
  }else if( u == u->parent->left){
    u->parent->left = v;
  }else{
    u->parent->right = v;
  }
  v->parent = u->parent;
  
}

// deleteFixUp()
// helper function for delete that helps maintain RBT rules.
void deleteFixUp(Dictionary D, Node x){
  //printf( "made it to deleteFixUp\n");
  while( x != D->root && x->color == 0){
    //printf("checking keys\n");
    //printf(""KEY_FORMAT"\n", x->parent->key);
    //printf(""KEY_FORMAT"\n", x->parent->left->key);
    //printf( "about to check x->parent->left\n");
    if ( x->parent->left != NULL){
      //printf( "about to check x->parent->left\n");
      if ( x == x->parent->left){
	//printf( "before if temp\n");
	Node temp = x->parent->right;
	if( temp != D->NIL){
	  if( temp->color == 1){
	    temp->color = 0;
	    x->parent->color = 1;
	    rotateLeft(D, x->parent);
	    temp = x->parent->right;
	  }
	  if ( temp->left->color == 0 && temp->right->color == 0){
	    temp->color = 1;
	    x = x->parent;
	  }else {
	    if ( temp->right->color == 0){
	      temp->left->color = 0;
	      temp->color = 1;
	      rotateRight(D, temp);
	      temp = x->parent->right;
	    }
	    temp->color = x->parent->color;
	    x->parent->color = 0;
	    temp->right->color = 0;
	    rotateLeft(D, x->parent);
	    x = D->root;
	  }
	}
      }
    }else{
      //printf("before else temp\n");
      Node temp = x->parent->left;
      if ( temp != D->NIL){
	if ( temp->color == 1){
	  temp->color = 0;
	  x->parent->color = 1;
	  rotateRight(D, x->parent);
	  temp = x->parent->left;
	}
	if ( temp->right->color == 0 && temp->left->color == 0){
	  temp->color = 1;
	  x = x->parent;
	} else{
	  if ( temp->left->color == 0 ){
	    temp->right->color = 0;
	    temp->color = 1;
	    rotateLeft(D, temp);
	    temp = x->parent->left;
	  }
	  temp->color = x->parent->color;
	  x->parent->color = 0;
	  temp->left->color = 0;
	  rotateRight(D, x->parent);
	  x = D->root;
	}
      }
    }
  }
  x->color = 0;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k) != VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
  //printf("made it into delete\n");
  if( lookup(D, k) != VAL_UNDEF){
    Node temp = D->root;
    Node x;
    temp = TreeSearch( temp, k);
    int originalColor = temp->color;
    if (temp == D->cursor){
      D->cursor = D->NIL;
    }
    if ( temp->left == D->NIL){
      x = temp->right;
      Transplant(D, temp, temp->right);
      //freeNode(&temp);
    }else if (temp->right == D->NIL){
      x = temp->right;
      Transplant(D, temp, temp->left);
      //freeNode(&temp);
    }else {
      Node y = temp->right;
      y = TreeMinimum(y);
      originalColor = y->color;
      x = y->right;
      if( y->parent == temp){
	x->parent = y;
      }else{
        Transplant(D, y, y->right);
        y->right = temp->right;
        y->right->parent = y;
      }
      Transplant( D, temp, y);
      y->left = temp->left;
      y->left->parent = y;
      y->color = temp->color;
      //freeNode(&temp);
    }
    if( originalColor == 0){
      //printf("goint into deletefixup\n");
      deleteFixUp(D, x);
    }
    freeNode(&temp);
    D->size--;
  }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs
void makeEmpty(Dictionary D){
  if(D->size != 0){
    PostOrderDelete(D ,D->root);
    D->size = 0;
    D->cursor = D->NIL;
  }
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
    fprintf( fileOut, ""KEY_FORMAT"\n", x->key);
    InOrderTreeWalk( fileOut, x->right);

  }

}

void PreOrderTreeWalk(FILE* fileOut, Node x){
  if ( fileOut == NULL){ return;}
  if ( x->key != KEY_UNDEF){
    fprintf( fileOut, ""KEY_FORMAT"\n", x->key);
    PreOrderTreeWalk( fileOut, x->left);
    PreOrderTreeWalk( fileOut, x->right);
  }
}

void PostOrderTreeWalk(FILE* fileOut, Node x){
  if ( fileOut == NULL){ return;}
  if ( x->key != KEY_UNDEF){
    PostOrderTreeWalk(fileOut, x->left);
    PostOrderTreeWalk(fileOut, x->right);
    fprintf( fileOut, ""KEY_FORMAT"\n", x->key);
  }
}

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items seperated by a
// single space. The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D, const char* ord){
  if( out != NULL && D != NULL){
    int test = strcmp( ord, "post"); // in < post < pre
    Node temp = D->root;
    if(test < 0 ){
      fprintf(out, "******************************************************\n");
      fprintf(out, "IN-ORDER:\n******************************************************\n");
      InOrderTreeWalk(out, temp);
    }else if( test > 0 ){
      fprintf(out, "******************************************************\n");
      fprintf(out, "PRE-ORDER:\n******************************************************\n");
      PreOrderTreeWalk(out, temp);
    }else if( test == 0){
      fprintf(out, "******************************************************\n");
      fprintf(out, "POST-ORDER:\n******************************************************\n");
      PostOrderTreeWalk(out, temp);
    }
  }
}

