#include "Figure.hpp"


Figure::Figure(std::vector<Point> & points, int x, int y, char texture): 
	points(points), 
	x(x), 
	y(y), 
	texture(texture)
{    
}

std::vector<Point>& const Figure::getPoints()
{
    return points;
}

void Figure::MoveOn(int x, int y)
{
	this->x += x;
	this->y += y;
}

int Figure::getX()
{
	return this->x;
}

int Figure::getY()
{
	return this->y;
}

char Figure::getTexture()
{
	return this->texture;
}

Figure Figure::Copy()
{
	std::vector<Point> pointsCopy;
	pointsCopy.reserve(points.size());
	for (auto& point : points)
	{
		pointsCopy.push_back({ point.getX(), point.getY(), 0 });
	}
	Figure figure(pointsCopy, x, y, texture);
	return figure;
}
