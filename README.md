# 🧱⏳ Sandtris: A Physics-Puzzle Engine

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML_3.0-8CC445?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Algorithm](https://img.shields.io/badge/Algorithm-BFS-blueviolet?style=for-the-badge)

**Sandtris** is a high-performance C++ game engine that reimagines the classic Tetris formula through the lens of real-time **Cellular Automata** physics. In this engine, blocks are not rigid shapes; they are composed of thousands of individual sand particles that react to gravity, slide down slopes, and stack into natural pyramids upon impact.

---

## 🌟 Technical Highlights

### 1. Real-Time Particle Physics
The heart of the engine is a custom **Cellular Automata** simulation. 
*   **Bottom-Up Traversal:** The grid is processed from the bottom row upward using 1D-array mathematical indexing to prevent "teleportation" bugs and simulate realistic gravity.
*   **Diagonal Sliding:** Every grain of sand checks its immediate neighbors to calculate diagonal sliding, allowing sand to pour into gaps and form realistic piles.

### 2. BFS Color-Blob Line Clearing
Unlike traditional Tetris, Sandtris uses a custom **Breadth-First Search (BFS)** algorithm to detect line clears.
*   **Monolithic Blobs:** The engine searches for contiguous clusters of the same color. 
*   **Clear Condition:** A blob is cleared only if a single contiguous mass of color manages to touch both the **Left and Right walls** of the play area simultaneously.
*   **Visual Polish:** Cleared particles enter a "dying" state (flashing white) using a delta-time timer before vanishing.

### 3. Advanced OOP Architecture & Memory
*   **Inheritance & Polymorphism:** Utilizes an abstract `GameObject` base class to standardized positioning and rendering across the `Grid` and `Tetromino` classes.
*   **Manual Memory Management:** To demonstrate mastery of memory allocation, the engine avoids standard containers in favor of **Raw Dynamic Pointers** (`new`/`delete`) and custom class destructors to ensure zero memory leaks.

### 4. Dynamic UI & Persistent Data
*   **Neon Arcade Interface:** Features a fully interactive UI built with SFML 3, including a Main Menu with difficulty selection, a Pause state, and a Game Over screen.
*   **Independent High Scores:** Utilizes C++ File I/O (`<fstream>`) to track and save **three separate high scores** (Easy, Medium, Hard) to a local `highscore.txt` file.
*   **Hardware-Accelerated Audio:** A multi-channel sound engine for menu music, rotation clicks, and line-clear chimes.

---

## 🎮 Controls

### Main Menu
*   **Mouse Click:** Select Difficulty (Easy: 2 Colors, Medium: 3 Colors, Hard: 4 Colors).

### Gameplay
*   **Left / Right Arrows:** Move the falling block.
*   **Space:** Rotate the block 90 degrees.
*   **Down Arrow (Hold):** Smooth Fast-Fall.
*   **ESC:** Pause the game.

### Pause / Game Over
*   **ESC (Paused):** Resume gameplay.
*   **Enter (Game Over):** Quick Restart on current difficulty.
*   **ESC (Game Over):** Return to Main Menu.

---

## 👥 The Development Team
This project was developed as a collaborative Object-Oriented Programming Final Project:

*   **Marryam Aqeel (Group Lead)**: UI Architecture & State Machine, BFS Clearing Logic Integration, Persistent File I/O (High Scores), and Audio Engine.
*   **Emaan Arif**: Physics Engine Development, 1D-Pointer Grid Management, and Particle logic.
*   **Mahlaka Yaseen**: Tetromino Matrix Logic, Shape Generation, and Matrix Rotation algorithms.
*   **M.Mohid Hassan**: Core Game Loop, GameObject Abstract Architecture, and Input Handling.

---

## 🚀 Build and Run

### Prerequisites
*   **SFML 3.0.2** Library.
*   C++17 compatible compiler (MinGW-w64 recommended for Windows).

### Compilation
Open your terminal in the project directory and run:

```bash
mingw32-make clean
mingw32-make