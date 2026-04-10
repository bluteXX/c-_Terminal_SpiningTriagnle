#pragma once
#include "Punkt.h"
#include "Matrix4x4.h"

class Kamera
{


public:
    // konstruktor inicjalizujący kamerę
    Kamera(Punkt startPosition);

    // generuje macierz widoku na podstawie Location, LookAt i WhereUp
    Matrix4x4 GetViewMatrix() const;

    // obrót kamery w lewo/prawo
    void LookLeft(float angleRad);
    void LookRight(float angleRad);

    // ruch wzdłuż kierunku patrzenia
    void MoveStraight(float distance);
    void MoveBack(float distance);

    // opcjonalnie: gettery do Location i LookAt
    Punkt GetLocation() const { return Location; }
    Punkt GetLookAt() const { return LookAt; }
    private:
    Punkt LookAt;      // punkt, na który patrzy kamera
    Punkt Location;    // pozycja kamery
    Punkt WhereUp;     // wektor góry (Y)
    Matrix4x4 ViewMatrix; // aktualna macierz widoku
};
