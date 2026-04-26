#include "Tetromino.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <algorithm>



Tetromino::Tetromino() : GameObject(100,0)
{
    int randomType = rand() % 7;
    currentShape = new Shape(randomType);
    baseColor = sf:: Color(0,255,255);
    fallTimer = 0;
}

void Tetromino::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(4.0f,4.0f)); // 4x4 pixel
    for (int y = 0; y < currentShape->getSize(); y++)    
    {
        for (int x = 0; x < currentShape->getSize(); x++)
        {
            if (currentShape->getPixel(x,y) == 1)
            {
                float x_cood = (x + getX()) * 4.0f;
                float y_cood = (y + getY()) * 4.0f;
                rectangle.setFillColor(baseColor);
                rectangle.setPosition({x_cood,y_cood});

                window.draw(rectangle);
            }
        }

    }
}

void Tetromino::update(grid* playfield)
{
    fallTimer++;
    if( fallTimer > 30)
    {
        fallTimer = 0;
        for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
        {
            for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
            {
                if (currentShape->getPixel(shapeX,shapeY) == 1)
                {
                    if (playfield->getParticleID(getX() + shapeX, getY() + shapeY + 1) == 1 || playfield->getParticleID(getX() + shapeX, getY() + shapeY + 1) == 2)
                    {
                        shatter(playfield);
                        return;
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

    for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
    {
        for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
        {
            if (currentShape->getPixel(shapeX,shapeY) == 1)
            {
                color = varyColor(baseColor);
                playfield->setParticle(getX() + shapeX, getY() + shapeY, 1 , color, baseColor);
            }
        }
        
    }

    delete currentShape;
    currentShape = new Shape(rand() % 7);
    this->x = 100;
    this->y = 0;
    
}

void Tetromino::handleInput(const sf::Event& event, grid* playfield)
{
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
                        if (playfield->getParticleID(getX() + ShapeX - 1, getY() + shapeY) == 1 || playfield->getParticleID(getX() + ShapeX - 1, getY() + shapeY) == 2)
                        {
                            return; 
                        }
                    }
                }
            }
            this->x--; 
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
                        if (playfield->getParticleID(getX() + ShapeX + 1, getY() + shapeY) == 1 ||  playfield->getParticleID(getX() + ShapeX + 1, getY() + shapeY) == 2)
                        {
                            return; 
                        }
                    }
                }
            }
            this->x++; 
        }

        // --- DOWN ARROW ---
        if (keyPressed->code == sf::Keyboard::Key::Down) 
        {
            fallTimer = 30; 
        }
    }
}
Tetromino::~Tetromino()
{
    delete currentShape;
}