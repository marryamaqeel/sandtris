#include "Tetromino.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <algorithm>

sf::Color getRandomPastelColor(int limit) 
{
    sf::Color pastels[4] = {
        sf::Color(0, 255, 255),   // Cyan
        sf::Color(255, 255, 0),   // Yellow
        sf::Color(255, 0, 128),   // Pink
        sf::Color(57, 255, 20)  // green
    };
    return pastels[rand() % limit];
}


Tetromino::Tetromino(int difficulty) : GameObject(64,0)
{
    int randomType = rand() % 7;
    currentShape = new Shape(randomType);
    baseColor = getRandomPastelColor(difficulty);
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
                float x_cood = 100 + (getX() + x * BLOCK_SCALE) * 4.0f;
                float y_cood = 50  + (getY() + y * BLOCK_SCALE) * 4.0f;
                rectangle.setFillColor(baseColor);
                rectangle.setPosition({x_cood,y_cood});

                window.draw(rectangle);
            }
        }

    }
}

void Tetromino::update(grid* playfield,int difficulty,UIManager* ui)
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
                            shatter(playfield,difficulty,ui);
                            return;
                        }
                    }
                }
            }        
        }

        this->y++;      
    }
}

void Tetromino::shatter(grid* playfield,int difficulty,UIManager* ui)
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

    ui->playSandSound();
    delete currentShape;
    currentShape = new Shape(rand() % 7);
    baseColor = getRandomPastelColor(difficulty);
    this->x = 60;
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
                        // FIX: Added 'i' loop to check the entire 8x8 destination block
                        for (int i = 0; i < BLOCK_SCALE; i++) {
                            for (int j = 0; j < BLOCK_SCALE; j++) {
                                int checkX = getX() + (ShapeX * BLOCK_SCALE) - BLOCK_SCALE + i; 
                                int checkY = getY() + (shapeY * BLOCK_SCALE) + j;
                                
                                if (playfield->getParticleID(checkX, checkY) != 0) return; 
                            }
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
                        // FIX: Added 'i' loop to check the entire 8x8 destination block
                        for (int i = 0; i < BLOCK_SCALE; i++) {
                            for (int j = 0; j < BLOCK_SCALE; j++) {
                                int checkX = getX() + (ShapeX * BLOCK_SCALE) + BLOCK_SCALE + i; 
                                int checkY = getY() + (shapeY * BLOCK_SCALE) + j;
                                
                                if (playfield->getParticleID(checkX, checkY) != 0) return; 
                            }
                        }
                    }
                }
            }
           this->x += BLOCK_SCALE; 
        }
        // --- DOWN ARROW ---
        if (keyPressed->code == sf::Keyboard::Key::Down) 
        {
            fallTimer = 40; 
        }

        if (keyPressed->code == sf::Keyboard::Key::Space) 
        {
            // 1. Spin it!
            currentShape->rotateRight();

            // 2. Check if we just spun into a wall or sand
            bool blocked = false;
            for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++) 
            {
                for (int ShapeX = 0; ShapeX < currentShape->getSize(); ShapeX++) 
                {
                    if (currentShape->getPixel(ShapeX, shapeY) == 1) 
                    {
                        // Check the whole block size
                        for (int i = 0; i < BLOCK_SCALE; i++) {
                            for (int j = 0; j < BLOCK_SCALE; j++) {
                                int checkX = getX() + (ShapeX * BLOCK_SCALE) + i;
                                int checkY = getY() + (shapeY * BLOCK_SCALE) + j;
                                
                                if (playfield->getParticleID(checkX, checkY) != 0) {
                                    blocked = true;
                                }
                            }
                        }
                    }
                }
            }

            // 3. If we hit a wall while spinning, undo the spin!
            if (blocked) {
                currentShape->rotateLeft();
            }
        }
    }
}
Tetromino::~Tetromino()
{
    delete currentShape;
}