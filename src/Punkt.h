#pragma once
#include <iostream>
#include <cmath>
#include "rozmiary.h"
#include "Ekran.h"

struct Punkt {
        float x, y, z, w=1;
    


    // mnożenie przez skalar
    Punkt operator*(float s) const {
        return Punkt{x * s, y * s, z * s};
    }

    // dodawanie z przypisaniem
    Punkt& operator+=(const Punkt& p) {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    // odejmowanie z przypisaniem (przydatne dla MoveBack)
    Punkt& operator-=(const Punkt& p) {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }

    // opcjonalnie: operator- i operator+ zwracające nowy Punkt
    Punkt operator+(const Punkt& p) const {
        return Punkt{x + p.x, y + p.y, z + p.z};
    }

    Punkt operator-(const Punkt& p) const {
        return Punkt{x - p.x, y - p.y, z - p.z};
    }
};

void ConnectTwoPoint(Punkt p1, Punkt p2, Ekran& ekran);
Punkt Cross(const Punkt& a, const Punkt& b);


