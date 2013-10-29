//
//  XmlReader.h
//  Lab 2
//
//  Created by Andrew Long on 10/29/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#ifndef XMLREADER
#define XMLREADER

#define TRUE = 1;
#define FALSE = 0;
#define VPN = 0;
#define VUP = 1;
#define PRP = 2;
#define VRP = 3;
#define POINT3D = 4;
#define POINT2D = 5;
#define SPHERE = 6;
#define RADIUS = 7;
#define WIREFRAME = 8;
#define LINEDRAW = 9;
#define CYLINDER = 10;

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <string.h>
#include <stdlib.h>

typedef struct Color {
    float r;
    float g;
    float b;
}Color;

typedef struct Point {
    float x;
    float y;
    float z;
}Point;

typedef struct Cylinder {
    Color color;
    Point center;
    float radius;
    float height;
}Cylinder;

typedef struct Sphere {
    Color color;
    Point center;
    float radius;
}Sphere;

typedef struct CononicalVolume {
    float uMin;
    float uMax;
    float vMin;
    float vMax;
    float zMin;  // Front place
    float zMax;  //  Back clipping plane
}CononicalVolume;

typedef struct VRC {
    Point vpn;   // Normalized vector
    Point prp;   // expressed in VRC coordinates
    Point vup;   // Normalized vector
    Point vrp;   // Expressed in global coordinates
}VRC;

typedef struct Node {
    Color color;
    Point point;
}Node;

typedef struct Face {
    Color color;
    Point point;
}Face;

typedef struct Connectivity {
    struct Connectivity *next;
    int id1;
    int id2;
}Connectivity;

class XmlReader{
public:
    int nodeCount;
    int faceCount;
    Cylinder cylinder;
    Sphere sphere;
    CononicalVolume volume;
    VRC vrc;
    
    // Node information
    Connectivity *headEdgePtr = NULL;
    Connectivity *tailEdgePtr = NULL;
    Node *nodeList = NULL;
    Face *faceList = NULL;

    void openFile(const char *fileName);
    void parseDatabase();
    void printDatabase();

private:
    
    xmlDoc *doc;
    xmlNode *head;
    
    int NodeCounter = 0;
    int FaceCounter = 0;

    void parseNode(xmlNode *currPtr,int type);
    void parsePoints(xmlNode *currPtr, int type);
    void parseVRC(xmlNode *ptr);
    void parseLineConnectivity(xmlNode *ptr, int type);
    void parseCononicalVolume(xmlNode *ptr);
    void parseHeight(xmlNode *node, int type);
    void parseColor(xmlNode *ptr, int type);
    void parseRadius(xmlNode *ptr, int type);
    void parseCenter(xmlNode *ptr, int type);
};

#endif