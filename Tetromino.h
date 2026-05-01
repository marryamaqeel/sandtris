#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Shape.h"
#include "Grid.h"

class Tetromino : public GameObject
{
public:
    Tetromino();
    ~Tetromino();

    void handleInput(const sf::Event& event, Grid* playfield);
    void update(Grid* playfield);
    void shatter(Grid* playfield);
    void draw(sf::RenderWindow& window);

private:
    Shape*    currentShape;
    sf::Color baseColor;
    float     fallTimer;
};