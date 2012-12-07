//
//  Array.h
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef ARRAY
#define ARRAY

#include "Collection.h"

class Array : public Collection {
    
public:
    Array();

    void add(int addItem, unsigned int atIndex);
    
    void remove(int removeItem);
    
};

#endif