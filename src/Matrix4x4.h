#pragma once
#include "Punkt.h"
struct Matrix4x4 {

    float m[4][4];  

};
Matrix4x4 PerspectiveMatrix(float l, float r, float b, float t, float n, float f);

Punkt MultiplyXvector(const Matrix4x4& mat, const Punkt p); 
Punkt SetOFTransformation(Matrix4x4 MatrixTab[],int NumberOfTransformation,Punkt p);//Do a set of transformation in order set in input 
Matrix4x4 RotateYMatrixCenter(float angleRad, Punkt center);
Matrix4x4 RotateXMatrix(float angleRad);
Matrix4x4 Multiply(const Matrix4x4 &a, const Matrix4x4 &b);
Matrix4x4 TranslationMatrix(float tx, float ty, float tz);
