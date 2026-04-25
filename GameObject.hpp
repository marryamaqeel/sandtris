#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameObject
{
protected:
    int x;
    int y;
public:
    GameObject(int startX, int startY);
    virtual void draw(sf::RenderWindow& window) = 0;// abstract class
    int getX() const;
    int getY() const;
    virtual ~GameObject(); // prevents memory leak
};

#endif