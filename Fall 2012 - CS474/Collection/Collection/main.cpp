//
//  main.cpp
//  Collection
//
//  Created by Andrew Long on 12/3/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include <iostream>
#include "OrderedCollection.h"
#include "Array.h"

int x = 0;

void testOrderedCollection();
void testArray();
void addAll(int i);

int main(int argc, const char * argv[])
{
    std::cout << "Begin tests...\n";
    testOrderedCollection();
    std::cout << "\n";
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
    
    Collection** a;
    a = new Collection*[5];
    
    a[0] = new OrderedCollection();
    a[0]->add(100,0);
    a[0]->add(50,0);
    a[0]->add(75,1);
    a[1] = a[0]->copy();
    
    for(int i = 0; i <= a[1]->size() - 1; ++i){
        std::cout << "(*a[1])[" << i << "] = " << (*a[1])[i] << "\n";
    }
    
    x = 0;
    
    temp2->iterate(&addAll);
    
    std::cout << "x = " << x << ".\n";
    
    std::cout << "Does *temp contain 300? " << (temp->contains(300) ? "True" : "False") << "! \n";
    std::cout << "Does *temp2 contain 300? " << (temp2->contains(300) ? "True" : "False") << "! \n";
    
    delete temp;
    delete temp2;
    delete a[1];
    delete a[0];
    delete [] a;
    
    temp = new OrderedCollection();
    temp->add(9, 0);
    temp->add(10,0);
    temp->add(11,2);
    (*temp)[1] = 100;
    
    for (int i = 0; i <= temp->size() - 1; i++) {
        std::cout << "(*temp)[" << i << "] = " << (*temp)[i] << "\n" ;
    }
    delete temp;
    
    std::cout << "End OrderedCollection tests...\n";
}

void testArray(){
    std::cout << "Begin Array tests...\n";
    
    Collection* temp = new Array(2);
    
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
    
    Collection** a;
    a = new Collection*[5];
    
    a[0] = new Array(2);
    a[0]->add(100,0);
    a[0]->add(50,0);
    a[0]->add(75,1);
    a[1] = a[0]->copy();
    
    for(int i = 0; i <= a[1]->size() - 1; ++i){
        std::cout << "(*a[1])[" << i << "] = " << (*a[1])[i] << "\n";
    }
    
    x = 0;
    
    temp2->iterate(&addAll);
    
    std::cout << "x = " << x << ".\n";
    
    std::cout << "Does *temp contain 300? " << (temp->contains(300) ? "True" : "False") << "! \n";
    std::cout << "Does *temp2 contain 300? " << (temp2->contains(300) ? "True" : "False") << "! \n";
    
    delete temp;
    delete temp2;
    delete a[1];
    delete a[0];
    delete [] a;
    
    temp = new Array(3);
    temp->add(9, 0);
    temp->add(10,0);
    temp->add(11,2);
    (*temp)[1] = 100;
    
    for (int i = 0; i <= temp->size() - 1; i++) {
        std::cout << "(*temp)[" << i << "] = " << (*temp)[i] << "\n" ;
    }
    delete temp;
    
    std::cout << "End Array tests...\n";    
}

void addAll(int i){
    x += i;
}
