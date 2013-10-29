//
//  ALMatrix.h
//  Lab 2
//
//  Created by Andrew Long on 10/29/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#ifndef ALMATRIX
#define ALMATRIX

#include <stdlib.h>
#include <stdio.h>

class ALHomogeneousVector;
class ALCartesianVector;

class AL4DMatrix{
public:
    AL4DMatrix(double v0, double v1, double v2, double v3,
               double v4, double v5, double v6, double v7,
               double v8, double v9, double v10, double v11,
               double v12, double v13, double v14, double v15);
    AL4DMatrix();
    ~AL4DMatrix();
    
    const AL4DMatrix operator*(const AL4DMatrix& rhs) const;
    const ALHomogeneousVector operator*(const ALHomogeneousVector& rhs) const;
    const double operator()(const int rIndex, const int cIndex) const;
    AL4DMatrix& operator=(const AL4DMatrix& rhs);

    void Display();

private:
    double** _values;

    const double At(const int row, const int column) const { return _values[row][column]; }

};

class ALCartesianVector {
public:
    ALCartesianVector(double x, double y, double z);
    ALCartesianVector(ALHomogeneousVector hVector);
    ALCartesianVector();
    
    int operator[](const int index) const;

private:
    double _x;
    double _y;
    double _z;
    
};

class ALHomogeneousVector {
public:
    ALHomogeneousVector(double x, double y, double z, double w);
    ALHomogeneousVector(ALCartesianVector cVector);
    ALHomogeneousVector();
    
    int operator[](const int index) const;
    void Display() { printf("(%f, %f, %f, %f)^T\n",_x,_y,_z,_w); }

private:
    double _x;
    double _y;
    double _z;
    double _w;
    
};

AL4DMatrix AL4DMatrixIdentity();

#endif
