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
    
    
    virtual void add(int addItem, unsigned int atIndex) = 0;
    virtual void remove(int removeItem);
    virtual Collection* copy() = 0;
    //virtual const Collection& operator=(const Collection& rightSide) = 0;
    virtual const int operator[](unsigned int index) = 0;

    unsigned int size();

    //void contains();
    //void do_();
    
protected:
    unsigned int size_;
};

#endif
