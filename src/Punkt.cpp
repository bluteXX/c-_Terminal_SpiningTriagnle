#include "Punkt.h"
#include <algorithm> // dla std::max
#include <cstdlib>   // dla abs()


void ConnectTwoPoint(Punkt p1, Punkt p2, Ekran& ekran) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float steps = std::max(std::fabs(dx), std::fabs(dy));
    if (steps == 0) { // ten sam punkt
        int xi = static_cast<int>(p1.x);
        int yi = static_cast<int>(p1.y);
        if (xi >= 0 && xi < szerokosci && yi >= 0 && yi < wysokosci)
            ekran.LightPixel(xi,yi,'*');
        return;
    }
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = p1.x;
    float y = p1.y;

    for (int i = 0; i <= steps; i++) {
        int xi = static_cast<int>(std::round(x));
        int yi = static_cast<int>(std::round(y));
        if (xi >= 0 && xi < szerokosci && yi >= 0 && yi < wysokosci)
            ekran.LightPixel(xi,yi,'*');
        x += xInc;
        y += yInc;
    }
}
Punkt Cross(const Punkt& a, const Punkt& b) {
    return Punkt{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
