#include "Point.hpp"

Point::Point(int x, int y, uint16_t color)
{
    this->x = x;
    this->y = y;
    this->color = color;
}

void Point::Set(int x, int y, uint16_t color)
{
    this->x = x;
    this->y = y;
    this->color = color;
}

std::tuple<int, int, uint16_t> Point::Get()
{
    return std::make_tuple(this->x, this->y, this->color);
}

int Point::getX()
{
    return this->x;
}

int Point::getY()
{
    return this->y;
}

void Point::setX(int x)
{
    this->x = x;
}

void Point::setY(int y)
{
    this->y = y;
}