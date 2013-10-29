Author: Andrew Long
Date: Sep 26th, 2013
Operating System: Macintosh OS X 10.8.4
Compiler: Xcode 4.6.3

*** README ***

In this assignment I have used various simple algorithms to draw lines and circles (in the form of letters, a house, and a filled house). The algorithms used were influenced by those used within our textbook ("Computer Graphics: Principles and Practice 2nd Edition", Foley) and modified to better suit my needs.

The method used to draw polygons however takes two different shapes. Multiple iterations of this project have been made to allow for an easier and more intuitive environment to draw lines. For my name, I used two methods to achieve an image. By calling startLine, we tell the computer to start connecting coordinates (coordinates that are fed in with drawLine afterwards). We will continue to draw lines until startLine has been called again, which moves the laser/pen to another location and waits for more coordinates. 

However, once I began to tackle the polygon fill algorith, I realized this wouldn't work so well. To remedy this, I began to create objects that handled drawing themselves. The alPolygon (Andrew Long Polygon) is easier to read since there is no "startPolygon", rather you just feed in vertexs and call draw. This allows for similair objects to be redrawn over and over again with consectuive draw calls with various offsets, freeing the programmer from redefining coordinates in the local space over and over.

To solve the fill problem I used an Active Edge List like we learned in lecture. I query the polygons coordinates and add entries into the AEL (using alActiveEdgeListEntry objects). After the table has been created, it is simply a matter of iterating through various y values and calculating where our next x coordinate will be and drawing/filling between those two points.