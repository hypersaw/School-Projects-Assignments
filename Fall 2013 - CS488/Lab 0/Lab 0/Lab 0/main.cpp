/*
 * File:   SampleMain.cpp
 * Author: Chihua Ma
 *
 * Date: Sep 1st, 2012
 *
 * Operating System: Windows 7 64-bit
 * Compiler: Visual Studio 2010
 *
 * Press key 's' to display square, and key 't' to display triangle
 */


#ifdef WIN32
#define WINDOWS
#elif WIN64
#define WINDOWS
#endif
#ifdef WINDOWS
#include <windows.h>  // Without include this header in Windows, you will get error C2381: 'exit' : redefinition; __declspec(noreturn) differs
#endif


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* Intialization of the sign of drawing graphics */
bool drawSquare = true;
bool drawTriangle = false;

/******************************************************************/

/* output code by Mark Kilgard */
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
            
		case 's':      // Draw Square
			drawSquare = true;
			drawTriangle = false;
			break;
            
		case 't':      // Draw Triangle
			drawSquare = false;
			drawTriangle = true;
			break;
	}
}


/******************************************************************/

void display(void) {
	/* clear the screen to the clear colour */
	glClear(GL_COLOR_BUFFER_BIT);
    
	// draw a red square
    if (drawSquare == true) {
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POLYGON); // in the first lab assignment, you can only use GL_POINT
        glVertex2f(200.0, 200.0);
        glVertex2f(200.0, 300.0);
        glVertex2f(300.0, 300.0);
        glVertex2f(300.0, 200.0);
		glEnd();
        
		glColor3f(1.0, 1.0, 1.0);
		output(200,150,"Square");
	}
    
	// draw a triangle with a white, red, and blue corner
	if (drawTriangle == true) {
		glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(180, 220);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(280, 400);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(300, 200);
		glEnd();
        
		glColor3f(1.0, 1.0, 1.0);
		output(200,150,"Triangle");
	}
    
    /* swap buffers */
    glutSwapBuffers();
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

/*******************************************************************/

int main(int argc, char** argv) {
    
	/* deal with any GLUT command Line options */
    glutInit(&argc, argv);
    
	/* create an output window */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
    
	/* set the name of the window and try to create it */
    glutCreateWindow("CS 488 - Sample");
    
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

