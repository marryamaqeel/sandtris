#pragma once
#include <stdexcept>
#include <string>

class Shape
{
private:
    int  shapeType;
    int  size = 3;
    int* matrix;
public:
    // Constructor & Rule of Three
    Shape(int type);
    ~Shape();

    // Rotation
    void rotateRight();
    void rotateLeft();

    // Getters (const-correct)
    int getPixel(int x, int y) const;
    int getSize()              const;
};