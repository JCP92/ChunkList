//
//  main.cpp
//  Assignment2-Data Structure
//
//  Created by Joshua Peckham on 1/25/17.
//  Copyright © 2017 Joshua Peckham. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "ChunkList.h"


using namespace std;
typedef char Type;

class noValue{};
class endLocation{};
class valueFound{};


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

