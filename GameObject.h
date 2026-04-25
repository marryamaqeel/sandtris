#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    int x, y;

public:
    GameObject(int startX, int startY);
    virtual ~GameObject();

    virtual void draw(sf::RenderWindow& window) = 0;

    int getX() const;
    int getY() const;
};