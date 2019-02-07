//
//  ChunkList.cpp
//  Assignment2-Data Structure
//
//  Created by Joshua Peckham on 2/1/17.
//  Copyright © 2017 Joshua Peckham. All rights reserved.
//

#include "ChunkList.h"
#include <iostream>
#include <fstream>
class noValue{};
class endLocation{};
class valueFound{};

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
