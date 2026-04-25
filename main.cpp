#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()
#include <algorithm> // For std::min and std::max
#include "grid.hpp"

int main()
{
    // Seed the random number generator for our color variation
    srand(time(NULL));

    // Create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SandTris");
    window.setFramerateLimit(60); // CRUCIAL: Keeps physics running at normal speed!

    // Create your Grid! 
    // Screen is 800x600. If sand is 4x4 pixels, grid is 200 wide by 150 tall.
    grid myGrid(200, 150);

    while (window.isOpen())
    {
        // --- 1. EVENT POLLING (SFML 3 Syntax) ---
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

        // --- 2. INPUT & GAME LOGIC ---
        
        // If Left Mouse Button is held down...
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
        {
            // Get mouse position
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            // Convert screen pixels (800x600) to grid cells (200x150)
            int gridX = mousePos.x / 4; 
            int gridY = mousePos.y / 4;
            
            // --- COLOR VARIATION MATH ---
            int baseR = 210, baseG = 180, baseB = 140; // Sand color
            int offset = (rand() % 51) - 25; // Random number between -25 and +25
            
            // Apply offset and keep between 0-255
            int r = std::min(255, std::max(0, baseR + offset));
            int g = std::min(255, std::max(0, baseG + offset));
            int b = std::min(255, std::max(0, baseB + offset));

            sf::Color randomSandColor(r, g, b);

            // Spawn the sand!
            // (We spawn a 3x3 brush so it's easier to draw thick lines)
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    myGrid.setParticle(gridX + i, gridY + j, 1, randomSandColor);
                }
            }
        }

        // Update your sand physics and clear full lines!
        myGrid.updatePhysics();
        myGrid.clearLines();

        // --- 3. RENDERING ---
        window.clear();
        
        // Draw your grid
        myGrid.draw(window);
        
        window.display();
    }

    return 0;
}