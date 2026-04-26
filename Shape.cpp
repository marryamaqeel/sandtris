#include "Shape.hpp"
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Shape::Shape(int type)
{
    Matrix = new int[size * size];
    for (int i = 0; i < size * size; i++)
    {
        Matrix[i] = 0;
    }
    
    switch (type)
    {
    case 0:
    {
        // square
        for (int i = 0; i < size * size; i++)
        {
            Matrix[i] = 1;
        }
        break;
        
    }
    case 1:
    {
        // horizontal line 
        for (int i = 3; i < 6; i++)
        {
            Matrix[i] = 1;
        }
        break;
        
    }
    case 2:
    {
        // T
        Matrix[1] = 1;
        Matrix[3] = 1;
        Matrix[4] = 1;
        Matrix[5] = 1;
        break;
    }

    case 3:
    {
        // L
        Matrix[2] = 1;
        Matrix[3] = 1;
        Matrix[4] = 1;
        Matrix[5] = 1;
        break;
    }

    case 4:
    {
        Matrix[0] = 1;
        Matrix[3] = 1;
        Matrix[4] = 1;
        Matrix[5] = 1;
        break;
    }

    case 5:
    {
        Matrix[1] = 1;
        Matrix[2] = 1;
        Matrix[3] = 1;
        Matrix[4] = 1;
        break;
    }

    case 6:
    {
        Matrix[0] = 1;
        Matrix[1] = 1;
        Matrix[4] = 1;
        Matrix[5] = 1;
        break;
    }
    
    default:
        break;
    }

}

Shape::~Shape()
{
    delete[] Matrix;
}

int Shape::getPixel(int x, int y) const
{
    if ((x >= 0 && x < size && y >= 0 && y < size))
    {
        int index = (y * size) + x;
        return Matrix[index];
    }

    return 0;

}

int Shape::getSize() const
{
    return size;
}

