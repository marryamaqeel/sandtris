#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include "grid.hpp"
#include "Tetromino.hpp"

int main()
{
    srand(time(NULL));

    // 1. Create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SandTris - Solo Project!");
    window.setFramerateLimit(60); 

    // 2. Create the Grid (Grid is 200x150 cells)
    grid myGrid(200, 150);

    // 3. Create the Falling Block!
    Tetromino activeBlock;

    while (window.isOpen())
    {
        // --- EVENT POLLING ---
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) window.close();
            }

            // PASS INPUT TO THE BLOCK!
            if (event.has_value()) {
                activeBlock.handleInput(event.value(), &myGrid);
            }
        }

        // --- GAME LOGIC ---
        // 1. Block falls and checks for crashes
        activeBlock.update(&myGrid); 
        
        // 2. Sand falls
        myGrid.updatePhysics();      
        
        // 3. Clear full lines
        myGrid.clearLines();         

        // --- RENDERING ---
        window.clear();
        
        myGrid.draw(window);         // Draw sand
        activeBlock.draw(window);    // Draw falling block
        
        window.display();
    }

    return 0;
}