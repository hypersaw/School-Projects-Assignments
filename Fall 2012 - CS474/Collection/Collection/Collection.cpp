//
//  Collection.cpp
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "Collection.h"

Collection::Collection(){
    size_ = 0;
}

unsigned int Collection::size(){
    return size_;
}

bool Collection::contains(int item){
    for(int i = 0; i < size_; ++i){
        if(collectionArray[i] == item){
            return true;
        }
    }
    
    return false;
}

void Collection::iterate(void (*function)(int)){
    for(int i = 0; i < size_; ++i){
        function(collectionArray[i]);
    }
}