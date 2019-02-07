
//
//  main.cpp
//  Assignment2-Data Structure
//
//  Created by Joshua Peckham on 1/25/17.
//  Copyright © 2017 Joshua Peckham. All rights reserved.
//

#include <iostream>
#include <fstream>


using namespace std;
typedef char Type;

const int ARRAY_SIZE = 8;
static int NODES = 0;

class noValue{};
class endLocation{};
class valueFound{};

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
template<class T>
ChunkList<T>::ChunkList(){
    head = nullptr;
    tail = nullptr;
    TotalListSize = 0;
}
template<class T>
ChunkList<T>::~ChunkList(){
    while(head != nullptr){
        tail = head;
        head = tail->next;
        delete tail;
        NODES--;
    }
}
template<class T>
T ChunkList<T>::LastValue() {
    if (tailNodeLength > 0)
        return tail->array[tailNodeLength - 1];
    else{
        tailNodeCheck();
        return tail->array[tailNodeLength - 1];
    }
    
}
template<class T>
void ChunkList<T>::tailNodeCheck(){
    if (tailNodeLength == -1){
        for (int i = 1; i < (NODES-1); i++){
            navi = navi->next;
        }
        tail = navi;
        navi = navi->next;
        delete navi;
        tail->next = nullptr;
        tailNodeLength = 8;
    }
}
template <class T>
void ChunkList<T>::MakeEmpty(){
    while(head != nullptr){
        tail = head;
        head = tail->next;
        delete tail;
        NODES--;
    }
    head = tail = nullptr;
    tailNodeLength = 0;
    TotalListSize = 0;
}
template <class T>
bool ChunkList<T>::isFull()const{
    
    ChunkNode* newChunk = new ChunkNode;
    newChunk->next = nullptr;
    
    if(newChunk){
        delete newChunk;
        return false;
    }
    else{
        return true;
    }
}
template<class T>
int ChunkList<T>::GetLength() const{
    return TotalListSize;
}
template<class T>
T ChunkList<T>::GetItem(T value){
    ResetList();
    for( int i = 0 ; i < TotalListSize; i++){
        if ( value == GetNextItem()){
            return value;
        }
    }
    throw noValue();
}
template<class T>
void ChunkList<T>::PutItem(T value){
    if( (TotalListSize == 0) || (tailNodeLength == ARRAY_SIZE) ){
        ChunkNode* newChunk = new ChunkNode;
        newChunk->next = nullptr;
        tailNodeLength = 0;
        newChunk->array[tailNodeLength++] = value;
        
        if(TotalListSize == 0)
            head = tail = newChunk;
        else{
            tail = newChunk;
            head->next = tail;
        }
        
        TotalListSize++;
        NODES++;
    }
    else{
        tail->array[tailNodeLength++] = value;
        TotalListSize++;
    }
}
template<class T>
void ChunkList<T>::DeleteItem(T value){
    ResetList();
    for(int i = 0; i < TotalListSize ; i++){
        if ( navi != tail ){
            if (value == navi->array[naviposition++]){
                navi->array[i] = LastValue();
                tailNodeLength--;
                tailNodeCheck();
                TotalListSize--;
                break;
            }
            if (naviposition%ARRAY_SIZE == 0){
                navi = navi->next;
                naviposition = 0;
            }
        }
    }
    throw noValue();
}
template<class T>
void ChunkList<T>::ResetList(){
    navi = head;
    naviposition = 0;
}
template<class T>
T ChunkList<T>::GetNextItem(){
    T item;
    if ( navi != tail ){
        item = navi->array[naviposition++];
        if (naviposition%ARRAY_SIZE == 0){
            navi = navi->next;
            naviposition = 0;
        }
        return item;
    }
    if ( naviposition != tailNodeLength){
        return navi->array[naviposition++];
    }
    else
        throw endLocation();
    return T(); // remember this
}
template<class T>
void ChunkList<T>::PrintList(){
    ResetList();
    for (int i = 0; i < TotalListSize; i++) {
        cout << GetNextItem() << " ";
    }
    cout << endl;
}

int main(){
    
    ifstream inFile;       // file containing operations
    ofstream outFile;      // file containing output
    string inFileName;     // input file external name
    string outFileName;    // output file external name
    string outputLabel;
    string command;        // operation to be executed
    
    ChunkList<Type> Chunk;
    int numCommands;
    
    Type item;
    int numInputs;
    
    
    // Prompt for file names, read file names, and prepare files
    cout << "Enter name of input command file; press return." << endl;
    cin >> inFileName;
    inFile.open(inFileName);
    if(inFile.is_open()) // verification the document opened
        cout << "File Opened Success" << endl;
    else
        cout << "fail" << endl;
    
    
    cout << "Enter name of output file; press return." << endl;
    cin  >> outFileName;
    outFile.open(outFileName);
    if(inFile.is_open())
        cout << "Success" << endl;
    else
        cout << "fail" << endl;
    
    cout << "Enter name of test run; press return." << endl;
    cin  >> outputLabel;
    outFile << outputLabel << endl;
    
    inFile >> command;
    
    
    numCommands = 0;
    while (command != "Quit")
    {
        try
        {
            if (command == "PutItem"){
                inFile >> numInputs;
                outFile << "Running PutItem" << endl;
                for(int i = 0; i < numInputs; i++){
                    inFile >> item;
                    Chunk.PutItem(item);
                }
            }
            else if (command == "GetLength"){
                outFile << "Running GetLength" << endl;
                outFile << Chunk.GetLength() << endl;
            }
            else if (command == "DeleteItem"){
                outFile << "Running DeleteItem" << endl;
                inFile >> item;
                Chunk.DeleteItem(item);
            }
            else if (command == "IsFull"){
                if (Chunk.isFull()){
                    outFile << "Stack is Full." << endl;
                }
                else{
                    outFile << "Not Full" << endl;
                }
            }
            else if(command == "MakeEmpty"){
                outFile << "Running MakeEmpty" << endl;
                Chunk.MakeEmpty();
            }
            else if( command == "PrintList"){
                Chunk.PrintList();
            }
            else if ( command == "GetItem"){
                outFile << "Running GetItem" << endl;
                inFile >> item;
                cout << Chunk.GetItem( item ) << endl;
                outFile << Chunk.GetItem( item ) << endl;
            }
            else if ( command == "NODES"){
                cout << NODES << endl;
            }
        }
        catch (noValue){
            outFile << "No value found" << endl;
        }
        catch (endLocation){
            outFile << "No more values" << endl;
        }
        catch (valueFound){
            outFile << "Value Found" << endl;
        }
        numCommands++;
        cout <<  " Command number " << numCommands << " completed."
        << endl;
        inFile >> command;
    }
    cout << "Testing completed."  << endl;
    inFile.close();
    outFile.close();
    return 0;
}

