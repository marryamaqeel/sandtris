# 🧱⏳ Sandtris

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML_3-8CC445?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Algorithm](https://img.shields.io/badge/Algorithm-BFS-blueviolet?style=for-the-badge)

**Sandtris** is a highly polished, custom-built game engine written purely in C++. It merges the rigid-body matrix mechanics of classic Tetris with a real-time, bottom-up cellular automata physics simulation. 

When Tetrominoes crash, they shatter into individual grains of sand that cascade, slide, and stack into natural pyramids using dynamic particle physics.

---

## ✨ Core Features & Technical Highlights

*   **Cellular Automata Physics Engine:** Processes thousands of individual sand particles simultaneously at 60 FPS using a bottom-up 1D-array traversal algorithm.
*   **Breadth-First Search (BFS) Line Clearing:** Utilizes a custom Flood-Fill BFS algorithm via `std::queue` to detect monolithic color blobs. Sand only clears if touching contiguous particles of the exact same color span from the left wall to the right wall.
*   **Custom Memory Management:** Avoids standard `<vector>` overhead by using raw dynamic pointers (`new`/`delete`) and custom destructors to prevent memory leaks during rapid state changes.
*   **Interactive State Machine:** A fully functional UI architecture featuring a Main Menu, Pause functionality, and Game Over states.
*   **Dynamic Difficulty Scaling:** Three distinct difficulties (Easy, Medium, Hard) that dynamically alter the RGB generation constraints, actively changing the complexity of the BFS color-matching requirement.
*   **Persistent Data:** Utilizes C++ `<fstream>` to read/write specific High Scores for all three difficulty levels to a local text file.
*   **Modern SFML 3 Architecture:** Built using the newest SFML 3 release, utilizing modern `std::optional` event polling and updated rendering pipelines.

---

## 🎮 Controls

### Main Menu
*   **Left Click:** Select Difficulty (Easy = 2 Colors, Medium = 3 Colors, Hard = 4 Colors)

### Gameplay
*   **Left / Right Arrows:** Move the falling block.
*   **Up Arrow:** Rotate the block 90 degrees.
*   **Down Arrow:** Accelerate gravity (Fast Fall).
*   **ESC:** Pause the game.

---

## 🚀 How to Build and Run

### Prerequisites
*   A C++17 compatible compiler (MinGW-w64 recommended for Windows).
*   **SFML 3.x** Library.

### Compilation
A standard `Makefile` is included. To compile the engine, open your terminal in the project directory and run:

```bash
mingw32-make clean
mingw32-make

```run
./Sandtris.exe