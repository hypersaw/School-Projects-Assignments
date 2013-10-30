Author: Andrew Long
Date: Oct 29th, 2013
Operating System: Macintosh OS X 10.8.4
Compiler: Xcode 5.0.1

*** README ***

This is an unfinished version of Lab 2. What I do have is a working version of the parser included
with the template, a Matrix library (includes a 4x4 Matrix, Cartesian and Homogeneous Vectors), and
a Transform class that would keep track of all of the necessary transformations being made and produce
a single matrix to be applied to each of our data points. Unfortunately, I was not able to sucussfully
bridge the gap from what we learned in class into implementing these pieces using OpenGL, so the program
does not do a whole lot as-is.

IMPORTANT NOTE: Opening this project on your local machine in it's original form will not parse the data
file correctly, as it needs to be directed to your own local directory containing project2.xml. I could
not find a way to get a relative path to work and required the absolute path for it to be opened.