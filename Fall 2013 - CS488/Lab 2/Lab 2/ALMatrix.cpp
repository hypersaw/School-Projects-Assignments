//
//  AL4DMatrix.cpp
//  Lab 2
//
//  Created by Andrew Long on 10/29/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#include "ALMatrix.h"

AL4DMatrix::AL4DMatrix(double v0, double v1, double v2, double v3,
                             double v4, double v5, double v6, double v7,
                             double v8, double v9, double v10, double v11,
                             double v12, double v13, double v14, double v15){
    _values = new double*[4];
    for(int i = 0; i < 4; ++i) _values[i] = new double[4];
    _values[0][0] = v0;
    _values[0][1] = v1;
    _values[0][2] = v2;
    _values[0][3] = v3;
    _values[1][0] = v4;
    _values[1][1] = v5;
    _values[1][2] = v6;
    _values[1][3] = v7;
    _values[2][0] = v8;
    _values[2][1] = v9;
    _values[2][2] = v10;
    _values[2][3] = v11;
    _values[3][0] = v12;
    _values[3][1] = v13;
    _values[3][2] = v14;
    _values[3][3] = v15;
}

AL4DMatrix::AL4DMatrix(){
    _values = new double*[4];
    for(int i = 0; i < 4; ++i) _values[i] = new double[4];
}

AL4DMatrix::~AL4DMatrix(){
    for(int i = 0; i < 4; ++i){
        delete _values[i];
    }

    delete _values;
}

const double AL4DMatrix::operator()(const int rIndex, const int cIndex) const{
    return At(rIndex,cIndex);
}

const AL4DMatrix AL4DMatrix::operator*(const AL4DMatrix& rhs) const{
    // Can we multiply these two?
    double** newVals;
    
    newVals = new double*[4];
    for(int i = 0; i < 4; ++i){
        newVals[i] = new double[4];
    }
    
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            newVals[i][j] = 0;
            for(int k = 0; k < 4; ++k){
                //printf("newVals[%d][%d] += (%f * %f)\n",i,j,(*this)(k,j),rhs(i,k));
                newVals[i][j] += ((*this)(k,j) * rhs(i,k));
            }
        }
    }
    
    AL4DMatrix result(newVals[0][0],newVals[0][1],newVals[0][2],newVals[0][3],
                      newVals[1][0],newVals[1][1],newVals[1][2],newVals[1][3],
                      newVals[2][0],newVals[2][1],newVals[2][2],newVals[2][3],
                      newVals[3][0],newVals[3][1],newVals[3][2],newVals[3][3]);
    
    for(int i = 0; i < 4; ++i){
        delete newVals[i];
    }
    
    delete newVals;
    
    return result;
}

const ALHomogeneousVector AL4DMatrix::operator*(const ALHomogeneousVector& rhs) const{
    double result[4];
    for(int i = 0; i < 4; ++i){
        result[i] = 0;
        for(int k = 0; k < 4; ++k){
            //printf("newVals[%d][%d] += (%f * %f)\n",i,j,(*this)(k,j),rhs(i,k));
            result[i] += ((*this)(i,k) * rhs[k]);
        }
    }
    
    return ALHomogeneousVector(result[0],result[1],result[2],result[3]);
}

AL4DMatrix& AL4DMatrix::operator=(const AL4DMatrix& rhs) {
    // 1.  Deallocate any memory that MyClass is using internally
    // 2.  Allocate some memory to hold the contents of rhs
    // 3.  Copy the values from rhs into this instance
    // 4.  Return *this
    if(&rhs == this) return *this;
    
    // Erase current contents
    for(int i = 0; i < 4; ++i){
        delete _values[i];
    }
    delete _values;
    
    _values = new double*[4];
    for(int i = 0; i < 4; ++i){
        _values[i] = new double[4];
    }
    
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            _values[i][j] = rhs(i,j);
        }
    }
    
    return *this;
}

void AL4DMatrix::Display(){
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            printf("%f\t",_values[i][j]);
        }
        printf("\n");
    }
}



ALCartesianVector::ALCartesianVector(double x, double y, double z){
    _x = x;
    _y = y;
    _z = z;
}

ALCartesianVector::ALCartesianVector(ALHomogeneousVector hVector){
    _x = hVector[0]/hVector[3];
    _y = hVector[1]/hVector[3];
    _z = hVector[2]/hVector[3];
}

int ALCartesianVector::operator[](const int index) const{
    if(index == 0) return _x;
    else if(index == 1) return _y;
    else if(index == 2) return _z;
    
    return 0;
}

ALHomogeneousVector::ALHomogeneousVector(double x, double y, double z, double w){
    _x = x;
    _y = y;
    _z = z;
    _w = w;
}

ALHomogeneousVector::ALHomogeneousVector(ALCartesianVector cVector){
    _x = cVector[0];
    _y = cVector[1];
    _z = cVector[2];
    _w = 1;
}

int ALHomogeneousVector::operator[](const int index) const{
    if(index == 0) return _x;
    else if(index == 1) return _y;
    else if(index == 2) return _z;
    else if(index == 3) return _w;
    
    return 0;
}



AL4DMatrix AL4DMatrixIdentity(){
    return AL4DMatrix(1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      0,0,0,1);
}