# ifndef PARTICLE_HPP
# define PARTICLE_HPP
# include <SFML/Graphics.hpp>

struct Particle
{
    int id;
    sf::Color color;
    sf::Color baseColor;
    float timer;
};
# endif
