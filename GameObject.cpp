#include "GameObject.h"

GameObject::GameObject(int startX, int startY) : x(startX), y(startY) {}

GameObject::~GameObject() {}

int GameObject::getX() const { return x; }
int GameObject::getY() const { return y; }