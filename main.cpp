#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    // FIX 1: Curly braces around the dimensions
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Window");

    while (window.isOpen())
    {
        // FIX 2: pollEvent now takes no arguments and returns an optional event
        while (const std::optional event = window.pollEvent())
        {
            // FIX 3: Check event types using the new is<T>() syntax
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // FIX 4: How to check for key presses in SFML 3
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();
        // window.draw(...);
        window.display();
    }

    return 0;
}