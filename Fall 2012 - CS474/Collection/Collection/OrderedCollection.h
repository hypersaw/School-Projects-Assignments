//
//  OrderedCollection.h
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//
//
//  OrderedCollection Notes
//  -All items added to end unless specified
//  -Initial size is 4 elements, each growth spurt is size*2
//  -If two items were added, firstIndex would be 0, lastIndex would be 3, size_ would be 2

#ifndef ORDERED_COLLECTION
#define ORDERED_COLLECTION

#include "Collection.h"

class OrderedCollection: public Collection {
public:
    OrderedCollection();
    ~OrderedCollection();
    
    void add(int addItem, unsigned int atIndex);
    void remove(int atIndex);
    
    Collection* copy();
    
    const Collection& operator=(Collection& rightSide);
    int& operator[](const unsigned int index);

private:
    int* collectionArray;
    
    unsigned int firstIndex;
    unsigned int lastIndex;
    
    unsigned int offset;
    
    void shiftRight(unsigned int fromIndex);
    void shiftLeft(unsigned int fromIndex);
    
    void removeShiftRight(unsigned int toIndex);
    void removeShiftLeft(unsigned int toIndex);
    
    void growIfNecessary();
};

#endif