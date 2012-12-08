//
//  Collection.h
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef COLLECTION
#define COLLECTION

#include <iostream>

class Collection {
public:
    Collection();
    virtual ~Collection();
    
    virtual void add(int addItem, unsigned int atIndex) = 0;
    virtual void remove(int removeItem) = 0;
    virtual Collection* copy() = 0;
    virtual const Collection& operator=(Collection& rightSide) = 0;
    virtual int& operator[](const unsigned int index) = 0;

    unsigned int size();

    bool contains(int item);
    void iterate(void (*function)(int));
    
protected:
    unsigned int size_;
};

inline Collection::~Collection(){}

#endif
