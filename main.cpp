#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "grid.hpp"

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SandTris");
    window.setFramerateLimit(60);

    grid myGrid(200, 150);

    // Base sand color (important for consistency)
    sf::Color baseSand(210, 180, 140);

    // Color variation function (keeps sand natural but grouped)
    auto varyColor = [](sf::Color base)
    {
        int r = base.r + (rand() % 21 - 10);
        int g = base.g + (rand() % 21 - 10);
        int b = base.b + (rand() % 21 - 10);

        r = std::clamp(r, 0, 255);
        g = std::clamp(g, 0, 255);
        b = std::clamp(b, 0, 255);

        return sf::Color(r, g, b);
    };

    while (window.isOpen())
    {
        // ---------------- EVENTS ----------------
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }

        // ---------------- INPUT ----------------
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            int gridX = mousePos.x / 4;
            int gridY = mousePos.y / 4;

            // Create consistent but slightly varied sand color
            sf::Color sandColor = varyColor(baseSand);

            // 3x3 brush
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    myGrid.setParticle(gridX + i, gridY + j, 1, sandColor,baseSand);
                }
            }
        }

        // ---------------- UPDATE ----------------
        myGrid.updatePhysics();
        myGrid.clearLines();

        // ---------------- RENDER ----------------
        window.clear();

        myGrid.draw(window);

        window.display();
    }

    return 0;
}