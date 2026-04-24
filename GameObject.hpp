#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

class GameObject
{
private:
    int x;
    int y;
public:
    GameObject(int startX, int startY);
    void draw(sf::RenderWindow& window);
    int getX() const;
    int getY() const;
    ~GameObject();
};

#endif