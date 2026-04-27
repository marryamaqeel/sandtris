#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Tetromino.h"
#include "UIManager.h"

class Game {
private:
    sf::RenderWindow window;
    Grid* playfield;
    Tetromino* activeBlock;
    UIManager* ui;
    bool isRunning;

public:
    Game();
    ~Game();

    void run();
    void processEvents();
    void update();
    void render();
};