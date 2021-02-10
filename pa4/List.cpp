//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//
//
//             List.cpp
// Assignment: Pa4: The perfect shuffle
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  implimentation of List ADT.
//----------------------------------------------------------------------------

using namespace std;

#include "List.h"


// Private Constructor -------------------------------------------------------

// Node constructor
List::Node::Node(int x){
  data = x;
  next = prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List(){
  frontDummy = new Node(-1); // -1 and -6 are just values to check for
  backDummy = new Node(-6);  // to find if we're at the front or the back
                             // of the List
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// Copy constructor.
List::List( const List& L){
  // make the empty List
  frontDummy = new Node(-1);
  backDummy = new Node(-6);
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
  if( L.num_elements != 0){
    // load elements of L into this
    Node* N = L.frontDummy;
    N = N->next;
    Node* M = new Node(N->data);
    frontDummy->next = M;
    M->prev = frontDummy;
    afterCursor = M;
    while( N->next != L.backDummy ){
      N = N->next;
      M->next = new Node(N->data);
      M->next->prev = M;
      M = M->next;
      
      //this->insertBefore(N->data);
      //N = N->next;
    }
    M->next = backDummy;
    backDummy->prev = M;
    num_elements = L.num_elements;
  }
  
}
 
 

// Destructors
List::~List(){
  clear();
  delete frontDummy;
  delete backDummy;
}

// Access functions -----------------------------------------------------------
 
// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
  return num_elements == 0;
} 

// size() 
// Returns the size of this List.
int List::size(){
  return num_elements;
}

// position()
// returns the position of the cursor in this List. The value returned
// will be in the range 0 to size();
int List::position(){
  return pos_cursor;
}

// Manipulation procedures ------------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
  pos_cursor = 0;
}

// moveBack()
// Moves cursor to the position size() in this List.
void List::moveBack(){
  beforeCursor = backDummy->prev;
  afterCursor = backDummy;
  pos_cursor = num_elements;
}

// peekNext()
// Returns the element after the cursor
// pre: position() < size ()
int List::peekNext(){
  if( pos_cursor < num_elements){
    return afterCursor->data;
  }else{
    cerr << "List Error: calling peekNext() at end of list." << endl;
    return -1;
  }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
  if( pos_cursor > 0){
    return beforeCursor->data;
  }else{
    cerr << "List Error: calling peekPrev() at the front of list." << endl;
    return -1;
  }
}

// moveNext()
// Advances cursor to next higher position. returns the list element that
// was passed over.
// pre: position() < size()
int List::moveNext(){
  if( position() < size()){
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
  }else{
    cerr << "List Error: calling moveNext() at the end of list." << endl;
    return -1;
  }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position() > 0
int List::movePrev(){
  if( position() > 0){
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
  }else{
    cerr << "List Error: calling movePrev() at the front of list." << endl;
    return -1;
  }
}

// insertAfter()
// inserts x after cursor.
void List::insertAfter(int x){
  Node* N = new Node(x);
  
  afterCursor->prev = N;
  N->next = afterCursor;
  beforeCursor->next = N;
  N->prev = beforeCursor;
  afterCursor = N;
  num_elements++;
}

// insertBefore()
// inserts x before cursor.
void List::insertBefore(int x){
  Node* N = new Node(x);

  beforeCursor->next = N;
  N->prev = beforeCursor;
  afterCursor->prev = N;
  N->next = afterCursor;
  beforeCursor = N;
  num_elements++;
  pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position() < size()
void List::eraseAfter(){
  if( position() < size()){
    afterCursor->next->prev = beforeCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next = nullptr;
    afterCursor->prev = nullptr;
    delete afterCursor;
    afterCursor = beforeCursor->next;
    num_elements--;
  }else{
    cerr << "List Error: eraseAfter() called at end of list." << endl;
    return;
  }

}

// eraseBefore()
// Deletes element after cursor.
// pre: position() > 0
void List::eraseBefore(){
  if( position() > 0){
    beforeCursor->prev->next = afterCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->next = nullptr;
    beforeCursor->prev = nullptr;
    delete beforeCursor;
    beforeCursor = afterCursor->prev;
    num_elements--;
    pos_cursor--;
  }else {
    cerr << "List Error: eraseBefore() called at front of list." << endl;
    return;
  }

}

// findNext()
// Starting from the current cursor position, preforms a linear search(in
// the direction front-to-back) for the first occurrence of the element x.
// if x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. if x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x){
  while( position() != size()){
    if(peekNext() == x){
      moveNext();
      return position(); 
      
    }else{
      moveNext();
      
    }
  }
  return -1;
  
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// if x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. if x is not found, place the cursor at position 0, and
// returns -1.
int List::findPrev(int x){
  while( position() != 0){
    if( peekPrev() == x){
       movePrev();
      return position();
    }else{
       movePrev();
    }
  }
  return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. the cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup(){
  Node* temp = frontDummy->next;
  Node* tempSearch = temp->next;
  Node* placeHolder = nullptr;
  int searchPosition = 0;
  int startPosition = 0;
  while(temp->next != backDummy){
    while( tempSearch != backDummy){
      //cout << "comparing "<< tempSearch->data << " to " << temp->data << endl;

      if( tempSearch->data == temp->data){
	
	//cout<< "made it into removal if \n";
	tempSearch->prev->next = tempSearch->next;
	tempSearch->next->prev = tempSearch->prev;

	if(tempSearch == beforeCursor ){

	  beforeCursor = tempSearch->prev;

	}else if( tempSearch == afterCursor){

	  afterCursor = tempSearch->next;
	}
	
	if( searchPosition <= pos_cursor ){
	  pos_cursor--;
	}

	placeHolder = tempSearch;
	tempSearch = tempSearch->next;
	delete placeHolder;
	placeHolder = nullptr;
	num_elements--;
	//cout<< "made it through deletion process\n";
      }else{

	tempSearch = tempSearch->next;
      }
      searchPosition++;
    }
    //cout<< "made it out of second while loop\n";
    startPosition++;
    searchPosition = startPosition + 1;
    if(temp->next != backDummy){
      temp = temp->next;
      tempSearch = temp->next;
    }
  }
  
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
  this->moveFront();

  while( num_elements != 0){
   this->eraseAfter();
  }
  
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
  List tempL = List(*this);
  Node* temp = L.frontDummy->next;
  tempL.moveBack();
    
  while( temp != L.backDummy){
    tempL.insertBefore(temp->data);
    temp = temp->next;
  }
  return tempL;

}


// Other Functions ----------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated squence of elements, surrounded by parentheses.
std::string List::to_string(){
  std::string s = "(";
  Node* temp = nullptr;
  
  for(temp = frontDummy->next; temp != backDummy; temp = temp->next){
    if( temp->next != backDummy ) {
      s += std::to_string(temp->data) + ", ";
    }else{
      s += std::to_string(temp->data) + ")";
    }
  
  }
  return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R
// the cursors in this List and in R are unchanged.
bool List::equals(const List& R){
  bool results = false;
  Node* temp = nullptr;
  Node* tempR = nullptr;
  
  results = ( this->num_elements == R.num_elements);

  temp =  this->frontDummy;
  tempR = R.frontDummy;
  
  while( results && temp != backDummy  ){
    results = ( temp->data == tempR->data );
    temp = temp->next;
    tempR = tempR->next;
  }
  return results;
}

// Overriden operators --------------------------------------------------

// operator<<()
// inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, List& L){
  return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B.
// cursors in both List are unchaanged.
bool operator==( List& A, const List& B){
  return A.List::equals(B);
}

// operator =()
// Overwrites the state of this List with state of L
List& List::operator= (const List& L){
  if( this != &L){
    List temp = L;
    
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(num_elements, temp.num_elements);
    
  }
  return *this;
}
