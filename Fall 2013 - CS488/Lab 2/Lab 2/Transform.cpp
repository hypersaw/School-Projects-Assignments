//
//  Transform.cpp
//  Lab 2
//
//  Created by Andrew Long on 10/29/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#include "Transform.h"

Transform::Transform(){
    ClearTransform();
}

void Transform::ClearTransform(){
    translateMatrix = AL4DMatrixIdentity();
    xRotationMatrix = AL4DMatrixIdentity();
    yRotationMatrix = AL4DMatrixIdentity();
    zRotationMatrix = AL4DMatrixIdentity();
    scaleMatrix = AL4DMatrixIdentity();
}

void Transform::Translate(double x, double y, double z){
    translateMatrix = AL4DMatrix(1,0,0,x,
                                 0,1,0,y,
                                 0,0,1,z,
                                 0,0,0,1);
}

void Transform::RotateAroundX(double rotateDegrees){
    xRotationMatrix = AL4DMatrix(1,0,0,0,
                                 0,cos(rotateDegrees),-sin(rotateDegrees),0,
                                 0,sin(rotateDegrees),cos(rotateDegrees),0,
                                 0,0,0,1);
}

void Transform::RotateAroundY(double rotateDegrees){
    yRotationMatrix = AL4DMatrix(cos(rotateDegrees),0,sin(rotateDegrees),0,
                                 0,1,0,0,
                                 -sin(rotateDegrees),0,cos(rotateDegrees),0,
                                 0,0,0,1);
}

void Transform::RotateAroundZ(double rotateDegrees){
    zRotationMatrix = AL4DMatrix(cos(rotateDegrees),-sin(rotateDegrees),0,0,
                                 sin(rotateDegrees),cos(rotateDegrees),0,0,
                                 0,0,1,0,
                                 0,0,0,1);
}

void Transform::Scale(double x, double y, double z){
    scaleMatrix = AL4DMatrix(x,0,0,0,
                             0,y,0,0,
                             0,0,z,0,
                             0,0,0,1);
}