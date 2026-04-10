#include "Ekran.h"

Ekran::Ekran() {
    InicjalizujEkran();
}

void Ekran::InicjalizujEkran() {
    for (int i = 0; i < wysokosci; i++)
        for (int j = 0; j < szerokosci; j++)
            ekran[i][j] = ' ';
}

bool Ekran::LightPixel(int x, int y, char znak) {
    if (x < 0 || x >= szerokosci || y < 0 || y >= wysokosci) return false;
    ekran[y][x] = znak; 
    return true;
}


void Ekran::Wypisz() const {
   
    std::cout << "\033[H"; 
    
    std::string buffer;
    buffer.reserve((szerokosci + 1) * wysokosci); 

    for (int i = 0; i < wysokosci; i++) {
        for (int j = 0; j < szerokosci; j++) {
            buffer += ekran[i][j];
        }
        buffer += '\n';
    }
    std::cout << buffer;
}

