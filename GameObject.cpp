#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

GameObject::GameObject(int startX, int startY)
{
    x = startX;
    y = startY;
}

int GameObject::getX() const
{
    return x;
}

int GameObject::getY() const
{
    return y;
}

GameObject::~GameObject() {}

