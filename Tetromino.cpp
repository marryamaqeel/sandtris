#include "Tetromino.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <algorithm>

sf::Color getRandomPastelColor() 
{
    sf::Color pastels[7] = {
        sf::Color(255, 0, 128),   // Hot Neon Pink
        sf::Color(0, 255, 255),   // Electric Cyan
        sf::Color(57, 255, 20),   // Toxic Lime Green
        sf::Color(255, 255, 0),   // Laser Yellow
        sf::Color(255, 80, 0),    // Vibrant Orange
        sf::Color(160, 32, 240),  // Deep Electric Purple
        sf::Color(255, 20, 20)      // Pastel Purple
    };
    return pastels[rand() % 4];
}


Tetromino::Tetromino() : GameObject(88,0)
{
    int randomType = rand() % 7;
    currentShape = new Shape(randomType);
    baseColor = getRandomPastelColor();
    fallTimer = 0;
}


void Tetromino::draw(sf::RenderWindow& window)
{
    int BLOCK_SCALE = 8;
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(4.0f * BLOCK_SCALE, 4.0f * BLOCK_SCALE));

    rectangle.setOutlineThickness(-1.0f); 
    rectangle.setOutlineColor(sf::Color(0, 0, 0, 150));
    for (int y = 0; y < currentShape->getSize(); y++)    
    {
        for (int x = 0; x < currentShape->getSize(); x++)
        {
            if (currentShape->getPixel(x,y) == 1)
            {
                float x_cood = ((x * BLOCK_SCALE) + getX()) * 4.0f;
                float y_cood = ((y * BLOCK_SCALE) + getY()) * 4.0f;
                rectangle.setFillColor(baseColor);
                rectangle.setPosition({x_cood,y_cood});

                window.draw(rectangle);
            }
        }

    }
}

void Tetromino::update(grid* playfield)
{
    int BLOCK_SCALE = 8;
    fallTimer++;
    if( fallTimer > 1)
    {
        fallTimer = 0;
        for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
        {
            for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
            {
                if (currentShape->getPixel(shapeX,shapeY) == 1)
                {
                    for (int i = 0; i < BLOCK_SCALE; i++) {
                        int checkX = getX() + (shapeX * BLOCK_SCALE) + i;
                        int checkY = getY() + (shapeY * BLOCK_SCALE) + BLOCK_SCALE; // +SCALE puts us exactly 1 pixel below the block

                        if (playfield->getParticleID(checkX, checkY) == 1 || playfield->getParticleID(checkX, checkY) == 2) {
                            shatter(playfield);
                            return;
                        }
                    }
                }
            }        
        }

        this->y++;      
    }
}

void Tetromino::shatter(grid* playfield)
{
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

    int BLOCK_SCALE = 8;

    for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
    {
        for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
        {
            if (currentShape->getPixel(shapeX,shapeY) == 1)
            {
                for(int i = 0; i < BLOCK_SCALE; i++) {
                    for(int j = 0; j < BLOCK_SCALE; j++) {
                        sf::Color color = varyColor(baseColor);
                        int finalX = getX() + (shapeX * BLOCK_SCALE) + i;
                        int finalY = getY() + (shapeY * BLOCK_SCALE) + j;
                        playfield->setParticle(finalX, finalY, 1 , color, baseColor);
                    }
                }
            }
        }
        
    }

    delete currentShape;
    currentShape = new Shape(rand() % 7);
    baseColor = getRandomPastelColor();
    this->x = 88;
    this->y = 0;
    
}

void Tetromino::handleInput(const sf::Event& event, grid* playfield)
{
    int BLOCK_SCALE = 8;
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        // --- LEFT ARROW ---
        if (keyPressed->code == sf::Keyboard::Key::Left) 
        {
            for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++) 
            {
                for (int ShapeX = 0; ShapeX < currentShape->getSize(); ShapeX++) 
                {
                    if (currentShape->getPixel(ShapeX,shapeY) == 1) 
                    {
                         for (int j = 0; j < BLOCK_SCALE; j++) {
                            int checkX = getX() + (ShapeX * BLOCK_SCALE) - BLOCK_SCALE; // Look 1 full block left
                            int checkY = getY() + (shapeY * BLOCK_SCALE) + j;
                            
                            // If anything is there (1=sand, 2=wall), we can't move!
                            if (playfield->getParticleID(checkX, checkY) != 0) return; 
                        }
                    }
                }
            }
            this->x -= BLOCK_SCALE; 
        }

        // --- RIGHT ARROW ---
        if (keyPressed->code == sf::Keyboard::Key::Right)
        {
            for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++) 
            {
                for (int ShapeX = 0; ShapeX < currentShape->getSize(); ShapeX++) 
                {
                    if (currentShape->getPixel(ShapeX,shapeY) == 1) 
                    {
                        for (int j = 0; j < BLOCK_SCALE; j++) {
                            int checkX = getX() + (ShapeX * BLOCK_SCALE) + BLOCK_SCALE; // Look 1 full block right
                            int checkY = getY() + (shapeY * BLOCK_SCALE) + j;
                            
                            if (playfield->getParticleID(checkX, checkY) != 0) return; 
                        }
                    }
                }
            }
           this->x += BLOCK_SCALE; 
        }

        // --- DOWN ARROW ---
        if (keyPressed->code == sf::Keyboard::Key::Down) 
        {
            fallTimer = 10; 
        }
    }
}
Tetromino::~Tetromino()
{
    delete currentShape;
}