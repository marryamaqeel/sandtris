# ifndef GRID_H
# define GRID_H
# include "particle.h"
# include <SFML/Graphics.hpp>

class Grid{
private:
    int width;
    int height;
    Particle* cells;
public:
    Grid(int w, int h);
    ~Grid();

    void updatePhysics();
    int clearLines();
    void setParticle(int x, int y, int id, sf::Color color, sf::Color baseColor);
    Particle getParticle(int x, int y)const;
    void draw(sf::RenderWindow& window);

};

# endif