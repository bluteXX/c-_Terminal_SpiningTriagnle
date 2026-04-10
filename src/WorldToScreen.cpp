#include <iostream>
#include "Punkt.h"
#include "Matrix4x4.h"
void MapToScreen(Punkt &p) {
    int j = static_cast<int>((p.x + 1.0f) / 2.0f * (szerokosci - 1));
    int i = static_cast<int>((1.0f - p.y) / 2.0f * (wysokosci - 1));

    if (j < 0) j = 0;
    if (j >= szerokosci) j = szerokosci - 1;
    if (i < 0) i = 0;
    if (i >= wysokosci) i = wysokosci - 1;

    p.x = j;
    p.y = i;
}
void DrawLine3D(Punkt v1, Punkt v2, Ekran& ekran) {
    // UWAGA: v1 i v2 muszą mieć już policzone 'w' (przez MultiplyXvector w main)
    
    float nearPlane = 0.1f; // Minimalna odległość od kamery

    // 1. CLIPPING (Przycinanie) na podstawie 'w'
    bool v1_out = v1.w < nearPlane;
    bool v2_out = v2.w < nearPlane;

    // Jeśli obie za kamerą -> odrzucamy
    if (v1_out && v2_out) return;

    // Jeśli linia przecina kamerę -> przycinamy
    if (v1_out || v2_out) {
        Punkt in  = v1_out ? v2 : v1; // Widoczny
        Punkt out = v1_out ? v1 : v2; // Niewidoczny

        // Interpolacja
        float t = (nearPlane - in.w) / (out.w - in.w);

        Punkt clipped;
        clipped.x = in.x + t * (out.x - in.x);
        clipped.y = in.y + t * (out.y - in.y);
        clipped.z = in.z + t * (out.z - in.z);
        clipped.w = nearPlane;

        if (v1_out) v1 = clipped;
        else        v2 = clipped;
    }

    // 2. PERSPECTIVE DIVIDE (Dzielenie przez W)
    // To robimy dopiero tutaj, po przycięciu!
    v1.x /= v1.w; 
    v1.y /= v1.w; 
    // v1.z /= v1.w; // opcjonalne

    v2.x /= v2.w; 
    v2.y /= v2.w;
    // v2.z /= v2.w;

    // 3. MAPOWANIE NA EKRAN
    MapToScreen(v1); // Twoja funkcja mapująca (korzystająca z szerokosci/wysokosci)
    MapToScreen(v2);

    // 4. RYSOWANIE
    ConnectTwoPoint(v1, v2, ekran);
}