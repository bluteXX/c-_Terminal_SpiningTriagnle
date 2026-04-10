#include <iostream>
#include "Kamera.h"

#include "Punkt.h"
#include "Matrix4x4.h"

Kamera::Kamera(Punkt startLocation)
{
    Location = startLocation;
    LookAt = Punkt{0,0,1};
    WhereUp = Punkt{0.0f, 1.0f, 0.0f}; 

    // macierz jednostkowa
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ViewMatrix.m[i][j] = (i == j) ? 1.0f : 0.0f;
}
void Kamera::MoveBack(float delta)
{

    // 1. Oblicz wektor kierunku (Gdzie patrzę?)
    Punkt forward = LookAt - Location;
    
    // 2. Znormalizuj go (żeby długość kroku była stała, niezależna od odległości LookAt)
    float len = std::sqrt(forward.x*forward.x + forward.y*forward.y + forward.z*forward.z);
    if (len > 0.0001f) {
        forward = forward * (1.0f / len);
    }

    // 3. Przesuń ZARÓWNO kamerę, jak i cel patrzenia
    Punkt step = forward * delta;
    Location += step;
    LookAt += step; // <-- TO JEST KLUCZOWE! "Niesiemy" punkt patrzenia ze sobą
}

void Kamera::MoveStraight(float delta)
{
    // To samo co wyżej, tylko odejmujemy krok
    Punkt forward = LookAt - Location;
    float len = std::sqrt(forward.x*forward.x + forward.y*forward.y + forward.z*forward.z);
    if (len > 0.0001f) {
        forward = forward * (1.0f / len);
    }

    Punkt step = forward * delta;
    Location -= step;
    LookAt -= step; // <-- Tutaj też przesuwamy oba
}

void Kamera::LookLeft(float angleRad)
{
    // Obrót punktu LookAt wokół Location (czyli rozglądamy się stojąc w miejscu)
    Matrix4x4 rot = RotateYMatrixCenter(-angleRad, Location);
    LookAt = MultiplyXvector(rot, LookAt);
}

void Kamera::LookRight(float angleRad)
{
    // To samo w drugą stronę
    Matrix4x4 rot = RotateYMatrixCenter(angleRad, Location);
    LookAt = MultiplyXvector(rot, LookAt);
}
Matrix4x4 Kamera::GetViewMatrix() const
{
    Punkt f = LookAt - Location; // forward
    float len = std::sqrt(f.x*f.x + f.y*f.y + f.z*f.z);
    f = f * (1.0f / len);        // normalizacja

    Punkt up = WhereUp;
    // opcjonalnie: normalizacja up
    len = std::sqrt(up.x*up.x + up.y*up.y + up.z*up.z);
    up = up * (1.0f / len);

    // s = f x up (cross product)
    Punkt s{
        f.y * up.z - f.z * up.y,
        f.z * up.x - f.x * up.z,
        f.x * up.y - f.y * up.x
    };
    // normalizacja s
    len = std::sqrt(s.x*s.x + s.y*s.y + s.z*s.z);
    s = s * (1.0f / len);

    // u = s x f
    Punkt u{
        s.y * f.z - s.z * f.y,
        s.z * f.x - s.x * f.z,
        s.x * f.y - s.y * f.x
    };

    Matrix4x4 view{};
    // wypełniamy macierz 4x4
    view.m[0][0] = s.x; view.m[0][1] = s.y; view.m[0][2] = s.z; view.m[0][3] = - (s.x*Location.x + s.y*Location.y + s.z*Location.z);
    view.m[1][0] = u.x; view.m[1][1] = u.y; view.m[1][2] = u.z; view.m[1][3] = - (u.x*Location.x + u.y*Location.y + u.z*Location.z);
    view.m[2][0] = -f.x; view.m[2][1] = -f.y; view.m[2][2] = -f.z; view.m[2][3] = f.x*Location.x + f.y*Location.y + f.z*Location.z;
    view.m[3][0] = 0; view.m[3][1] = 0; view.m[3][2] = 0; view.m[3][3] = 1;

    return view;
}
