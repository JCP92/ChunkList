//
//  ChunkList.h
//  Assignment2-Data Structure
//
//  Created by Joshua Peckham on 2/1/17.
//  Copyright © 2017 Joshua Peckham. All rights reserved.
//
#include <iostream>
#include <fstream>
#ifndef ChunkList_h
#define ChunkList_h
using namespace std;
typedef char Type;

const int ARRAY_SIZE = 8;
static int NODES = 0;
template<class T>
class ChunkList{
private:
    struct ChunkNode{
        ChunkNode* next;
        T array[ARRAY_SIZE];
    };
    ChunkNode* head;
    ChunkNode* tail;
    ChunkNode* navi;
    int naviposition;
    int tailNodeLength;
    int TotalListSize;
public:
    ChunkList();
    // Function: Initialize chunklist
    // Precondition: define variable based on class
    // Postcondition: class will be ready to use
    ~ChunkList();
    // Function: deallocate all dynamically allocated memory
    // Precondition:must have allocated memory to dealocate
    // Postcondition: no memory leak
    void MakeEmpty();
    // Function: deallocate all dynamically allocated memory
    // Precondition:must have allocated memory to dealocate
    // Postcondition: New Start of the list
    bool isFull() const;
    // Function: Make sure there is memory availible
    // Precondition: n/a
    // Postcondition: can create more nodes
    int GetLength() const;
    // Function: Return total amount of used space in chunklist
    // Precondition: class must be activated
    // Postcondition: shows amount of all arrays elements in use
    T GetNextItem();
    // Function: Finds and returns searched valuse
    // Precondition: must have an activated ChunkList
    // Postcondition: return the value or no value
    void PutItem(T);
    // Function: Place items in the chunklist
    // Precondition: must have to be able to dynamically allocated memory
    // Postcondition: stored in check list
    void DeleteItem(T);
    // Function: Located and delete item if present
    // Precondition: Chunklist must be actived
    // Postcondition: Removed item or exception thrown
    void ResetList();
    // Function: Prepare to navigate values
    // Precondition: chunlist initailized
    // Postcondition: Navigation is ready to begin from the beginning
    T GetItem(T);
    // Function: Return values in consective order
    // Precondition: Must have used reset list
    // Postcondition: returned values or exception thrown
    void PrintList();
    // Function: Print all values availible
    // Precondition: Must you use reset list
    // Postcondition: Print all values applicable or exception thrown
    void tailNodeCheck();
    // Function: Navigate to send correct value
    // Precondition: must have more than one chunknode
    // Postcondition: will give correct value
    T LastValue();
    // Function: return last value
    // Precondition:arrays must be initialized
    // Postcondition: value is returend
};


#endif /* ChunkList_h */
