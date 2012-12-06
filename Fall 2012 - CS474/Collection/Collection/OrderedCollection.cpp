//
//  OrderedCollection.cpp
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "OrderedCollection.h"

OrderedCollection::OrderedCollection(){
    collectionArray = new int[4];
    firstIndex = 0;
    lastIndex = 3;
    size_ = 0;
}

OrderedCollection::~OrderedCollection(){
    delete [] collectionArray;
}

void OrderedCollection::add(int addItem, unsigned int atIndex){
    // Check to make sure the index is valid
    if(atIndex <= lastIndex){
        growIfNecessary();
        
        if(atIndex == 0){
            collectionArray[0] = addItem;
        }
        else if(atIndex >= size_){
            collectionArray[size_] = addItem;
        }
        else{
            // Shift items greater than/equal to atIndex
            // up by one
            for(int i = size_; i > atIndex; --i){
                collectionArray[i] = collectionArray[i-1];
            }
        
            // Add item into desired index position
            collectionArray[atIndex] = addItem;
        }
        
        ++size_;
    }
}

void OrderedCollection::remove(int atIndex){
    ++atIndex;
}

Collection* OrderedCollection::copy(){
    Collection* copiedOrderedCollection = new OrderedCollection();
    for(int i = 0; i < size(); ++i){
        copiedOrderedCollection->add(collectionArray[i],i);
    }
    
    return copiedOrderedCollection;
}

/*
const Collection& OrderedCollection::operator=(const Collection &rightSide){
    
}
*/
const int OrderedCollection::operator[](unsigned int index){
    return collectionArray[index];
}


void OrderedCollection::growIfNecessary(){
    // If necessary...
    if(size_ == (lastIndex + 1)){
        // Create new array with double the space
        lastIndex = (lastIndex+1) * 2;
        int* newArray;
        newArray = new int[lastIndex];
    
        // Copy contents of old array into new array
        for(int i = 0; i <= lastIndex; ++i){
            newArray[i] = collectionArray[i];
        }
    
        // Destroy old array and reassign
        delete [] collectionArray;
        collectionArray = newArray;
    }
}