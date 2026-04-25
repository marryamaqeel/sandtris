#include "grid.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Particle.hpp"

grid::grid(int w, int h) : GameObject(0,0)
{
    width = w;
    height = h;
    cell = new Particle[width * height];
    for (int i = 0; i < width*height; i++)
    {
        cell[i].id = 0;
    }
    

}

void grid::setParticle(int x , int y , int id , sf::Color color)
{
    if ((x>= 0 && x < width) && (y>=0 && y < height))
    {
        int index = (y * width) + x;
        cell[index].color = color;
        cell[index].id = id;
    }
    else
    {
        return;
    }
}

int grid::getParticleID(int x, int y)const
{
    if( x>=0 && x <width && y>= 0 && y < height)
    {
        int index = (y * width) + x;
        return cell[index].id;
    }
    else
    {
        return 2;
    }
}
grid::~grid()
{
    delete[] cell;
}

void  grid:: draw(sf::RenderWindow& window)
{
    sf::RectangleShape rectangle;
    float cellsize = 4.0f;
    rectangle.setSize(sf::Vector2f{cellsize, cellsize}); // making sand 4x4 

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width) + x;
            if (cell[index].id == 1)
            {
                rectangle.setFillColor(cell[index].color);
                float x_cood = (x*cellsize) + getX();
                float y_cood = (y*cellsize) + getY();
                rectangle.setPosition({x_cood, y_cood});
                window.draw(rectangle);
            }
        }
        
    }
}

void grid::updatePhysics() // falling sand simulator cellular automata
{
    for (int y = height - 2; y >= 0 ; y--) // h - 2 bcz h - 1 is already floor cant go any further
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y*width) + x;
            if (cell[index].id == 1)
            {
                // use random rand() % 2 to decide left or right
                if (getParticleID(x,y+1) == 0) // down (gravity)
                {
                    setParticle(x,y+1,cell[index].id , cell[index].color);
                    cell[index].id = 0;
                }
                else if(getParticleID(x - 1, y + 1) == 0) // slide left (if space)
                {
                    setParticle(x-1,y+1,cell[index].id , cell[index].color);
                    cell[index].id = 0;
                }
                else if (getParticleID(x + 1, y + 1) == 0) // right slide (if space)
                {
                    setParticle(x+1,y+1,cell[index].id , cell[index].color);
                    cell[index].id = 0;
                }

            }
        }
        
    }
    
}

int grid::clearLines()
{
    int lineclear = 0;
    for (int y = 0; y < height; y++)
    {
        if (getParticleID(0,y) == 0)
        {
            continue;
        }
        sf::Color targetcolor = cell[(y*width) + 0].color;
        bool isfull = true;

        for (int x = 0; x < width; x++)
        {
            int index = (y*width) + x;
            if (cell[index].id == 0 || cell[index].color != targetcolor)
            {
                isfull =false;
                break;
            }
        }
        
        if (isfull == true)
        {
            for (int x = 0; x < width; x++)
            {
                int index = (y*width) + x;
                cell[index].id = 0;
            }
            lineclear++;
            
        }


    }
    return lineclear;
}

