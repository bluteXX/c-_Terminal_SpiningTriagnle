#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

const int wysokosci = 25;  
const int szerokosci = 80;

struct Punkt { float x, y; };

struct Kwadrat {
    Punkt a[4];
    void ustaw(float x, float y, float bok) {
        a[0] = {x, y};
        a[1] = {x + bok, y};
        a[2] = {x + bok, y + bok};
        a[3] = {x, y + bok};
    }
};

ostream& operator<<(ostream& os, const Kwadrat& k) {
    for (int i = 0; i < 4; i++)
        os << "Punkt " << i << ": (" << k.a[i].x << ", " << k.a[i].y << ")\n";
    return os;
}

void ConnectTwoPoint(Punkt p1, Punkt p2, char ekran[wysokosci][szerokosci]) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float steps = max(abs(dx), abs(dy));
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = p1.x;
    float y = p1.y;
    for (int i = 0; i <= steps; i++) {
        int xi = static_cast<int>(x);
        int yi = static_cast<int>(y);
        if (xi >= 0 && xi < szerokosci && yi >= 0 && yi < wysokosci)
            ekran[yi][xi] = '*';
        x += xInc;
        y += yInc;
    }
}

void ConnectSquare(const Kwadrat& k, char ekran[wysokosci][szerokosci]) {
    for (int i = 0; i < 4; i++)
        ConnectTwoPoint(k.a[i], k.a[(i + 1) % 4], ekran);
}

void InicjalizujEkran(char ekran[wysokosci][szerokosci]) {
    for (int i = 0; i < wysokosci; i++)
        for (int j = 0; j < szerokosci; j++)
            ekran[i][j] = ' ';
}

void Wypisz(char ekran[wysokosci][szerokosci]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPos); 

    for (int i = 0; i < wysokosci; i++) {
        for (int j = 0; j < szerokosci; j++)
            cout << ekran[i][j];
        cout << endl;
    }
}

int main() {
    char ekran[wysokosci][szerokosci];
    InicjalizujEkran(ekran);

    Kwadrat k1;
    k1.ustaw(5,5, 5);
    ConnectSquare(k1, ekran);

    while (1) {
        Wypisz(ekran);
        Sleep(100); 
    }

    return 0;
}
