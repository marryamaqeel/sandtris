#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>

class Shape
{
private:
    int* Matrix;
    static const int size = 3;
    int shapeType;

public:
    Shape(int type);
    ~Shape();

    void rotateRight();
    void rotateLeft();

    int getSize() const;

    int getPixel(int x, int y) const;
};

#endif
