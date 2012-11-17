//
//  SetCalculator.h
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/10/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef SETCALCULATOR
#define SETCALCULATOR

#include <iostream>
#include <string>
#include "BinaryHeap.h"

class SetCalculator {
public:
    SetCalculator();
    ~SetCalculator();

    void displayPrompt();
    
private:
    // Sets
    BinaryHeap* setOne;
    BinaryHeap* setTwo;
    
    // Display
    void displaySetOne();
    void displaySetTwo();
    
    // Add
    void addToSetOne(int data);
    void addToSetTwo(int data);
    
    // Remove
    void removeFromSetOne(int data);
    void removeFromSetTwo(int data);
    
    // Perform
    void performClear();
    void performSwitch();
    void performCopy();
    void performIntersection();
    void performUnion();
    
    void traverseAndAddDuplicatesTo(BinaryNode* subRoot, BinaryHeap* newHeap);
    void traverseAndAddTo(BinaryNode* subRoot, BinaryHeap* newHeap);
};

#endif
