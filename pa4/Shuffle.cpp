//----------------------------------------------------------------------------
// Created by : Smith, Shane
//              ssmith30
//
//
//             shuffle.cpp
// Assignment: Pa4: the perfect shuffle
//             CSE 101, Introduction to Data Structures and algorithms
//             UC Santa Cruz, Winter 2021.
//
// Description:  shuffles a deck of cards represented by a integer List ADT
//----------------------------------------------------------------------------

//#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "List.h"

using namespace std;

void shuffle(List& D);

int main(int argc, char * argv[]){
  if (argc < 2 ){
    cout << "not enough arguments" << endl;
    return -1; 
  }
  List myList, copyList;
  int shuffleCount;
  int input = atoi(argv[1]);
  cout << "deck size        shuffle count\n";
  cout << "------------------------------\n";
  for(int i = 1; i <= input; i++){
    myList.insertBefore(i);
    copyList = myList;
    shuffle(myList);
    shuffleCount = 1;
    
    while( !( myList == copyList)){
      shuffle(myList);
      shuffleCount++;
    }
    cout << " " << setw(17) << left << i << setfill(' ') 
	 << right << shuffleCount << endl;
  }
  
  


  return 0;
}

void shuffle( List& D){
  int midwayPoint = (D.size())/2;
  int myArr[midwayPoint];
  D.moveFront();
  
  for(int i = 0; i < midwayPoint; i++){
    myArr[i] = D.moveNext();
    D.eraseBefore();
  }
  
  D.moveFront();
  for(int i = 0; i < midwayPoint; i++){
    D.moveNext();
    D.insertBefore(myArr[i]);
  }
  

}
