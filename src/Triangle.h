#pragma once
#include <iostream>
#include "Punkt.h"
#include "Ekran.h"
#include "Matrix4x4.h"
#include "WorldToScreen.h"
struct Trojkat {
    Punkt a[3];  // trzy wierzchołki
    void ustaw(float x1, float y1, float z1,float x2, float y2, float z2,float x3, float y3, float z3);  // ustawia trójkąt na ekranie
    void Trainglepushback(float zmiana);
};

std::ostream& operator<<(std::ostream& os, const Trojkat& t);
void ConnectTriangle(const Trojkat& t, Ekran& ekran);
void TransformByMatrixes(Trojkat& t,Matrix4x4 tab[],int NumberOfTransformation);





