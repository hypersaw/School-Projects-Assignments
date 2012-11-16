//
//  Set.h
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/10/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef SET
#define SET

#include "BinaryHeap.h"

class Set: public BinaryHeap{
public:
    Set();
    ~Set();
    
    Set& intersectionWith(const Set& secondSet);
    Set& unionWith(const Set& secondSet);
    Set& differenceWith(const Set& secondSet);
};

#endif