//
//  BinaryHeap.h
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/6/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef BINARYHEAP
#define BINARYHEAP

#include <stdlib.h>
#include <iostream>
#include "BinaryNode.h"
#include "Queue.h"

class BinaryHeap {
public:
    BinaryHeap();
    ~BinaryHeap();
    
    BinaryNode* root;
    BinaryNode* last;
    
    int add(int data);
    int remove(int data);
    void display();
    int exists(int data);
    
    void clear();
    
    bool isEmpty() const;
    
    BinaryHeap& operator=(const BinaryHeap& otherHeap);
    
private:
    // Copying
    void copy(const BinaryHeap& otherHeap);
    void copy_recursive(BinaryNode* currentNode);
    
    // Adding | Removing
    int add_recursive(BinaryNode* data);
    void clear_recursive(BinaryNode* subRoot);
    
    // Finding
    BinaryNode* find(int searchData);
    BinaryNode* find_recursive(BinaryNode* subRoot, BinaryNode* searchData);
    void exists_recursive(BinaryNode* subRoot, BinaryNode* searchData, int& found);
    void setLast();
    
    // Sorting
    void sort();
    void sort_recursive();
    void heapify(BinaryNode* subRoot);
    
protected:
};

#endif