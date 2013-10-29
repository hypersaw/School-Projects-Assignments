/*
 * File:   main.cpp
 * Author: Andrew Long
 *
 * Date: Sep 26th, 2013
 *
 * Operating System: Macintosh OS X 10.8.4
 * Compiler: Xcode 4.6.3
 *
 * Press key 'a' and 'd' to cycle through my name (in rad 80's style), a house, and a filled house
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
#include "util.h"


/* Intialization of the sign of drawing graphics */
bool drawName = true;
bool drawHouse = false;
bool drawFilled = false;

/*******************************************************************/

/* 
    Draws a line between two 2D coordinates
    If origin is true we define what our origin is and return (act of placing the pen down)
    Additionally, if origin is true then we can also define an offset for x and y (to plot points in local space)
    Each sequential call to drawLine will then draw a line to the defined coordinate of (x,y)
*/
void drawLine(float x, float y, bool origin = false, float xOff = 0, float yOff = 0){
    static float xOrigin, yOrigin;
    static float xOffset, yOffset;
    static float hasOrigin = false;
    
    if(origin){
        xOrigin = x + xOffset; yOrigin = y + yOffset;
        xOffset = xOff; yOffset = yOff;
        hasOrigin = true;
    }
    else if(!origin && !hasOrigin){
        exit(EXIT_FAILURE);
    }
    else{
        float x0 = xOrigin; float x1 = x+ xOffset;
        float y0 = yOrigin; float y1 = y + yOffset;
    
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
    
    xOrigin = x + xOffset;
    yOrigin = y + yOffset;
}

/*
    "Nicer"/More intuitive way of defining when to start a line
    Ex. startLine(15.0, 100.0); drawLine(25.0, 100.0) 
                            vs.
        drawLine(15.0, 100.0, true); drawLine(25.0, 100.0)
*/
void startLine(float x, float y, float xOffset = 0, float yOffset = 0){
    drawLine(x, y, true, xOffset, yOffset);
}

/*
    Draws a circle given an origin and a radius
    if the fill parameter is set then we will fill in the circle
*/
void drawCircle(float xCenter, float yCenter, float r, bool fill = false){
    //drawArc(x, y, r, 0, 360);
    int x = 0;
    int y = r;
    double d = 5.0 / 4.0 - r;
    glVertex2f(x+xCenter, y+yCenter);
    
    while(y > x){
        if(d < 0)
            d += 2.0 * x + 3.0;
        else{
            d += 2.0 * (x - y) + 5.0;
            y--;
        }
        x++;
        int xPoint = x+xCenter; int xPointO = yCenter+x; int xPointN = xCenter - x; int xPointNO = yCenter - x;
        int yPoint = y+yCenter; int yPointO = xCenter+y; int yPointN = yCenter - y; int yPointNO = xCenter - y;
        if(fill){
            float yScanline = yPoint;
            for(int fillX = xPointN; fillX < xPoint; fillX++) glVertex2f(fillX, yScanline);
            
            yScanline = yPointN;
            for(int fillX = xPointN; fillX < xPoint; fillX++) glVertex2f(fillX, yScanline);
            
            yScanline = xPointO;
            for(int fillX = yPointNO; fillX < yPointO; fillX++) glVertex2f(fillX, yScanline);
            
            yScanline = xPointNO;
            for(int fillX = yPointNO; fillX < yPointO; fillX++) glVertex2f(fillX, yScanline);
            
            yScanline = yCenter;
            for(int fillX = xCenter - r; fillX < xCenter + r; fillX++) glVertex2f(fillX, yScanline);
        }
        else{
            glVertex2f(xPoint,yPoint); glVertex2f(xPointN,yPoint);
            glVertex2f(xPoint,yPointN); glVertex2f(xPointN,yPointN);
            glVertex2f(yPointO,xPointO); glVertex2f(yPointNO,xPointO);
            glVertex2f(yPointO,xPointNO); glVertex2f(yPointNO,xPointNO);
        }
    }

}

/*
    Used to begin a polygon "act of placing the pen down"
    Note: Has since been replaced by the alPolygon class
*/
void startPolygon(float x, float y, float xOffset = 0, float yOffset = 0){
    
}

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
            
		case 'd':      // Draw Name
			if(drawName){ drawName = false; drawHouse = true; }
            else if(drawHouse){ drawHouse = false; drawFilled = true; }
            else{ drawFilled = false; drawName = true; }
			break;
            
		case 'a':      // Draw House
			if(drawName){ drawName = false; drawFilled = true; }
            else if(drawHouse){ drawHouse = false; drawName = true; }
            else{ drawFilled = false; drawHouse = true; }
            break;
	}
}


/******************************************************************/

void display(void) {
	/* clear the screen to the clear colour */
	glClear(GL_COLOR_BUFFER_BIT);
    

    if (drawName == true){
		float xOrigin = 20.0, yOrigin = 200.0;
        float charSpacing = 120.0;
		
        float sRed = 1.0, sGreen = 0.6, sBlue = 0.0;
        float dRed = -0.12, dGreen = -0.12, dBlue = 0.167;
        glBegin(GL_POINTS);
        glPointSize(10.0);
        
        /* A */
        glColor3f(sRed,sGreen,sBlue); // Set Point Color
        xOrigin += charSpacing;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(0.0, 200.0); drawLine(100.0, 200.0); drawLine(100.0, 0.0);
        drawLine(75.0, 0.0); drawLine(75.0, 100.0); drawLine(50.0, 100.0);
        drawLine(50.0, 0.0); drawLine(0.0, 0.0);
        startLine(50.0, 125.0, xOrigin, yOrigin);
        drawLine(75.0, 125.0); drawLine(75.0, 175.0); drawLine(50.0, 175.0);
        drawLine(50.0, 125.0);
        
        /* n */
        glColor3f(sRed+=dRed,sGreen+=dGreen,sBlue+=dBlue); // Set Point Color
        xOrigin += charSpacing;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(0.0, 100.0); drawLine(50.0, 100.0); drawLine(75.0, 50.0);
        drawLine(75.0, 100.0); drawLine(100.0, 100.0); drawLine(100.0, 0.0);
        drawLine(75.0, 0.0); drawLine(50.0, 50.0); drawLine(50.0, 0.0);
        drawLine(0.0, 0.0);
        
        /* d */
        glColor3f(sRed+=dRed,sGreen+=dGreen,sBlue+=dBlue); // Set Point Color
        xOrigin += charSpacing;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(75.0, 0.0); drawLine(100.0, 50.0);
        drawLine(75.0, 100.0); drawLine(0.0,100.0); drawLine(0.0, 0.0);
        startLine(50.0, 25.0, xOrigin, yOrigin);
        drawLine(60.0, 25.0); drawLine(75.0, 50.0); drawLine(60.0, 75.0);
        drawLine(50.0, 75.0); drawLine(50.0, 25.0);
        
        /* r */
        glColor3f(sRed+=dRed,sGreen+=dGreen,sBlue+=dBlue); // Set Point Color
        xOrigin += charSpacing;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(0.0, 100.0); drawLine(100.0, 100.0); drawLine(100.0, 50.0);
        drawLine(50.0, 50.0); drawLine(100.0, 0.0); drawLine(75.0, 0.0);
        drawLine(50.0, 25.0); drawLine(50.0, 0.0); drawLine(0.0, 0.0);
        startLine(50.0, 65.0, xOrigin, yOrigin);
        drawLine(50.0, 85.0); drawLine(75.0, 85.0); drawLine(75.0, 65.0);
        drawLine(50.0, 65.0);
        
        /* e */
        glColor3f(sRed+=dRed,sGreen+=dGreen,sBlue+=dBlue); // Set Point Color
        xOrigin += charSpacing;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(0.0, 100.0); drawLine(100.0, 100.0); drawLine(100.0, 80.0);
        drawLine(50.0, 80.0); drawLine(50.0, 60.0); drawLine(100.0, 60.0);
        drawLine(100.0, 40.0); drawLine(50.0, 40.0); drawLine(50.0, 20.0);
        drawLine(100.0, 20.0); drawLine(100.0, 0.0); drawLine(0.0, 0.0);
        
        /* w */
        glColor3f(sRed+=dRed,sGreen+=dGreen,sBlue+=dBlue); // Set Point Color
        xOrigin += charSpacing;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(100.0, 0.0);
        drawLine(100.0, 75.0); drawLine(125.0, 75.0); drawLine(150.0, 100.0); drawLine(85.0, 100.0);
        drawLine(85.0, 25.0); drawLine(80.0, 25.0); drawLine(80.0, 100.0); drawLine(55.0, 100.0);
        drawLine(55.0, 25.0); drawLine(50.0, 25.0); drawLine(50.0, 100.0); drawLine(0.0, 100.0); drawLine(0.0, 0.0);
                
        /* underline */
        glColor3f(sRed+1.0, sGreen+1.0, sBlue+1.0);
        xOrigin = 140.0; yOrigin -= 50.0;
        startLine(0.0, 0.0 , xOrigin, yOrigin);
        drawLine(15.0, 0.0);
        drawLine(30.0, 25.0);
        drawLine(15.0, 25.0);
        drawLine(0.0, 0.0);
        
        glColor3f(sRed+0.6, sGreen+0.6, sBlue+0.6);
        xOrigin += 25.0;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(15.0, 0.0);
        drawLine(30.0, 25.0);
        drawLine(15.0, 25.0);
        drawLine(0.0, 0.0);
        
        glColor3f(sRed+0.2, sGreen+0.2, sBlue+0.2);
        xOrigin += 25.0;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(15.0, 0.0);
        drawLine(30.0, 25.0);
        drawLine(15.0, 25.0);
        drawLine(0.0, 0.0);
        
        glColor3f(sRed, sGreen, sBlue);
        xOrigin += 25.0;
        startLine(0.0, 0.0, xOrigin, yOrigin);
        drawLine(675.0, 0.0);
        drawLine(675.0, 135.0);
        drawLine(650.0, 110.0);
        drawLine(650.0, 25.0);
        drawLine(15.0, 25.0);
        drawLine(0.0, 0.0);
        
        
        
        glEnd();
        
		glColor3f(1.0, 1.0, 1.0);
		output(20,20,"Name");
	}
    
	if (drawHouse == true){
		glBegin(GL_POINTS);
        
        /* House base */
        glColor3f(1.0, 0.0, 0.0);
        float xHouseLoc = 300.0, yHouseLoc = 150.0;

        alPolygon houseBase;
        houseBase.addVertex(al2DCoord(0.0,0.0));
        houseBase.addVertex(al2DCoord(300.0,0.0));
        houseBase.addVertex(al2DCoord(300.0,200.0));
        houseBase.addVertex(al2DCoord(0.0,200.0));
        houseBase.draw(false, xHouseLoc, yHouseLoc);
        
        /* House roof */
        glColor3f(0.7, 1.0, 0.7);
        alPolygon houseRoof;
        houseRoof.addVertex(al2DCoord(350.0, 0.0));
        houseRoof.addVertex(al2DCoord(325.0, 100.0));
        houseRoof.addVertex(al2DCoord(25.0, 100.0));
        houseRoof.addVertex(al2DCoord(0.0, 0.0));
        houseRoof.draw(false, xHouseLoc-25.0, yHouseLoc+200.0);
        
        /* House window */
        glColor3f(0.0, 0.0, 1.0);
        drawCircle(xHouseLoc+100, yHouseLoc+100, 50.0);
        
        /* House door */
        glColor3f(0.5, 0.25, 0.0);
        alPolygon houseDoor;
        houseDoor.addVertex(al2DCoord(0.0, 125.0));
        houseDoor.addVertex(al2DCoord(75.0, 125.0));
        houseDoor.addVertex(al2DCoord(75.0, 0.0));
        houseDoor.addVertex(al2DCoord(0.0, 0.0));
        houseDoor.draw(false, xHouseLoc+201.0, yHouseLoc);

        /* House door knob */
        glColor3f(1.0, 1.0, 0.0);
        drawCircle(xHouseLoc+265.0, yHouseLoc+50.0, 5.0);
        
        /* Tree base */
        glColor3f(0.5, 0.25, 0.0);
        alPolygon treeBase;
        treeBase.addVertex(al2DCoord(50.0, 0.0));
        treeBase.addVertex(al2DCoord(50.0, 150.0));
        treeBase.addVertex(al2DCoord(0.0, 150.0));
        treeBase.addVertex(al2DCoord(0.0, 0.0));
        treeBase.draw(false, xHouseLoc+350.0, yHouseLoc);
        
        /* Tree trap */
        glColor3f(0.0, 0.9, 0.1);
        alPolygon treeTrap;
        treeTrap.addVertex(al2DCoord(100.0, 0.0));
        treeTrap.addVertex(al2DCoord(75.0, 25.0));
        treeTrap.addVertex(al2DCoord(25.0, 25.0));
        treeTrap.addVertex(al2DCoord(0.0, 0.0));
        treeTrap.draw(false, xHouseLoc+325.0, yHouseLoc+150.0);
        
        /* Tree tri */
        alPolygon treeTri;
        treeTri.addVertex(al2DCoord(100.0, 0.0));
        treeTri.addVertex(al2DCoord(50.0, 50.0));
        treeTri.addVertex(al2DCoord(0.0, 0.0));
        treeTri.draw(false, xHouseLoc+325.0, yHouseLoc+175.0);
        
		glEnd();
        
		glColor3f(1.0, 1.0, 1.0);
		output(20,20,"House");
	}
    
    if (drawFilled == true){
		glBegin(GL_POINTS);
        
        /* House base */
        glColor3f(1.0, 0.0, 0.0);
        float xHouseLoc = 300.0, yHouseLoc = 150.0;
        
        alPolygon houseBase;
        houseBase.addVertex(al2DCoord(0.0,0.0));
        houseBase.addVertex(al2DCoord(300.0,0.0));
        houseBase.addVertex(al2DCoord(300.0,200.0));
        houseBase.addVertex(al2DCoord(0.0,200.0));
        houseBase.draw(true, xHouseLoc, yHouseLoc);
        
        /* House roof */
        glColor3f(0.7, 1.0, 0.7);
        alPolygon houseRoof;
        houseRoof.addVertex(al2DCoord(350.0, 0.0));
        houseRoof.addVertex(al2DCoord(325.0, 100.0));
        houseRoof.addVertex(al2DCoord(25.0, 100.0));
        houseRoof.addVertex(al2DCoord(0.0, 0.0));
        houseRoof.draw(true, xHouseLoc-25.0, yHouseLoc+200.0);
        
        /* House window */
        glColor3f(0.0, 0.0, 1.0);
        drawCircle(xHouseLoc+100, yHouseLoc+100, 50.0, true);
        
        /* House door */
        glColor3f(0.5, 0.25, 0.0);
        alPolygon houseDoor;
        houseDoor.addVertex(al2DCoord(0.0, 125.0));
        houseDoor.addVertex(al2DCoord(75.0, 125.0));
        houseDoor.addVertex(al2DCoord(75.0, 0.0));
        houseDoor.addVertex(al2DCoord(0.0, 0.0));
        houseDoor.draw(true, xHouseLoc+201.0, yHouseLoc);
        
        /* House door knob */
        glColor3f(1.0, 1.0, 0.0);
        drawCircle(xHouseLoc+265.0, yHouseLoc+50.0, 5.0, true);
        
        /* Tree base */
        glColor3f(0.5, 0.25, 0.0);
        alPolygon treeBase;
        treeBase.addVertex(al2DCoord(50.0, 0.0));
        treeBase.addVertex(al2DCoord(50.0, 150.0));
        treeBase.addVertex(al2DCoord(0.0, 150.0));
        treeBase.addVertex(al2DCoord(0.0, 0.0));
        treeBase.draw(true, xHouseLoc+350.0, yHouseLoc);
        
        /* Tree trap */
        glColor3f(0.0, 0.9, 0.1);
        alPolygon treeTrap;
        treeTrap.addVertex(al2DCoord(100.0, 0.0));
        treeTrap.addVertex(al2DCoord(75.0, 25.0));
        treeTrap.addVertex(al2DCoord(25.0, 25.0));
        treeTrap.addVertex(al2DCoord(0.0, 0.0));
        treeTrap.draw(true, xHouseLoc+325.0, yHouseLoc+150.0);
        
        /* Tree tri */
        alPolygon treeTri;
        treeTri.addVertex(al2DCoord(100.0, 0.0));
        treeTri.addVertex(al2DCoord(50.0, 50.0));
        treeTri.addVertex(al2DCoord(0.0, 0.0));
        treeTri.draw(true, xHouseLoc+325.0, yHouseLoc+175.0);
        
		glEnd();
        
		glColor3f(1.0, 1.0, 1.0);
		output(20,20,"Filled");
	}
    
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
	glutInitWindowSize(1024, 576);
    
	/* set the name of the window and try to create it */
    glutCreateWindow("CS 488 - Lab 1 - Andrew Long");
    
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
