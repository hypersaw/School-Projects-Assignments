//
//  BinaryHeap.cpp
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/6/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "BinaryHeap.h"

BinaryHeap::BinaryHeap(){
    root = NULL;
    last = NULL;
}

BinaryHeap::~BinaryHeap(){
    clear();
}

int BinaryHeap::add(int data){
    // Check if item already exists
    if(exists(data)){
        return 0;
    }
    
    // Item doesn't exists, add to last
    BinaryNode* newNode;
    newNode = new BinaryNode(data);
    if(isEmpty()){
        root = newNode;
        last = newNode;
    }
    else{
        BinaryNode* currentNode = last;
        // If our current node is not a left child or not root, move to it's parent
        while(currentNode->isRightChild()){
            currentNode = currentNode->parent;

        }
        
        // Get current sibling, or set node if no sibling
        if(currentNode->isLeftChild()){
            if(currentNode->hasSibling()){
                currentNode = currentNode->parent->rightChild;
            }
            else{
                currentNode = currentNode->parent;
                currentNode->setRightChild(*newNode);
                last = newNode;
                sort();
                return 1;
            }
        }
        
        while(currentNode->hasLeftChild()){
            currentNode = currentNode->leftChild;
        }
        currentNode->setLeftChild(*newNode);
        last = newNode;
        sort();
    }

    return 1;
}

int BinaryHeap::remove(int data){
   
    return 0;
}

void BinaryHeap::display(){
    Queue<BinaryNode> displayQueue;
    
    if(!isEmpty()){
        displayQueue.enqueue(root);
    }
    
    std::cout << "Heap: ";
    while(displayQueue.itemCount() > 0){
        BinaryNode displayNode = displayQueue.dequeue();
        std::cout << displayNode.data;
        
        if(displayNode.leftChild != NULL){
            displayQueue.enqueue(displayNode.leftChild);
        }
        if(displayNode.rightChild != NULL){
            displayQueue.enqueue(displayNode.rightChild);
        }
        if(displayQueue.itemCount() != 0){
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
}

void BinaryHeap::clear(){
    if(!isEmpty()){
        if(root->hasLeftChild()){
            clear_recursive(root->leftChild);
            delete root->leftChild;
        }
        if(root->hasRightChild()){
            clear_recursive(root->rightChild);
            delete root->rightChild;
        }
        
        delete root; root = NULL;
        delete last; last = NULL;
    }
}

void BinaryHeap::clear_recursive(BinaryNode *subRoot){
    if(subRoot->hasLeftChild()){
        clear_recursive(subRoot->leftChild);
        delete subRoot->leftChild;
    }
    if(subRoot->hasRightChild()){
        clear_recursive(subRoot->rightChild);
        delete subRoot->rightChild;
    }
}

void BinaryHeap::copy(const BinaryHeap& otherHeap){
    BinaryNode* currentNode = otherHeap.root;
    
    clear();
    
    if(!otherHeap.isEmpty()){
        copy_recursive(currentNode);
    }
}

void BinaryHeap::copy_recursive(BinaryNode* subRoot){
    add(subRoot->data);
    
    if(subRoot->hasLeftChild()){
        copy_recursive(subRoot->leftChild);
    }
    if(subRoot->hasRightChild()){
        copy_recursive(subRoot->rightChild);
    }
}

bool BinaryHeap::isEmpty() const{
    if(root == NULL){
        return true;
    }
    
    return false;
}

BinaryHeap& BinaryHeap::operator=(const BinaryHeap &otherHeap){
    if(&otherHeap != this){
        copy(otherHeap);
    }
    
    return *this;
}

BinaryNode& BinaryHeap::find(int searchData){
    BinaryNode* foundNode = NULL;
    
    if(!isEmpty()){
        // We have a non-empty list, make a new node and search
        BinaryNode searchNode(searchData);
        find_recursive(root, &searchNode, foundNode);
    }
    
    return *foundNode;
}

void BinaryHeap::find_recursive(BinaryNode* subRoot, BinaryNode* searchNode, BinaryNode* foundNode){
    
    if(subRoot == searchNode){
        foundNode = subRoot;
    }
    
    // If we found our node, stop recursion
    // Else, search children
    if(foundNode == NULL){
        if(subRoot->leftChild != NULL){
            find_recursive(subRoot->leftChild, searchNode, foundNode);
        }
        if(subRoot->rightChild != NULL){
            find_recursive(subRoot->rightChild, searchNode, foundNode);
        }
    }
}

int BinaryHeap::exists(int data){
    BinaryNode searchNode(data);
    int found = 0;
    
    if(!isEmpty()){
        exists_recursive(*root,searchNode,found);
    }
    
    return found;
}

void  BinaryHeap::exists_recursive(BinaryNode& subRoot, BinaryNode& searchNode, int &found){
    // If our root is equal to what we are searching for
    // then we set found to 1.
    if(subRoot == searchNode){
        found = 1;
    }
    
    // If we haven't found the item then search the children
    if(found != 1){
        if(subRoot.leftChild != NULL){
            exists_recursive(*subRoot.leftChild, searchNode, found);
        }
        if(subRoot.rightChild != NULL){
            exists_recursive(*subRoot.rightChild, searchNode, found);
        }
    }
}

void BinaryHeap::sort(){
    
    BinaryNode* currentNode = last;
    
    while(currentNode->hasParent()){
        if(*currentNode > *currentNode->parent){
            int temp = currentNode->data;
            currentNode->setData(currentNode->parent->data);
            currentNode->parent->setData(temp);
            currentNode = currentNode->parent;
        }
        else{
            currentNode = root;
        }
    }
}

