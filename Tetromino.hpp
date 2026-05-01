#ifndef TETROMINO_H
#define TETROMINO_H
#include "GameObject.hpp"
#include "grid.hpp"
#include "Shape.hpp"
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Tetromino : public GameObject
{
private:
    Shape * currentShape;
    sf::Color color;
    sf:: Color baseColor;
    int fallTimer;
public:
    Tetromino(int difficulty);
    ~Tetromino();
    void update(grid* playfield,int difficulty);
    void shatter(grid* playfield,int difficulty);
    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event,grid* playfield);
};

#endif