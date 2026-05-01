#include "Tetromino.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <algorithm>


sf::Color getShapeColor()
{
    sf::Color colors[5] =
    {
        sf::Color(0,   255, 255),  // cyan
        sf::Color(255, 255, 0  ),  // yellow
        sf::Color(160, 32,  240),  // purple
        sf::Color(57,  255, 20 ),  // green
        sf::Color(255, 20,  20 ),  // red
    };
    return colors[rand() % 5];
}


Tetromino::Tetromino() : GameObject(60, 0),
                         currentShape(nullptr),
                         baseColor(sf::Color(255, 255, 255)),
                         fallTimer(0.0f)
{
    int randomType = rand() % 7;
    currentShape   = new Shape(randomType);
    baseColor      = getShapeColor();
}



Tetromino::~Tetromino()
{
    delete currentShape;
}



void Tetromino::handleInput(const sf::Event& event, Grid* playfield)
{
    int BLOCK_SCALE = 8;

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        // --- LEFT ---
        if (keyPressed->code == sf::Keyboard::Key::Left)
        {
            for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
            {
                for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
                {
                    if (currentShape->getPixel(shapeX, shapeY) == 1)
                    {
                        for (int i = 0; i < BLOCK_SCALE; i++)
                        {
                            for (int j = 0; j < BLOCK_SCALE; j++)
                            {
                                int checkX = getX() + (shapeX * BLOCK_SCALE) - BLOCK_SCALE + i;
                                int checkY = getY() + (shapeY * BLOCK_SCALE) + j;

                                if (playfield->getParticleID(checkX, checkY) != 0)
                                    return;
                            }
                        }
                    }
                }
            }
            this->x -= BLOCK_SCALE;
        }

        // --- RIGHT ---
        if (keyPressed->code == sf::Keyboard::Key::Right)
        {
            for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
            {
                for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
                {
                    if (currentShape->getPixel(shapeX, shapeY) == 1)
                    {
                        for (int i = 0; i < BLOCK_SCALE; i++)
                        {
                            for (int j = 0; j < BLOCK_SCALE; j++)
                            {
                                int checkX = getX() + (shapeX * BLOCK_SCALE) + BLOCK_SCALE + i;
                                int checkY = getY() + (shapeY * BLOCK_SCALE) + j;

                                if (playfield->getParticleID(checkX, checkY) != 0)
                                    return;
                            }
                        }
                    }
                }
            }
            this->x += BLOCK_SCALE;
        }

        // --- DOWN ---
        if (keyPressed->code == sf::Keyboard::Key::Down)
        {
            fallTimer = 40.0f;  // force fast drop
        }

        // --- SPACE (rotate) ---
        if (keyPressed->code == sf::Keyboard::Key::Space)
        {
            currentShape->rotateRight();

            bool blocked = false;

            for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
            {
                for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
                {
                    if (currentShape->getPixel(shapeX, shapeY) == 1)
                    {
                        for (int i = 0; i < BLOCK_SCALE; i++)
                        {
                            for (int j = 0; j < BLOCK_SCALE; j++)
                            {
                                int checkX = getX() + (shapeX * BLOCK_SCALE) + i;
                                int checkY = getY() + (shapeY * BLOCK_SCALE) + j;

                                if (playfield->getParticleID(checkX, checkY) != 0)
                                    blocked = true;
                            }
                        }
                    }
                }
            }

            // undo rotation if blocked
            if (blocked)
                currentShape->rotateLeft();
        }
    }
}


void Tetromino::update(Grid* playfield)
{
    int BLOCK_SCALE = 8;

    fallTimer++;

    if (fallTimer > 30)
    {
        fallTimer = 0;

        for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
        {
            for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
            {
                if (currentShape->getPixel(shapeX, shapeY) == 1)
                {
                    for (int i = 0; i < BLOCK_SCALE; i++)
                    {
                        int checkX = getX() + (shapeX * BLOCK_SCALE) + i;
                        int checkY = getY() + (shapeY * BLOCK_SCALE) + BLOCK_SCALE;

                        if (playfield->getParticleID(checkX, checkY) == 1 ||
                            playfield->getParticleID(checkX, checkY) == 2)
                        {
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



void Tetromino::shatter(Grid* playfield)
{
    int BLOCK_SCALE = 8;

    // small color variation per particle for sand effect
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
            if (currentShape->getPixel(shapeX, shapeY) == 1)
            {
                for (int i = 0; i < BLOCK_SCALE; i++)
                {
                    for (int j = 0; j < BLOCK_SCALE; j++)
                    {
                        sf::Color variedColor = varyColor(baseColor);
                        int finalX = getX() + (shapeX * BLOCK_SCALE) + i;
                        int finalY = getY() + (shapeY * BLOCK_SCALE) + j;

                        playfield->setParticle(finalX, finalY, 1, variedColor, baseColor);
                    }
                }
            }
        }
    }

    // spawn new shape
    delete currentShape;

    currentShape = new Shape(rand() % 7);
    baseColor    = getShapeColor();
    this->x      = 60;
    this->y      = 0;
}

/

void Tetromino::draw(sf::RenderWindow& window)
{
    int BLOCK_SCALE = 8;

    sf::RectangleShape block;
    block.setSize(sf::Vector2f(4.0f * BLOCK_SCALE, 4.0f * BLOCK_SCALE));
    block.setOutlineThickness(-1.0f);
    block.setOutlineColor(sf::Color(0, 0, 0, 150));

    for (int shapeY = 0; shapeY < currentShape->getSize(); shapeY++)
    {
        for (int shapeX = 0; shapeX < currentShape->getSize(); shapeX++)
        {
            if (currentShape->getPixel(shapeX, shapeY) == 1)
            {
                float xCoord = 100 + (getX() + shapeX * BLOCK_SCALE) * 4.0f;
                float yCoord = 50  + (getY() + shapeY * BLOCK_SCALE) * 4.0f;

                block.setFillColor(baseColor);
                block.setPosition({xCoord, yCoord});

                window.draw(block);
            }
        }
    }
}