#ifndef GRID_H
#define GRID_H
#include "GameObject.h"
#include<iostream>
#include "Particle.hpp"
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

class grid : public GameObject
{
private:
    int width;
    int height;
    Particle* cell;
public:
    grid(int w, int h);
    ~grid();
    void updatePhysics();
    void setParticle(int x , int y , int id , sf::Color color,sf::Color baseColor);
    int getParticleID(int x, int y) const;
    int clearLines();
    void updateTimers(float dt);
    bool checkGameOver() const;
    void draw(sf::RenderWindow& window) override; // override the gameobject draw function this function will called
};

#endif