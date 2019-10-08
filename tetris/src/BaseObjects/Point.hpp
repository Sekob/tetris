#pragma once
#include <stdint.h>
#include <tuple>

class Point
{
private:
    int x = 0;
    int y = 0;
    uint16_t color = 0; 
public:
    Point(int x, int y, uint16_t color);
    void Set(int x, int y, uint16_t color);
    std::tuple<int, int, uint16_t> Get();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};


