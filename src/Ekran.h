#pragma once
#include "rozmiary.h"
#include <iostream>

class Ekran {
public:
    Ekran();
    ~Ekran() = default;

    // Zabroń kopiowania
    Ekran(const Ekran&) = delete;
    Ekran& operator=(const Ekran&) = delete;

    void InicjalizujEkran();
    bool LightPixel(int x, int y, char znak);
    void Wypisz() const;
    

private:
    char ekran[wysokosci][szerokosci];
    
};
