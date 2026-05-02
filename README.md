# 🧱⏳ Sandtris: A Physics-Puzzle Engine

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML_3.0-8CC445?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Algorithm](https://img.shields.io/badge/Algorithm-BFS-blueviolet?style=for-the-badge)

**Sandtris** is a high-performance, Object-Oriented game engine built in C++. It reinvents the classic Tetris formula by introducing real-time **Cellular Automata** physics. In this game, Tetrominoes are not just rigid blocks; they are composed of thousands of individual sand particles that shatter, cascade, and settle into gaps upon impact.

---

## 🚀 Technical Highlights

### 1. Real-Time Particle Simulation
The engine utilizes a custom-built physics simulation based on **Cellular Automata**. 
*   **Bottom-Up Traversal:** Updates the grid from the bottom row upward to prevent "teleportation" bugs and simulate realistic gravity.
*   **Diagonal Sliding:** Sand particles check their down-left and down-right neighbors, allowing them to form natural pyramids and slide down slopes.

### 2. BFS Flood-Fill Line Clearing
Unlike traditional Tetris, Sandtris uses a **Breadth-First Search (BFS)** algorithm to detect line clears.
*   **Monolithic Blobs:** The engine searches for contiguous clusters of the same color. 
*   **Clear Condition:** A blob is cleared only if it manages to touch both the **Left and Right walls** of the play area simultaneously.
*   **Visual Feedback:** Particles enter a "dying" state, turning white before vanishing to provide satisfying player feedback.

### 3. Advanced OOP & Memory Management
*   **Abstract Architecture:** Uses a `GameObject` base class with virtual rendering methods to manage the physics `Grid` and the player-controlled `Tetromino`.
*   **Manual Memory Control:** To demonstrate low-level proficiency, the project avoids standard containers in favor of **Raw Dynamic Pointers** (`new`/`delete`) and custom class destructors to ensure zero memory leaks.

### 4. Audio & Persistent Data
*   **Dynamic Sound Engine:** Hardware-accelerated audio using SFML 3's new audio pipeline for shattering sounds and line-clear chimes.
*   **Persistent High Scores:** Implements C++ File I/O (`<fstream>`) to track **three independent high scores** (Easy, Medium, Hard) saved in a local `highscores.txt` file.

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
*   **Enter (Game Over):** Quick Restart.
*   **ESC (Game Over):** Return to Main Menu.
*   **M (Paused):** Return to Main Menu.

---

## 🛠️ Build and Run

### Prerequisites
*   **SFML 3.x** Library.
*   C++17 compatible compiler (MinGW-w64 recommended for Windows).

### Compilation
Open your terminal in the project directory and run:

```bash
mingw32-make clean
mingw32-make