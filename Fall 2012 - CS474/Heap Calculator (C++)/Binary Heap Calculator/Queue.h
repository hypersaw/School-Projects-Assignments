//
//  Queue.h
//  Binary Heap Calculator
//
//  Created by Andrew Long on 11/6/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#ifndef QUEUE
#define QUEUE

#include <stdlib.h>

template <class Type>
class Queue{
public:
    Queue();
    ~Queue();
    
    void enqueue(Type* data);
    Type dequeue();
    int itemCount();
    bool isEmpty();
    
private:
    class QueueItem{
    public:
        QueueItem();
        
        QueueItem(Type data);
        QueueItem(const QueueItem& otherItem);
    
        Type data;
        QueueItem* nextItem;
    };

    QueueItem* first;
    int count;
};

template <class Type>
Queue<Type>::Queue(){
    first = NULL;
    count = 0;
}

template <class Type>
Queue<Type>::~Queue(){

}

template <class Type>
void Queue<Type>::enqueue(Type* data){
    QueueItem* newItem;
    newItem = new QueueItem(*data);
    
    if(!isEmpty()){
        QueueItem* current = first;
        while(current->nextItem != NULL){
            current = current->nextItem;
        }
        
        current->nextItem = newItem;
    }
    else{
        first = newItem;
    }
    
    ++count;
}

template <class Type>
Type Queue<Type>::dequeue(){
    if(!isEmpty()){
        QueueItem* returnItem;
        returnItem = new QueueItem(*first);

        delete first;
        first = returnItem->nextItem;
        --count;
        
        return returnItem->data;
    }

    return NULL;
}

template <class Type>
int Queue<Type>::itemCount(){
    return count;
}

template <class Type>
bool Queue<Type>::isEmpty(){
    return (first == NULL);
}

template <class Type>
Queue<Type>::QueueItem::QueueItem(){
    data = NULL;
    nextItem = NULL;
}

template <class Type>
Queue<Type>::QueueItem::QueueItem(Type newData){
    data = newData;
    nextItem = NULL;
}

template <class Type>
Queue<Type>::QueueItem::QueueItem(const QueueItem& otherItem){
    data = otherItem.data;
    nextItem = otherItem.nextItem;
}

#endif