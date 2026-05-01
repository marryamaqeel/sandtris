# 🧱⏳ Sandtris

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML_3-8CC445?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Algorithm](https://img.shields.io/badge/Algorithm-BFS-blueviolet?style=for-the-badge)

**Sandtris** is a high-performance C++ game engine that reimagines the classic Tetris formula through the lens of cellular automata physics. Unlike standard puzzle games, every block in Sandtris is composed of individual sand particles that react to gravity, slide down slopes, and stack into natural pyramids in real-time.

---

## 🌟 Technical Overview & Features

### 1. Cellular Automata Physics
The heart of the game is a bottom-up physics engine. Every grain of sand calculates its movement based on its immediate neighbors, allowing for realistic sliding, stacking, and crumbling.
*   **Optimization:** Uses a 1D pointer-based array to maximize CPU cache hits and ensure smooth 60 FPS performance even with thousands of active particles.

### 2. BFS Color-Matching Algorithm
Instead of simple row clearing, this project implements a **Breadth-First Search (BFS)** algorithm to detect contiguous blobs of color. 
*   **Logic:** When a block shatters, the engine uses a queue-based Flood Fill to identify if a single-color mass touches both the left and right walls of the play area simultaneously.
*   **Visual Polish:** Cleared particles enter a "dying" state (turning white) before vanishing, providing satisfying visual feedback.

### 3. Advanced OOP Architecture
*   **Inheritance & Polymorphism:** Utilizes an abstract `GameObject` base class to standardize rendering and positioning for both the physics `Grid` and the falling `Tetromino`.
*   **Manual Memory Management:** To demonstrate mastery of C++ memory, the project avoids standard vectors in favor of raw dynamic pointers (`new`/`delete`) with strict destructor management to prevent memory leaks.

### 4. Difficulty & Independent High Scores
The game features a custom neon-themed UI with dynamic difficulty scaling. The game tracks **3 separate High Scores**, automatically saving and loading them via C++ File I/O (`<fstream>`) to a local `highscores.txt` file based on the selected mode:
*   🟢 **Easy (Default):** 2 Colors (Cyan & Yellow). High probability of BFS clearing. *Tracks Easy High Score.*
*   🟡 **Medium:** 3 Colors. *Tracks Medium High Score.*
*   🔴 **Hard:** 4 Colors. Requires strategic placement and faster reactions. *Tracks Hard High Score.*

---

## 🎮 Controls

### Main Menu
*   **Left Click:** Select Difficulty Buttons (Easy, Medium, or Hard).
*   **Num Keys 1, 2, 3:** Keyboard shortcuts for difficulty selection.

### Gameplay
*   **Left / Right Arrows:** Move the block.
*   **Up Arrow:** Rotate the block 90 degrees.
*   **Down Arrow (Hold):** Accelerate gravity (Fast Fall).
*   **ESC:** Pause the game.

### Game Over / Pause
*   **Enter (Game Over):** Restart on current difficulty.
*   **ESC (Game Over):** Return to Main Menu.
*   **ESC (Playing):** Toggle Pause.

---

## 🚀 Installation and Build

### Prerequisites
*   **SFML 3.x** (Latest Release).
*   A C++17 compatible compiler (e.g., MinGW-w64).

### Build Instructions
This project includes a `Makefile` for easy compilation. Open your terminal in the project directory and run:

```bash
# Clean previous builds
mingw32-make clean

# Compile the engine
mingw32-make