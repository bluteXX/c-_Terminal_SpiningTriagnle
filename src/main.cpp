#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

#include "Matrix4x4.h"
#include "Triangle.h"
#include "Ekran.h"
#include "rozmiary.h"
#include "WorldToScreen.h"
#include "Kamera.h"

// Konfiguracja terminala (Non-blocking mode)
void SetTerminalRawMode(termios& oldt) {
    termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); 
    newt.c_cc[VMIN] = 0;  
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void RestoreTerminalMode(termios& oldt) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int main() {
    Ekran ekran;
    Kamera kamera(Punkt{0.0f, 0.0f, 0.0f});
    Trojkat trojkaty[12];

    // Przód (z = 0.5)
    trojkaty[0].ustaw(-0.5f,-0.5f,0.5f,   0.5f,-0.5f,0.5f,    0.5f,0.5f,0.5f);
    trojkaty[1].ustaw(-0.5f,-0.5f,0.5f,   0.5f,0.5f,0.5f,    -0.5f,0.5f,0.5f);
    
    // Tył (z = -0.5)
    trojkaty[2].ustaw(-0.5f,-0.5f,-0.5f,   0.5f,0.5f,-0.5f,    0.5f,-0.5f,-0.5f);
    trojkaty[3].ustaw(-0.5f,-0.5f,-0.5f,  -0.5f,0.5f,-0.5f,   0.5f,0.5f,-0.5f);
    
    // Lewo (x = -0.5)
    trojkaty[4].ustaw(-0.5f,-0.5f,-0.5f,  -0.5f,-0.5f,0.5f,   -0.5f,0.5f,0.5f);
    trojkaty[5].ustaw(-0.5f,-0.5f,-0.5f,  -0.5f,0.5f,0.5f,    -0.5f,0.5f,-0.5f);
    
    // Prawo (x = 0.5)
    trojkaty[6].ustaw(0.5f,-0.5f,-0.5f,    0.5f,0.5f,0.5f,     0.5f,-0.5f,0.5f);
    trojkaty[7].ustaw(0.5f,-0.5f,-0.5f,    0.5f,0.5f,-0.5f,    0.5f,0.5f,0.5f);
    
    // Dół (y = -0.5)
    trojkaty[8].ustaw(-0.5f,-0.5f,-0.5f,   0.5f,-0.5f,0.5f,    0.5f,-0.5f,-0.5f);
    trojkaty[9].ustaw(-0.5f,-0.5f,-0.5f,  -0.5f,-0.5f,0.5f,    0.5f,-0.5f,0.5f);
    
    // Góra (y = 0.5)
    trojkaty[10].ustaw(-0.5f,0.5f,-0.5f,   0.5f,0.5f,0.5f,     0.5f,0.5f,-0.5f);
    trojkaty[11].ustaw(-0.5f,0.5f,-0.5f,  -0.5f,0.5f,0.5f,     0.5f,0.5f,0.5f);
    

    float n = 0.1f;     
    float f = 100.0f;   
    
    float t = 0.0577f; 
    float b = -0.0577f; 
    
    float r = 0.1026f;  
    float l = -0.1026f; 
    Matrix4x4 perspective = PerspectiveMatrix(l, r, b, t, n, f);

    termios oldt;
    SetTerminalRawMode(oldt); // włącz tryb "na żywo"
   

    float delta = 0.10f;
    bool running = true;
    system("clear"); // czyścimy ekran raz na początek

    while (running) {
        std::cout << "\033[H"; // przesuwamy kursor na początek

        ekran.InicjalizujEkran();

        // Obsługa wejścia (non-blocking)
        char c = 0;
        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'w') kamera.MoveStraight(delta);
            else if (c == 's') kamera.MoveBack(delta);
            else if (c == 'a') kamera.LookLeft(delta);
            else if (c == 'd') kamera.LookRight(delta);
            else if (c == 'q') running = false;
        }

        
        Matrix4x4 viewMatrix = kamera.GetViewMatrix();
        for (int idx = 0; idx < 12; idx++) {
            Trojkat kopia = trojkaty[idx];
            Matrix4x4 tab[2] = { viewMatrix, perspective };
            TransformByMatrixes(kopia, tab, 2);
            ConnectTriangle(kopia, ekran);
        }

        ekran.Wypisz();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    std::cout << "\033[?25h"; // pokaż kursor
    RestoreTerminalMode(oldt); 
    std::cout << "Koniec programu." << std::endl;

    return 0;
}
