# 🧱⏳ Sandtris

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-8CC445?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OOP](https://img.shields.io/badge/Architecture-OOP-blueviolet?style=for-the-badge)

**Sandtris** is an innovative hybrid puzzle game built entirely from scratch in C++. It combines the classic rigid-block mechanics of Tetris with a dynamic, falling-sand physics engine driven by cellular automata. 

When blocks hit the ground, they lose their rigid structure and shatter into individual grains of sand, stacking naturally into pyramids and settling into gaps.

> **Note:** [Insert a link to a GIF or screenshot of your gameplay here later!]

---

## ✨ Features & Functionalities

*   **Custom Physics Simulation:** Implements a bottom-up cellular automata algorithm to calculate the gravity, sliding (down-left/down-right), and stacking of thousands of individual sand particles at 60 FPS.
*   **Tetromino Mechanics:** Full implementation of classic puzzle mechanics, including matrix rotation, movement, and gravity.
*   **Dynamic State Conversion:** Seamless algorithm that transfers rigid block coordinates into independent physics particles upon collision.
*   **Manual Memory Management:** The game grid avoids standard library vectors in favor of **raw dynamic pointers** (`new` and `delete`). It utilizes mathematical indexing to map a 1D array into a 2D coordinate space for maximum memory access speed.
*   **Line Clearing & Scoring:** Evaluates uneven sand piles to clear fully occupied horizontal rows and updates the game state.

---

## 🏗️ Project Architecture (OOP)

This project strictly follows Object-Oriented Programming principles. Every component is encapsulated within its own Header (`.h`) and Source (`.cpp`) files.

| Class / File | Description |
| :--- | :--- |
| `main.cpp` | The entry point of the program. |
| `Constants.h` | Global configuration for screen size, cell size, and grid dimensions. |
| `Game` | The core engine. Manages the SFML window, delta-time, event polling, and the main loop. |
| `Grid` | The physics engine. Manages the dynamic 1D pointer array of sand particles and collision checks. |
| `Tetromino` | The player-controlled rigid shapes. Handles user input, matrix rotation, and shattering logic. |

---

## 🎮 Controls

*   **Left / Right Arrows:** Move the falling block left or right.
*   **Up Arrow:** Rotate the block 90 degrees.
*   **Down Arrow:** Accelerate the block's fall speed.
*   **ESC:** Close the game.

---

## 🚀 How to Build and Run

### Prerequisites
*   A C++ compiler (MSVC, GCC, or Clang).
*   Visual Studio 2022 (Recommended for Windows).
*   **SFML 2.6+** (Simple and Fast Multimedia Library).

### Installation Steps
1. Clone this repository:
   ```bash
   git clone https://github.com/YourUsername/Sandtris.git