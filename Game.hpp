#pragma once
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "Tetromino.hpp"
#include "UIManager.hpp"

enum class GameState {
    MainMenu,
    Playing,
    GameOver
};
class Game {
private:
    sf::RenderWindow window;
    grid* playfield;
    Tetromino* activeBlock;
    UIManager* ui;
    bool isRunning;
    GameState currentState;
    

public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
};
