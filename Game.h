#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"
#include "Tetromino.h"
#include "UIManager.h"

enum class GameState {
    MainMenu,
    Playing,
    GameOver,
    Paused
};
class Game {
private:
    sf::RenderWindow window;
    Grid* playfield;
    Tetromino* activeBlock;
    UIManager* ui;
    bool isRunning;
     GameState currentState;
    int currentDifficulty;

public:
    Game();
    ~Game();

    void run();
    void processEvents();
    void update();
    void render();
};