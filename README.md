# 🖥️ Terminal 3D Engine (C++)

A custom-built, software-based 3D graphics engine written entirely in C++ from scratch. This project renders 3D geometry (like a 3D cube) directly inside the Unix/Linux terminal using text characters. It features a custom mathematics library, a first-person camera system, and real-time user input without the use of any external graphical APIs (no OpenGL, Vulkan, or SDL).

## ✨ Features

* **Custom 3D Math Library:** Implements 4x4 matrices, 3D vectors (`Punkt`), and operations like cross-products, matrix multiplication, and translation/rotation matrices.
* **Perspective Projection:** Simulates true 3D depth using a custom perspective projection matrix and perspective divide (W-division).
* **First-Person Camera:** A fully functional camera that can move through the 3D space and look around by rotating the view matrix.
* **Near-Plane Clipping:** Implements line clipping against the camera's near-plane to prevent rendering bugs and crashes when objects move behind the camera.
* **Real-time Terminal Rendering:** Uses raw terminal mode (`termios`) and ANSI escape codes for non-blocking input and flicker-free 30 FPS console rendering.

## 🎮 Controls

The engine uses a non-blocking input loop. You can navigate the 3D space in real-time:

* **W** - Move Forward
* **S** - Move Backward
* **A** - Look Left (Rotate Camera)
* **D** - Look Right (Rotate Camera)
* **Q** - Quit Application

## 🛠️ Architecture & Code Structure

* `main.cpp` - The core application loop, terminal raw-mode configuration, and 3D cube definition (12 triangles).
* `Kamera.h / .cpp` - Handles the camera's position, look-at target, up-vector, and calculates the View Matrix.
* `Matrix4x4.h / .cpp` - The backbone of the 3D math, handling all transformations (Rotation, Translation, Perspective).
* `WorldToScreen.h / .cpp` - Handles the pipeline from 3D world space to 2D screen space, including clipping and mapping to console grid coordinates.
* `Ekran.h / .cpp` - Manages the 2D character buffer that represents the terminal screen.
* `rozmiary.h` - Global configuration for the terminal resolution (Width x Height).

## 🚀 How to Compile and Run

### Requirements
* A C++ compiler (e.g., `g++` or `clang++`).
* A Unix-like operating system (Linux, macOS) or WSL on Windows, as the project relies on `<termios.h>` and `<unistd.h>` for raw terminal input.

### Build Instructions

1. Clone the repository and navigate to the project directory.
2. Compile the source files using your preferred C++ compiler:
   ```bash
   g++ *.cpp -o terminal3d
