//
//  BinaryNode.h
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/6/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef BINARYNODE
#define BINARYNODE

#include <stdlib.h>

class BinaryNode {
public:
    BinaryNode();
    BinaryNode(int data);
    ~BinaryNode();
    
    BinaryNode* parent;
    BinaryNode* leftChild;
    BinaryNode* rightChild;
    int data;
    
    void setRightChild(BinaryNode& newRightChild);
    void setLeftChild(BinaryNode& newLeftChild);
    void setData(int data);
    
    bool hasChildren();
    bool hasLeftChild();
    bool hasRightChild();
    bool hasParent();
    bool hasSibling();
    
    bool isLeftChild();
    bool isRightChild();
    bool isRoot();
    
    bool operator==(const BinaryNode& rhs) const;
    bool operator>(const BinaryNode& rhs) const;
    bool operator<(const BinaryNode& rhs) const;
};

#endif