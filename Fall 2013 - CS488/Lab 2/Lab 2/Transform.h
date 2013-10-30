//
//  Transform.h
//  Lab 2
//
//  Created by Andrew Long on 10/29/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#ifndef TRANSFORM
#define TRANSFORM

#include <iostream>
#include <math.h>
#include "ALMatrix.h"

// Object that holds all of the relevant transformations being made
// and returns a matrix that applies all necessary transformations into one
// to be used across a series of points.
class Transform{
public:
    Transform();
    
    void ClearTransform();
    
    void Translate(double x, double y, double z);
    void RotateAroundX(double rotateDegrees);
    void RotateAroundY(double rotateDegrees);
    void RotateAroundZ(double rotateDegrees);
    void Scale(double x, double y, double z);
private:
    AL4DMatrix translateMatrix;         // Translate Matrix
    AL4DMatrix xRotationMatrix;         // X Rotate Matrix
    AL4DMatrix yRotationMatrix;         // Y Rotate Matrix
    AL4DMatrix zRotationMatrix;         // Z Rotate Matrix
    AL4DMatrix scaleMatrix;             // Scale Matrix
};


#endif