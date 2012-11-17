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
    BinaryHeap(const BinaryHeap& otherHeap);
    ~BinaryHeap();
    
    BinaryNode* root;                       // The first item in the tree
    BinaryNode* last;                       // The last item in the tree
    
    int add(int data);                      // Add an alement to tree defined by int
    int remove(int data);                   // Remove an element from tree defined by int
    void display();                         // Display breadth-order
    int exists(int data);                   // Does an item exist in tree?
    void clear();                           // Empty out the list
    bool isEmpty() const;                   // Is the list empty?
    
    BinaryHeap& operator=(const BinaryHeap& otherHeap);
    
private:
    // Copying
    void copy(const BinaryHeap* otherHeap); // Deep copy of otherHeap into self.
    void copy_recursive(BinaryNode* currentNode);
    
    // Adding | Removing
    int add_recursive(BinaryNode* data);
    void clear_recursive(BinaryNode* subRoot);
    void removeLast();                      // Deletes last, set's it to NULL and calls setLast()
    
    // Finding
    BinaryNode* find(int searchData);       // Finds an item in a tree and returns it's pointer
    BinaryNode* find_recursive(BinaryNode* subRoot, BinaryNode* searchData);
    void exists_recursive(BinaryNode* subRoot, BinaryNode* searchData, int& found);
    void setLast();                         // Finds the last position in the tree and sets last.
    
    // Sorting
    void sort();                            // Takes the last element and sifts it up the tree
    void sort_recursive();
    void heapify(BinaryNode* subRoot);      // Takes a defined element and sifts it down the tree
};

#endif