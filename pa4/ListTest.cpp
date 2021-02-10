//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//
//
//             ListTest.cpp
// Assignment: Pa4: the perfect shuffle
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  testing module for the List ADT
//----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int main() {
  List myList, copyList, myOtherList;
  
  cout << "my List is empty = " << ( myList.isEmpty()?"true":"false") << " should be true" << endl;
  
  for( int i = 1; i <= 30; i++){
    myList.insertAfter(i);
    myOtherList.insertBefore(i);
    
  }
  
  cout << endl;
  cout << "my List = " << myList << endl;
  cout << "my List is size " << myList.size() 
       << " and it's cursor position is " << myList.position() << endl;
  cout << endl << "my Other List = " << myOtherList << endl;
  cout << "my Other List is size " << myOtherList.size()
       << " and it's cursor position is " << myOtherList.position() << endl;
  
  myList.moveBack();
  myOtherList.moveFront();
  cout << endl << "my list position is " << myList.position() 
       << " my other lists position is " << myOtherList.position() << endl;
  
  while ( myList.position() != 0){
    cout << "is "<< myList.peekPrev() << " equal to "<< myOtherList.peekNext()
	 << ( myList.movePrev() == myOtherList.moveNext()?" true":" false") << endl;
  }
  
  copyList = myOtherList;
  copyList.concat(myList);
  cout << copyList << endl;

  copyList.cleanup();
  cout << copyList << endl;

  cout << endl << myList << endl;
  cout << endl << myOtherList << endl;
  for(int i = 1; i<=30; i++){
    if ( i%2 == 0){
      myList.findNext(i);
      myList.eraseBefore();
    }else{
      myOtherList.findPrev(i);
      myOtherList.eraseAfter();
    }
  }
  cout << endl << myList << endl;
  cout << endl << myOtherList << endl;
  
  myList.clear();
  myOtherList.clear();
  cout << " the Lists are now equal: " << (myList == myOtherList?"true":"false") << endl;
  cout << endl << myList << endl;
  cout << endl << myOtherList << endl;
 


  return 0; 
}
