//
//  main.cpp
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include <iostream>
#include "OrderedCollection.h"

void testOrderedCollection();
void testArray();

int main(int argc, const char * argv[])
{
    std::cout << "Begin tests...\n";
    testOrderedCollection();
    testArray();
    return 0;
}

void testOrderedCollection(){
    std::cout << "Begin OrderedCollection tests...\n";
    
    Collection* temp = new OrderedCollection();
    
    temp->add(10, 0);
    temp->add(200, 1);
    temp->add(250, 1);
    
    for(int i = 0; i <= temp->size() - 1; ++i){
        std::cout << "(*temp)[" << i << "] = " << (*temp)[i] << "\n";
    }
    
    Collection* temp2;
    temp2 = temp->copy();
    temp2->add(300, 2);
    
    for(int i = 0; i <= temp->size() - 1; ++i){
        std::cout << "(*temp)[" << i << "] = " << (*temp)[i] << "\n";
    }
    
    for(int i = 0; i <= temp2->size() - 1; ++i){
        std::cout << "(*temp2)[" << i << "] = " << (*temp2)[i] << "\n";
    }
    
    std::cout << "End OrderedCollection tests...\n";
}

void testArray(){
    
}
