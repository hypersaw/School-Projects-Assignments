//
//  Collection.h
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef COLLECTION
#define COLLECTION

class Collection {
public:
    virtual void add() = 0;
    virtual void remove() = 0;
    virtual const Collection& operator=(const Collection& rightSide) = 0;
    virtual const Collection& operator[](unsigned int index) = 0;

    unsigned int size();

    //void contains();
    //void do_();
    
private:
    unsigned int size_;
};

#endif
