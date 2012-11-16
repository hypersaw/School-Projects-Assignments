//
//  BinaryNode.cpp
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/6/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "BinaryNode.h"

BinaryNode::BinaryNode(){
    parent = NULL;
    data = NULL;
    leftChild = NULL;
    rightChild = NULL;
}

BinaryNode::BinaryNode(int newData){
    parent = NULL;
    data = newData;
    leftChild = NULL;
    rightChild = NULL;
}

BinaryNode::~BinaryNode(){
    // Since we automatically make connections when we use
    // the setXChild methods, we need to clean up the ties
    if(hasParent()){
        if(isLeftChild()){
            parent->leftChild = NULL;
        }
        else{
            parent->rightChild = NULL;
        }
    }
}

void BinaryNode::setLeftChild(BinaryNode &newLeftChild){
    this->leftChild = &newLeftChild;
    newLeftChild.parent = this;
}

void BinaryNode::setRightChild(BinaryNode &newRightChild){
    this->rightChild = &newRightChild;
    newRightChild.parent = this;
}

void BinaryNode::setData(int newData){
    this->data = newData;
}

bool BinaryNode::hasChildren(){
    if(leftChild == NULL & rightChild == NULL){
        return false;
    }
    
    return true;
}

bool BinaryNode::hasLeftChild(){
    return (leftChild != NULL);
}

bool BinaryNode::hasRightChild(){
    return (rightChild != NULL);
}

bool BinaryNode::hasParent(){
    return (parent != NULL);
}

bool BinaryNode::hasSibling(){
    bool sibling = false;
    
    if(hasParent()){
        if(parent->leftChild == this){
            if(parent->rightChild != NULL){
                sibling = true;
            }
        }
        else{
            if(parent->leftChild != NULL){
                sibling = true;
            }
        }
    }
    
    return sibling;
}

bool BinaryNode::isLeftChild(){
    if(hasParent()){
        return (this == parent->leftChild);
    }
    
    return false;
}

bool BinaryNode::isRightChild(){
    if(hasParent()){
        return (this == parent->rightChild);
    }
    
    return false;
}

bool BinaryNode::isRoot(){
    return (parent == NULL);
}

bool BinaryNode::operator==(const BinaryNode &rhs) const{
    return (this->data == rhs.data);
}

bool BinaryNode::operator>(const BinaryNode &rhs) const{
    return (this->data > rhs.data);
}

bool BinaryNode::operator<(const BinaryNode &rhs) const{
    return (this->data < rhs.data);
}
