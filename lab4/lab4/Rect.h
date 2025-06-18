#pragma once
#include <iostream>
#include <algorithm>

class Rect {
public:
    Rect(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    bool operator<(const Rect& other) const {
        int distance = x * x + y * y;
        int otherDistance = other.x * other.x + other.y * other.y;

        return distance < otherDistance;
    }

private:
    int x, y;     
    int width, height;  
};


