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
        break;
        
        case 't':      // Toggle View
        if(viewFront){ viewFront = false; viewSide = true; }
        else if(viewSide){ viewSide = false; viewTop = true; }
        else if(viewTop){ viewTop = false; viewUser = true; }
        else { viewUser = false; viewFront = true; }
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
    
    if(newReader.nodeCount > 0){
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(newReader.nodeList[0].point.x, newReader.nodeList[0].point.y, 0);//newReader.nodeList[0].point.z);
        glVertex3f(newReader.nodeList[1].point.x, newReader.nodeList[1].point.y, 0);//newReader.nodeList[1].point.z);
        glVertex3f(newReader.nodeList[2].point.x, newReader.nodeList[2].point.y, 0);//newReader.nodeList[2].point.z);
        glVertex3f(newReader.nodeList[3].point.x, newReader.nodeList[3].point.y, 0);//newReader.nodeList[3].point.z);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(newReader.nodeList[4].point.x, newReader.nodeList[4].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[5].point.x, newReader.nodeList[5].point.y, 0);//newReader.nodeList[5].point.z);
        glVertex3f(newReader.nodeList[6].point.x, newReader.nodeList[6].point.y, 0);//newReader.nodeList[6].point.z);
        glVertex3f(newReader.nodeList[7].point.x, newReader.nodeList[7].point.y, 0);//newReader.nodeList[7].point.z);
        glEnd();

        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[0].point.x, newReader.nodeList[0].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[4].point.x, newReader.nodeList[4].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
    
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[1].point.x, newReader.nodeList[1].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[5].point.x, newReader.nodeList[5].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
    
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[2].point.x, newReader.nodeList[2].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[6].point.x, newReader.nodeList[6].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
    
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[3].point.x, newReader.nodeList[3].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[7].point.x, newReader.nodeList[7].point.y, 0);//newReader.nodeList[5].point.z);
        
        glBegin(GL_LINE_LOOP);
        glVertex3f(newReader.nodeList[8].point.x, newReader.nodeList[8].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[9].point.x, newReader.nodeList[9].point.y, 0);//newReader.nodeList[5].point.z);
        glVertex3f(newReader.nodeList[10].point.x, newReader.nodeList[10].point.y, 0);//newReader.nodeList[6].point.z);
        glVertex3f(newReader.nodeList[11].point.x, newReader.nodeList[11].point.y, 0);//newReader.nodeList[7].point.z);
        glEnd();
        
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[10].point.x, newReader.nodeList[10].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[13].point.x, newReader.nodeList[13].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
        
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[9].point.x, newReader.nodeList[9].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[11].point.x, newReader.nodeList[11].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
        
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[9].point.x, newReader.nodeList[9].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[13].point.x, newReader.nodeList[13].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();

        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[9].point.x, newReader.nodeList[9].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[12].point.x, newReader.nodeList[12].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
        
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[12].point.x, newReader.nodeList[12].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[11].point.x, newReader.nodeList[11].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
        
        glBegin(GL_LINE);
        glVertex3f(newReader.nodeList[12].point.x, newReader.nodeList[12].point.y, 0);//newReader.nodeList[4].point.z);
        glVertex3f(newReader.nodeList[13].point.x, newReader.nodeList[13].point.y, 0);//newReader.nodeList[5].point.z);
        glEnd();
    }
    output(200,150,"Segment 1");
    
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    
    printf("file name %s \n", filename);
    newReader.openFile(filename);
    newReader.parseDatabase();
    printf("Printing out database \n");
    newReader.printDatabase();
    
//    /* deal with any GLUT command Line options */
//    glutInit(&argc, argv);
//    
//    /* create an output window */
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
//    glutInitWindowSize(800, 800);
//    
//    /* set the name of the window and try to create it */
//    glutCreateWindow("CS 488 - Lab 2 - Andrew Long");
//    
//    /* specify clear values for the color buffers */
//    glClearColor (0.0, 0.0, 0.0, 1.0);
//    
//    /* Receive keyboard inputs */
//    glutKeyboardFunc (Keyboard);
//    
//    /* assign the display function */
//    glutDisplayFunc(display);
//    
//    /* assign the idle function */
//    glutIdleFunc(display);
//    
//    /* sets the reshape callback for the current window */
//    glutReshapeFunc(reshape);
//    
//    /* enters the GLUT event processing loop */
//    glutMainLoop();
    
    
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
    
    
    return (EXIT_SUCCESS);
    
}

