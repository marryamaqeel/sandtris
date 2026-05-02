#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Shape.h"
#include "grid.hpp"
#include "UIManager.h"

class Tetromino : public GameObject
{
private:
    Shape*    currentShape;
    sf::Color baseColor;
    sf::Color color;
    int     fallTimer;
public:
    Tetromino(int difficulty);
    ~Tetromino();

    void handleInput(const sf::Event& event, grid* playfield);
    void update(grid* playfield, int difficulty, UIManager* ui);
    void shatter(grid* playfield , int difficulty, UIManager* ui);
    void draw(sf::RenderWindow& window) override;

};