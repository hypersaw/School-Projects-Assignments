//
//  util.cpp
//  Lab 1
//
//  Created by Andrew Long on 9/26/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#include "util.h"


/*
    Finds the slope between two al2DCoord points
*/
float al2DSlope(al2DCoord p1, al2DCoord p2){
    return (p1.getX()-p2.getX())/(p1.getY()-p2.getY());
}

alCoordinateList::alCoordinateList(){
    origin = nullptr;
    end = nullptr;
    numCoord = 0;
}

alCoordinateList::~alCoordinateList(){
    if(numCoord >= 1){
        Coord* currentCoord = origin;
        for(int i = 1; i < numCoord; ++i){
            Coord* temp = currentCoord;
            currentCoord = currentCoord->next;
            delete temp;
        }
        delete currentCoord;
    }
}

/*
    Adds a al2DCoord to our list at the end
*/
void alCoordinateList::addCoordinate(al2DCoord new2DCoord){
    Coord* newCoord = new Coord(new2DCoord);
    
    if(origin == nullptr){
        origin = newCoord;
        end = newCoord;
        numCoord = 1;
    }
    else{
        newCoord->prev = end;
        newCoord->next = origin;
        end->next = newCoord;
        end = newCoord;
        ++numCoord;
    }
}

/*
    Returns an al2DCoord from our coordinate list at index
*/
al2DCoord alCoordinateList::getCoord(int index){
    if(origin == nullptr){
        exit(EXIT_FAILURE);
    }
    else{
        while(index < 0){
            index += numCoord;
        }
        Coord* currentCoord = origin;
        for(int i = 1; i <= index; ++i){
            currentCoord = currentCoord->next;
        }
        
        return al2DCoord(currentCoord->x,currentCoord->y);
    }
}

alActiveEdgeListEntry::alActiveEdgeListEntry(){
    yMax = 0;
    xBot = 0;
    slope = 0;
    nextEntry = nullptr;
    valid = false;
}

alActiveEdgeListEntry::alActiveEdgeListEntry(float y, float x, float s){
    yMax = y;
    xBot = x;
    slope = s;
    nextEntry = nullptr;
    valid = true;
}

alActiveEdgeList::alActiveEdgeList(){
    edgeList = nullptr;
}

/*
    Adds an entry to our AEL at a given y value
*/
void alActiveEdgeList::addEntry(alActiveEdgeListEntry newEntry, int yMin){
    if(edgeList == nullptr) exit(EXIT_FAILURE);
    
    if(edgeList[yMin].isValid()){
        alActiveEdgeListEntry *currentEntry = &edgeList[yMin];
        while(currentEntry->nextEntry != nullptr){
            currentEntry = currentEntry->nextEntry;
        }
        currentEntry->nextEntry = &newEntry;
    }
    else{
        edgeList[yMin] = newEntry;
    }
}

/*
    Defines the maximum Y value for our AEL
    Note: Required to be called prior to using the AEL
*/
void alActiveEdgeList::defineMaxY(int size){
    if(this->edgeList != nullptr){
        delete [] this->edgeList;
    }
    
    maxY = size;
    this->edgeList = new alActiveEdgeListEntry[size];
}

alPolygon::alPolygon(){
}

/*
    Draws the entire polygon by calling drawLine
    on the provided coordinates
*/
void alPolygon::draw(bool fill, float xOff, float yOff){
    if(coordinates.getCount() > 1){
        if(fill){
            alActiveEdgeList *edgeList = createEdgeTable();
            //edgeList->printList();
            
            alActiveEdgeListEntry activeEntries;
            alActiveEdgeListEntry *temp, *prev;
            
            for(int yScanline = 0; yScanline < edgeList->entryCount(); ++yScanline){
                // Check to see if any entries have expired
                if(activeEntries.isValid()){
                    temp = &activeEntries;
                    prev = nullptr;
                    while(temp != nullptr){
                        if(temp->getYMax() == yScanline){
                            if(prev == nullptr){
                                temp = temp->nextEntry;
                            }
                            else{
                                prev->nextEntry = temp->nextEntry;
                                temp = prev;
                            }
                        }
                        else{
                            prev = temp;
                            temp = temp->nextEntry;
                        }
                    }
                }
                
                // Check to see if any new entries exists here
                alActiveEdgeListEntry currentEntry = edgeList->getEntry(yScanline);
                if(currentEntry.isValid()){
                    if(!activeEntries.isValid()){
                        activeEntries = currentEntry;
                    }
                    else{
                        temp = &activeEntries;
                        while(temp->nextEntry != nullptr) temp = temp->nextEntry;
                        temp->nextEntry = &currentEntry;
                    }
                }
                
                if(activeEntries.isValid()){
                    prev = &activeEntries;
                    do{
                        // Draw lines in pairs
                        temp = prev->nextEntry;
                        int x0, x1;
                        x0 = prev->getXBot() + prev->getSlope(); prev->adjustXBot();
                        x1 = temp->getXBot() + prev->getSlope(); temp->adjustXBot();
                        drawLine(x0+xOff, yScanline+yOff, x1+xOff, yScanline+yOff);
                        
                        prev = temp->nextEntry;
                    }while(prev != nullptr);
                }
            }
        }
        else{
            al2DCoord origin = coordinates.getCoord(0);
            
            float xOrigin = origin.getX() + xOff;
            float yOrigin = origin.getY() + yOff;
            float x0 = xOrigin, y0 = yOrigin, x1, y1;
            
            for(int i = 1; i <= coordinates.getCount(); ++i){
                al2DCoord newVertex = coordinates.getCoord(i);
                x1 = newVertex.getX() + xOff;
                y1 = newVertex.getY() + yOff;
                
                drawLine(x0, y0, x1, y1);
                x0 = x1;
                y0 = y1;
            }
            
            drawLine(x1, y1, xOrigin, yOrigin);
        }
    }
}

/*
    Draws a line between two coordinates
*/
void alPolygon::drawLine(float x0, float y0, float x1, float y1){
    float dy = y1-y0;
    float dx = x1-x0;
    float m = dy/dx;
    float y = y0;
    
    // Vertical Line
    if(dx == 0){
        // Bottom to Top
        if(y0 < y1){
            for(int y = y0; y <= y1; y++){
                glVertex2f(x0, y);
            }
        }
        // Top to Bottom
        else{
            for(int y = y0; y >= y1; y--){
                glVertex2f(x0, y);
            }
        }
    }
    // Horizontal Line
    else if(dy == 0){
        // Right to Left
        if(x0 < x1){
            for(int x = x0; x <= x1; x++){
                glVertex2f(x, y0);
            }
        }
        else{
            for(int x = x0; x >= x1; x--){
                glVertex2f(x, y0);
            }
        }
    }
    // All Other Lines
    else{
        // Right to Left
        if(x0 < x1){
            for(int x = x0; x <= x1; x++){
                glVertex2f(x,(int)y);
                y += m;
            }
        }
        // Left to Right
        else{
            for(int x = x0; x >= x1; x--){
                glVertex2f(x,(int)y);
                y -= m;
            }
        }
    }
}

/*
    Iterates through the coordinates and creates an AEL
*/
alActiveEdgeList* alPolygon::createEdgeTable(){
    alActiveEdgeList *newList = new alActiveEdgeList;
    
    int minIndex = 0;
    float minY = 99999;
    float maxY = 0;
    
    // Find the lowest vertex
    for(int i = 0; i < coordinates.getCount(); ++i){
        al2DCoord currentCoord = coordinates.getCoord(i);
        if(minY > currentCoord.getY()){
            minIndex = i;
            minY = currentCoord.getY();
        }
        if(maxY < currentCoord.getY()){
            maxY = currentCoord.getY();
        }
    }
    
    // Create our edge table to be as big as we need
    newList->defineMaxY((int)maxY);
    
    int index = minIndex;
    do{
        int nextIndex = index + 1;
        if(nextIndex == coordinates.getCount()) nextIndex = 0;
        
        al2DCoord p1 = coordinates.getCoord(index);
        al2DCoord p2 = coordinates.getCoord(nextIndex);
        
        // p1 is yMIN
        if(p1.getY() < p2.getY()){
            alActiveEdgeListEntry newEntry(p2.getY(),p1.getX(),al2DSlope(p1,p2));
            newList->addEntry(newEntry,(int)p1.getY());
        }
        else if(p2.getY() < p1.getY()){
            alActiveEdgeListEntry newEntry(p1.getY(),p2.getX(),al2DSlope(p2,p1));
            newList->addEntry(newEntry,(int)p2.getY());
        }
        
        index = nextIndex;
    }while(index != minIndex);
    
    return newList;
}

/* 
 Used for debugging purposes to print out the AEL
*/
void alActiveEdgeList::printList(){
    for(int i = 0; i < maxY; ++i){
        if(edgeList[i].isValid()){
            printf("Entry at edgeList[%d] = (%f,%f,%f)",i,edgeList[i].getYMax(),edgeList[i].getXBot(),edgeList[i].getSlope());
            
            int j = 1;
            alActiveEdgeListEntry *temp;
            temp = edgeList[i].nextEntry;
            while(temp != nullptr){
                printf(", (%f,%f,%f)",temp->getYMax(),temp->getXBot(),temp->getSlope());
                temp = temp->nextEntry;
            }
            printf("\n");
        }
        else{
            printf("Entry at edgeList[%d] = NULL\n",i);
        }
    }
}
