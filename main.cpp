#include <SFML/Graphics.hpp>
#include "grid.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    const int GRID_WIDTH = 100;
    const int GRID_HEIGHT = 100;
    const int CELL_SIZE = 8;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "Sandtrix Test");
    window.setFramerateLimit(60);

    Grid gameGrid(GRID_WIDTH, GRID_HEIGHT);

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mPos = sf::Mouse::getPosition(window);
            int gx = mPos.x / CELL_SIZE;
            int gy = mPos.y / CELL_SIZE;

            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    gameGrid.setParticle(gx + dx, gy + dy, 1, sf::Color::Yellow, sf::Color::Yellow);
                }
            }
        }

        gameGrid.updatePhysics();
        gameGrid.clearLines();

        window.clear(sf::Color(20, 20, 20));
        gameGrid.draw(window);
        window.display();
    }

    return 0;
}