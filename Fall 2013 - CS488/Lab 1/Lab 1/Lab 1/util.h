//
//  util.h
//  Lab 1
//
//  Created by Andrew Long on 9/26/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#ifndef Lab_1_util_h
#define Lab_1_util_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

/*
    A two dimensional coordinate
*/
class al2DCoord{
private:
    float _x;
    float _y;

public:
    al2DCoord(float x, float y) { _x = x; _y = y; }
    float getX() { return _x; }
    float getY() { return _y; }
};

/*
    A collection of al2DCoord objects
*/
class alCoordinateList{
public:
    class Coord{
    public:
        float x; float y;
        Coord(al2DCoord newCoord){
            next = nullptr;
            x = newCoord.getX();
            y = newCoord.getY();
        }
        Coord* next;
        Coord* prev;
    };
    
    alCoordinateList();
    ~alCoordinateList();
    
    void addCoordinate(al2DCoord newCoord);
    al2DCoord getCoord(int index);
    int getCount() { return numCoord; }
    
private:
    Coord* origin;
    Coord* end;
    int numCoord;
};

/*
    A single entry for an Active Edge List that
    holds information about the Ymax, Xbot, and Slope
    Note: Check isValid prior to using an entry to
    ensure it is a usuable entry
*/
class alActiveEdgeListEntry{
public:
    alActiveEdgeListEntry();
    alActiveEdgeListEntry(float y, float x, float s);
    float getYMax() { return yMax; }
    float getXBot() { return xBot; }
    float getSlope() { return slope; }
    void adjustXBot() { xBot += slope; }
    bool isValid() { return valid; }
    
    alActiveEdgeListEntry *nextEntry;
private:
    float yMax;
    float xBot;
    float slope;
    bool valid;
};

/*
    A collection of Active Edge List Entries used to draw polygons
*/
class alActiveEdgeList{
public:
    alActiveEdgeList();
    void addEntry(alActiveEdgeListEntry newEntry, int yMin);
    void defineMaxY(int y);
    float entryCount() { return maxY; }
    alActiveEdgeListEntry getEntry(int index) { return edgeList[index]; }
    void printList();
    
private:
    float maxY;
    alActiveEdgeListEntry *edgeList;
};


/*
    A polygon class, used to draw polygons by defining
    coordinates using addVertex(al2DCoord) followed
    by calling draw(bool,float,float)
*/
class alPolygon{
public:
    alPolygon();
    void addVertex(al2DCoord newVertex) { coordinates.addCoordinate(newVertex); }
    void draw(bool fill, float xOff = 0, float yOff = 0);
    
private:
    alCoordinateList coordinates;
    
    void drawLine(float x0, float y0, float x1, float y1);
    alActiveEdgeList* createEdgeTable();
};


#endif
