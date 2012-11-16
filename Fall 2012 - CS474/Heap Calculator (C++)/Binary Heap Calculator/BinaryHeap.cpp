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
    BinaryNode* foundNode;
    foundNode = find(data);
    
    if(foundNode){
        foundNode->data = last->data;
        last->data = data;
        heapify(foundNode);
        setLast();
        
        delete last;
        last = NULL;
        return 1;
    }
    
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
        clear_recursive(root);
        
        delete root;
        root = NULL; last = NULL;
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

BinaryNode* BinaryHeap::find(int searchData){
    BinaryNode* foundNode = NULL;
    
    if(!isEmpty()){
        // We have a non-empty list, make a new node and search
        BinaryNode searchNode(searchData);
        foundNode = find_recursive(root, &searchNode);
    }
    
    return foundNode;
}

BinaryNode* BinaryHeap::find_recursive(BinaryNode* subRoot, BinaryNode* searchNode){
    BinaryNode* foundNode = NULL;
    
    if(*subRoot == *searchNode){
        foundNode = subRoot;
    }
    
    // If we found our node, stop recursion
    // Else, search children
    if(foundNode == NULL){
        if(subRoot->leftChild != NULL){
            foundNode = find_recursive(subRoot->leftChild, searchNode);
            if(foundNode){
                return foundNode;
            }
        }
        if(foundNode == NULL){
            if(subRoot->rightChild != NULL){
                foundNode = find_recursive(subRoot->rightChild, searchNode);
                if(foundNode){
                    return foundNode;
                }
            }
        }
    }
    
    return foundNode;
}

int BinaryHeap::exists(int data){
    BinaryNode searchNode(data);
    int found = 0;
    
    if(!isEmpty()){
        exists_recursive(root,&searchNode,found);
    }
    
    return found;
}

void  BinaryHeap::exists_recursive(BinaryNode* subRoot, BinaryNode* searchNode, int &found){
    // If our root is equal to what we are searching for
    // then we set found to 1.
    if(subRoot == searchNode){
        found = 1;
    }
    
    // If we haven't found the item then search the children
    if(found != 1){
        if(subRoot->leftChild != NULL){
            exists_recursive(subRoot->leftChild, searchNode, found);
        }
        if(subRoot->rightChild != NULL){
            exists_recursive(subRoot->rightChild, searchNode, found);
        }
    }
}

void BinaryHeap::setLast(){
    if(!last){
        BinaryNode* currentNode = root;
        
        // While our node has children we will check
        // to see if it has a right branch. If it doesn't
        // we will set to the left (which it must have).
        while(currentNode->hasChildren()){
            if(currentNode->hasRightChild()){
                currentNode = currentNode->rightChild;
            }
            else{
                currentNode = currentNode->leftChild;
            }
        }
        
        // We've reached a node with no children, our last element.
        last = currentNode;
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

void BinaryHeap::heapify(BinaryNode* subRoot){
    // Since the current element used to be in last, we will assume
    // that all items above it are greater, so we will only check down.
    if(subRoot->hasChildren()){
        if(subRoot > subRoot->leftChild){
            int temp;
            temp = subRoot->data;
            subRoot->data = subRoot->leftChild->data;
            subRoot->leftChild->data = temp;
            subRoot = subRoot->leftChild;
        }
    }
}
