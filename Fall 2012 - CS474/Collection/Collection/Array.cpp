//
//  Array.cpp
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "Array.h"

Array::Array(unsigned int size) : Collection(){
    collectionArray = new int[size];
    size_ = size;
}

void Array::add(int addItem, unsigned int atIndex){
    std::cerr << "Cannot add item to Array\n";
}

void Array::remove(int removeItem){
    std::cerr << "Cannot remove item from Array\n";
}

Collection* Array::copy(){
    Collection* newArray = new Array(size_);
    
    for(int i = 0; i < size_; ++i){
        (*newArray)[i] = collectionArray[i];
    }
    
    return newArray;
}

const Collection& Array::operator=(Collection &rightSide){
    if(this == &rightSide){
        return *this;
    }
    
    Collection* newArray = new Array(size_);
    newArray = this->copy();
    
    return *newArray;
}

int& Array::operator[](const unsigned int index){
    return collectionArray[index];
}


