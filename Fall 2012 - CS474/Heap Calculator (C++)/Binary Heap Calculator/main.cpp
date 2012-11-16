//
//  main.cpp
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/6/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#include "BinaryHeap.h"

int main(int argc, const char * argv[])
{
    BinaryNode pNode(5), lNode(6), rNode(4);
    
    pNode.setLeftChild(lNode);
    pNode.setRightChild(rNode);
    
    std::cout << "<CONSOLE> Testing Node Children Check" << std::endl;
    std::cout << "pNode hasChildren: " << pNode.hasChildren() << std::endl;
    std::cout << "pNode hasLeftChild: " << pNode.hasLeftChild() << std::endl;
    std::cout << "pNode hasRightChild: " << pNode.hasRightChild() << std::endl;
    std::cout << std::endl;
    
    std::cout << "<CONSOLE> Testing Node Equality/Comparison" << std::endl;
    std::cout << "pNode == lNode: " << (pNode == lNode) << std::endl;
    std::cout << "lNode > rNode: " << (lNode > rNode) << std::endl;
    std::cout << "lNode < rNode: " << (lNode < rNode) << std::endl;
    std::cout << std::endl;
    
    std::cout << "<CONSOLE> Testing Node Ownership" << std::endl;
    pNode.setLeftChild(lNode);
    pNode.setRightChild(rNode);
    std::cout << "pNode(" << &pNode << ")  lNode(" << &lNode << ")  rNode(" << &rNode << ")" << std::endl;
    std::cout << "pNode hasLeftChild: " << pNode.hasLeftChild() << "(" << pNode.leftChild << ")" << std::endl;
    std::cout << "pNode hasRightChild: " << pNode.hasRightChild() << "(" << pNode.rightChild << ")" << std::endl;
    std::cout << "lNode hasParent: " << lNode.hasParent() << "(" << lNode.parent << ")" << std::endl;
    std::cout << "rNode hasParent: " << rNode.hasParent() << "(" << rNode.parent << ")" << std::endl;
    std::cout << "lNode hasSibling: " << lNode.hasSibling() << std::endl;
    std::cout << "rNode hasSibling: " << rNode.hasSibling() << std::endl;
    std::cout << "lNode isLeftChild: " << lNode.isLeftChild() << std::endl;
    std::cout << "lNode isRightChild: " << lNode.isRightChild() << std::endl;
    std::cout << "rNode isLeftChild: " << rNode.isLeftChild() << std::endl;
    std::cout << "rNode isRightChild: " << rNode.isRightChild() << std::endl;
    std::cout << "rNode > rNode->parent: " << (rNode > *rNode.parent) << std::endl;
    std::cout << "lNode > lNode->parent: " << (lNode > *lNode.parent) << std::endl;
    std::cout << std::endl;
    
    std::cout << "<CONSOLE> Adding Items to Heap" << std::endl;
    
    BinaryHeap aHeap;
    std::cout << "Adding 1..." << std::endl; aHeap.add(1);
    std::cout << "Adding 2..." << std::endl; aHeap.add(2);
    std::cout << "Adding 3..." << std::endl; aHeap.add(3);
    std::cout << "Adding 4..." << std::endl; aHeap.add(4);
    std::cout << "Adding 5..." << std::endl; aHeap.add(5);
    std::cout << "Adding 6..." << std::endl; aHeap.add(6);
    std::cout << "Adding 7..." << std::endl; aHeap.add(7);
    std::cout << "Adding 8..." << std::endl; aHeap.add(8);
    std::cout << "<CONSOLE> Added 8 Items to Heap" << std::endl;
    std::cout << std::endl;
    
    std::cout << "<CONSOLE> Display Heap" << std::endl;
    aHeap.display();
    std::cout << std::endl;
    
    std::cout << "<CONSOLE> Checking Heap 'exists' Method" << std::endl;
    std::cout << "1 Exists: " << aHeap.exists(1) << std::endl;
    std::cout << "2 Exists: " << aHeap.exists(2) << std::endl;
    std::cout << "5 Exists: " << aHeap.exists(5) << std::endl;
    std::cout << "7 Exists: " << aHeap.exists(7) << std::endl;
    std::cout << "9 Exists: " << aHeap.exists(9) << std::endl;
    std::cout << std::endl;
    
    getchar();
    std::cout << "<CONSOLE> Exiting. Goodbye." << std::endl;
    return 0;
}

