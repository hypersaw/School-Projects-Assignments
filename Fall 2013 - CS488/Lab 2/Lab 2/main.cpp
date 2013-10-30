/*
 * File:   SampleMain.cpp
 * Author: Chihua Ma
 *
 * Date: Oct 5th, 2013
 *
 * Operating System: Windows 7 64-bit
 * Compiler: Visual Studio 2010
 */

#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "XmlReader.h"
#include "ALMatrix.h"

const char * filename = "/Users/andrew/Documents/School-Projects-Assignments/Fall 2013 - CS488/Lab 2/Lab 2/project2.xml";  // Opens the XML file based on the entire pathname "filename"

bool    viewFront = true,
        viewSide = false,
        viewTop = false,
        viewUser = false;

XmlReader newReader;

void output(int x, int y, char *string)
{
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    //cout<<key<<endl;
    switch (key)
    {
        case 27:       //ESCAPE key
        exit(0);
        break;
        
        case 'r':      // Rotate around Y-Axis
            glRotatef(90, 0, 1, 0);
        break;
        
        case 't':      // Toggle View
            if(viewFront){ viewFront = false; viewSide = true; }
            else if(viewSide){ viewSide = false; viewTop = true; }
            else if(viewTop){ viewTop = false; viewUser = true; }
            else { viewUser = false; viewFront = true; }
            
            if(viewTop) gluLookAt(0, 250, 250, 0, 0, 0, 0, 0, 1);
            if(viewFront) { gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0); glMatrixMode(GL_PROJECTION); }
            printf("Front: %d\tSide: %d\tTop: %d\tUser: %d\n",viewFront,viewSide,viewTop,viewUser);
        break;
            
        case 'i':       // Zoom in
        break;
        
        case 'o':       // Zoom out
        break;
    }
}

void reshape (int w, int h) {
    /* set the viewport */
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    /* Matrix for projection transformation */
    glMatrixMode (GL_PROJECTION);
    
    /* replaces the current matrix with the identity matrix */
    glLoadIdentity ();
    
    /* Define a 2d orthographic projection matrix */
    gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void display(void) {
    /* clear the screen to the clear colour */
    glClear(GL_COLOR_BUFFER_BIT);
    
//    if(newReader.nodeCount > 0){
//        glColor3f(1.0, 1.0, 1.0);
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(newReader.nodeList[0].point.x+40*10, newReader.nodeList[0].point.x+40*10, newReader.nodeList[0].point.z+40*10);   // 10, 10, -10
//        glVertex3f(newReader.nodeList[1].point.x+40*10, newReader.nodeList[1].point.x+40*10, newReader.nodeList[1].point.z+40*10);   // 40, 10, -10
//        glVertex3f(newReader.nodeList[2].point.x+40*10, newReader.nodeList[2].point.x+40*10, newReader.nodeList[2].point.z+40*10);   // 40, 10, -30
//        glVertex3f(newReader.nodeList[3].point.x+40*10, newReader.nodeList[3].point.x+40*10, newReader.nodeList[3].point.z+40*10);   // 10, 10, -30
//        glEnd();
//
//        glColor3f(0.0, 1.0, 1.0);
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(newReader.nodeList[4].point.x+40*10, newReader.nodeList[4].point.x+40*10, newReader.nodeList[4].point.z+40*10);   // 10, 15, -10
//        glVertex3f(newReader.nodeList[5].point.x+40*10, newReader.nodeList[5].point.x+40*10, newReader.nodeList[5].point.z+40*10);   // 40, 15, -10
//        glVertex3f(newReader.nodeList[6].point.x+40*10, newReader.nodeList[6].point.x+40*10, newReader.nodeList[6].point.z+40*10);   // 40, 15, -30
//        glVertex3f(newReader.nodeList[7].point.x+40*10, newReader.nodeList[7].point.x+40*10, newReader.nodeList[7].point.z+40*10);   // 10, 15, -30
//        glEnd();
//
//        glColor3f(1.0, 0.0, 1.0);
//        glBegin(GL_LINES);
//        glVertex3f(newReader.nodeList[0].point.x+40*10, newReader.nodeList[0].point.x+40*10, newReader.nodeList[0].point.z+40*10);   // 10, 10, -10
//        glVertex3f(newReader.nodeList[4].point.x+40*10, newReader.nodeList[4].point.x+40*10, newReader.nodeList[4].point.z+40*10);   // 10, 15, -10
//
//        glVertex3f(newReader.nodeList[1].point.x+40*10, newReader.nodeList[1].point.x+40*10, newReader.nodeList[1].point.z+40*10);   // 40, 10, -10
//        glVertex3f(newReader.nodeList[5].point.x+40*10, newReader.nodeList[5].point.x+40*10, newReader.nodeList[5].point.z+40*10);   // 40, 15, -10
//        
//        glVertex3f(newReader.nodeList[2].point.x+40*10, newReader.nodeList[2].point.x+40*10, newReader.nodeList[2].point.z+40*10);   // 40, 10, -30
//        glVertex3f(newReader.nodeList[6].point.x+40*10, newReader.nodeList[6].point.x+40*10, newReader.nodeList[6].point.z+40*10);   // 40, 15, -30
//        
//        glVertex3f(newReader.nodeList[3].point.x+40*10, newReader.nodeList[3].point.x+40*10, newReader.nodeList[3].point.z+40*10);   // 10, 10, -30
//        glVertex3f(newReader.nodeList[7].point.x+40*10, newReader.nodeList[7].point.x+40*10, newReader.nodeList[7].point.z+40*10);   // 10, 15, -30
//        glEnd();
//        
//        glColor3f(1.0, 1.0, 0.0);
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(newReader.nodeList[8].point.x+40*10, newReader.nodeList[8].point.x+40*10, newReader.nodeList[8].point.z+40*10);   // 20, 40, -20
//        glVertex3f(newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.z+40*10);   // 20, 35, -20
//        glVertex3f(newReader.nodeList[10].point.x+40*10, newReader.nodeList[10].point.x+40*10, newReader.nodeList[10].point.z+40*10);// 20, 30, -15
//        glVertex3f(newReader.nodeList[11].point.x+40*10, newReader.nodeList[11].point.x+40*10, newReader.nodeList[11].point.z+40*10);// 25, 30, -20
//        glEnd();
//        
//        glColor3f(0.0, 0.0, 1.0);
//        glBegin(GL_LINES);
//        glVertex3f(newReader.nodeList[10].point.x+40*10, newReader.nodeList[10].point.x+40*10, newReader.nodeList[10].point.z+40*10);// 20, 30, -15
//        glVertex3f(newReader.nodeList[13].point.x+40*10, newReader.nodeList[13].point.x+40*10, newReader.nodeList[13].point.z+40*10);// 15, 30, -20
//
//        glVertex3f(newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.z+40*10);   // 20, 35, -20
//        glVertex3f(newReader.nodeList[11].point.x+40*10, newReader.nodeList[11].point.x+40*10, newReader.nodeList[11].point.z+40*10);// 25, 30, -20
//        
//        glVertex3f(newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.z+40*10);   // 20, 35, -20
//        glVertex3f(newReader.nodeList[13].point.x+40*10, newReader.nodeList[13].point.x+40*10, newReader.nodeList[13].point.z+40*10);// 15, 30, -20
//        
//        glVertex3f(newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.x+40*10, newReader.nodeList[9].point.z+40*10);   // 20, 35, -20
//        glVertex3f(newReader.nodeList[12].point.x+40*10, newReader.nodeList[12].point.x+40*10, newReader.nodeList[12].point.z+40*10);// 20, 30, -25
//        
//        glVertex3f(newReader.nodeList[12].point.x+40*10, newReader.nodeList[12].point.x+40*10, newReader.nodeList[12].point.z+40*10);// 20, 30, -25
//        glVertex3f(newReader.nodeList[11].point.x+40*10, newReader.nodeList[11].point.x+40*10, newReader.nodeList[11].point.z+40*10);// 25, 30, -20
//        
//        glVertex3f(newReader.nodeList[12].point.x+40*10, newReader.nodeList[12].point.x+40*10, newReader.nodeList[12].point.z+40*10);// 20, 30, -25
//        glVertex3f(newReader.nodeList[13].point.x+40*10, newReader.nodeList[13].point.x+40*10, newReader.nodeList[13].point.z+40*10);// 15, 30, -20
//        glEnd();
//    }

    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3i(250,250,0);
    glVertex3i(500,250,0);
    glVertex3i(500,500,0);
    glVertex3i(250,500,0);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3i(250, 375, 0);
    glVertex3i(500, 375, 0);
    glVertex3i(250, 375, 250);
    glVertex3i(250, 375, 0);
    glEnd();
    
    output(200,150,"Segment 1");
    
    glutSwapBuffers();
}

void testALMatrix(){
    ALHomogeneousVector hVector(2,2,2,1);
    
    AL4DMatrix aMatrix(2,2,2,2,
                       2,2,2,2,
                       2,2,2,2,
                       2,2,2,2);
    
    AL4DMatrix bMatrix(1,0,0,0,
                       0,1,0,0,
                       0,0,1,0,
                       0,0,0,1);
    
    ALHomogeneousVector result = aMatrix * hVector;
    result.Display();
    
    AL4DMatrix result2 = aMatrix * 2;
    result2.Display();
    
    result2 = 2 * aMatrix;
    result2.Display();
}


int main(int argc, char** argv) {
    
    printf("file name %s \n", filename);
    newReader.openFile(filename);
    newReader.parseDatabase();
    printf("Printing out database \n");
    newReader.printDatabase();
    
    /* deal with any GLUT command Line options */
    glutInit(&argc, argv);
    
    /* create an output window */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800, 800);
    
    /* set the name of the window and try to create it */
    glutCreateWindow("CS 488 - Lab 2 - Andrew Long");
    
    /* specify clear values for the color buffers */
    glClearColor (0.0, 0.0, 0.0, 1.0);
    
    /* Receive keyboard inputs */
    glutKeyboardFunc (Keyboard);
    
    /* assign the display function */
    glutDisplayFunc(display);
    
    /* assign the idle function */
    glutIdleFunc(display);
    
    /* sets the reshape callback for the current window */
    glutReshapeFunc(reshape);
    
    /* enters the GLUT event processing loop */
    glutMainLoop();
    
    return (EXIT_SUCCESS);
    
}

