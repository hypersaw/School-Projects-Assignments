//
//  OrderedCollection.cpp
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "OrderedCollection.h"

OrderedCollection::OrderedCollection() : Collection(){
    collectionArray = new int[4];
    firstIndex = 2;
    lastIndex = 1;
    offset = 1;
}

OrderedCollection::~OrderedCollection(){
    delete [] collectionArray;
}

void OrderedCollection::add(int addItem, unsigned int atIndex){
    // Check to make sure the index is valid/contiguous
    
    if(atIndex <= (lastIndex-firstIndex+1)){
        growIfNecessary();
        
        // If list is empty
        if(firstIndex > lastIndex){
            collectionArray[lastIndex] = addItem;
            
            firstIndex = lastIndex;
        }
        else{
            // If the desired index is closest to the
            // firstIndex OR the middle
            if((atIndex * 2) <= (firstIndex + lastIndex)){
                // Check to see if left side is filled
                if(firstIndex == 0 || atIndex == 0){
                    shiftRight(atIndex);
                }
                // Otherwise shift items from atIndex and down to the left
                else{
                    shiftLeft(firstIndex + atIndex - 1);
                }
            }
            else{
                // Check to see if right side is filled
                if((lastIndex + 1) == (offset * 4)){
                    shiftLeft(atIndex - firstIndex);
                }
                // Otherwise shift items from atIndex and up to the right
                else{
                    shiftRight(firstIndex + atIndex);
                }
            }
            
            collectionArray[firstIndex + atIndex] = addItem;
        }
        
        ++size_;
    }
}

void OrderedCollection::remove(int removeItem){
    if(contains(removeItem)){
        for(int i = firstIndex; i <= lastIndex; ++i){
            if(collectionArray[i] == removeItem){
                if(((firstIndex + i) * 2 <= (firstIndex + lastIndex))
                   && (firstIndex != i)){
                    // The item we are removing is in the first half of our set
                    // (but not the first) So we will shift those numbers to the right
                    removeShiftRight(i);
                }
                else{
                    removeShiftLeft(i);
                }
            }
        }
    }
}

Collection* OrderedCollection::copy(){
    Collection* copiedOrderedCollection = new OrderedCollection();
    for(int i = 0; i < size(); ++i){
        copiedOrderedCollection->add((*this)[i],i);
    }
    
    return copiedOrderedCollection;
}

const Collection& OrderedCollection::operator=(Collection& rightSide){
    if(this == &rightSide){
        return *this;
    }
    
    Collection* newCollection = new OrderedCollection();
    newCollection = this->copy();
    
    return *newCollection;
}

int& OrderedCollection::operator[](const unsigned int index){
    return collectionArray[firstIndex+index];
}

// Expands the collection from the passed in value and up
void OrderedCollection::shiftRight(unsigned int fromIndex){
    for(int i = lastIndex; i >= (firstIndex + fromIndex); --i){
        collectionArray[i + 1] = collectionArray[i];
    }
    ++lastIndex;
}

// Expands the collection from the passed in value and down
void OrderedCollection::shiftLeft(unsigned int fromIndex){
    for(int i = firstIndex; i <= (firstIndex + fromIndex); ++i){
        collectionArray[i - 1] = collectionArray[i];
    }
    --firstIndex;
}

// Contracts the collection from the passed in value and up
void OrderedCollection::removeShiftRight(unsigned int toIndex){
    for(int i = toIndex; i > firstIndex; --i){
        collectionArray[i] = collectionArray[i-1];
    }
    --firstIndex;
}

// Contracts the collection from the passed in value and down
void OrderedCollection::removeShiftLeft(unsigned int toIndex){
    for(int i = toIndex; i < lastIndex; ++i){
        collectionArray[i] = collectionArray[i+1];
    }
    --lastIndex;
}

// If the size of the array has reached it's limit then grow
void OrderedCollection::growIfNecessary(){
    // If necessary...
    if(size_ == (offset * 4)){
        // Calculate the offset we will have
        // to place elements in middle of new array
        offset = (lastIndex+1)/2;
        
        // Create new array with double the space
        lastIndex = (size_ * 2) - 1;
        int* newArray;
        newArray = new int[lastIndex+1];
        lastIndex -= offset;    // Correct lastIndex to reflect offset on end
        firstIndex = offset;    // Correct firstIndex to reflect new firstIndex (the offset)
        
        // Copy contents of old array into new array
        for(int i = offset; i <= lastIndex; ++i){
            newArray[i] = collectionArray[i-offset];
        }
    
        // Destroy old array and reassign
        delete [] collectionArray;
        collectionArray = newArray;
    }
}