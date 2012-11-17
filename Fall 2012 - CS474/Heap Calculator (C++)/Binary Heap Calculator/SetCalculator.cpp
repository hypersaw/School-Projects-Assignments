//
//  SetCalculator.cpp
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/10/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "SetCalculator.h"

SetCalculator::SetCalculator(){
    setOne = new BinaryHeap;
    setTwo = new BinaryHeap;
}

SetCalculator::~SetCalculator(){
    delete setOne;
    delete setTwo;
}

void SetCalculator::displayPrompt(){
    std::cout << "Set Calculator (C++) by Andrew Long. University of Illinois - Chicago." << std::endl;
    char choice;
    
    do{
        std::cout << "(C)lear C(o)py (S)witch (D)isplay (A)dd (R)emove (U)nion (I)ntersection (Q)uit" << std::endl;
        std::cout << "(Set One) "; setOne->display();
        std::cout << "(Set Two) "; setTwo->display();
        std::cout << "Choice: "; std::cin >> choice;
        
        switch(choice){
            case 'C':
            case 'c':
                performClear();
            break;
            case 'O':
            case 'o':
                performCopy();
            break;
            case 'S':
            case 's':
                performSwitch();
            break;
            case 'A':
            case 'a':{
                // Add Item.
                int addInput;
                std::cout << "Add: "; std::cin >> addInput;
                setOne->add(addInput);
            }
            break;
            case 'R':
            case 'r':{
                // Remove Item.
                int removeInput;
                std::cout << "Remove: "; std::cin >> removeInput;
                setOne->remove(removeInput);
            }
            break;
            case 'U':
            case 'u':
                performUnion();
            break;
            case 'I':
            case 'i':
                performIntersection();
            break;
        }
        std::cout << std::endl;
    }while(choice != 'q');
}

void SetCalculator::displaySetOne(){
    std::cout << "(H1) "; setOne->display();
}

void SetCalculator::displaySetTwo(){
    std::cout << "(H2) "; setTwo->display();
}

void SetCalculator::addToSetOne(int data){
    if(!setOne->add(data)){
        std::cout << "Item already exists in H1." << std::endl;
    }
}

void SetCalculator::addToSetTwo(int data){
    if(!setTwo->add(data)){
        std::cout << "Item already exists in H2." << std::endl;
    }
}

void SetCalculator::removeFromSetOne(int data){
    if(!setOne->remove(data)){
        std::cout << "Item does not exist in H1." << std::endl;
    }
}

void SetCalculator::removeFromSetTwo(int data){
    if(!setTwo->remove(data)){
        std::cout << "Item does not exist in H2." << std::endl;
    }
}

void SetCalculator::performClear(){
    setOne->clear();
}

void SetCalculator::performSwitch(){
    BinaryHeap temp(*setOne);
    delete setOne;
    setOne = new BinaryHeap(*setTwo);
    delete setTwo;
    setTwo = new BinaryHeap(temp);
}

void SetCalculator::performCopy(){
    *setTwo = *setOne;
}

void SetCalculator::performIntersection(){
    BinaryHeap intersectionHeap;
    
    traverseAndAddDuplicatesTo(setOne->root, &intersectionHeap);
    
    *setOne = intersectionHeap;
}

void SetCalculator::performUnion(){
    traverseAndAddTo(setTwo->root, setOne);
}

void SetCalculator::traverseAndAddDuplicatesTo(BinaryNode* subRoot, BinaryHeap* newHeap){
    if(setTwo->exists(subRoot->data)){
        newHeap->add(subRoot->data);
    }
    
    if(subRoot->hasLeftChild()){
        traverseAndAddDuplicatesTo(subRoot->leftChild, newHeap);
    }
    if(subRoot->hasRightChild()){
        traverseAndAddDuplicatesTo(subRoot->rightChild, newHeap);
    }
}

void SetCalculator::traverseAndAddTo(BinaryNode* subRoot, BinaryHeap* newHeap){
    newHeap->add(subRoot->data);
    
    if(subRoot->hasLeftChild()){
        traverseAndAddTo(subRoot->leftChild, newHeap);
    }
    if(subRoot->hasRightChild()){
        traverseAndAddTo(subRoot->rightChild, newHeap);
    }
}
