#include "Figure.hpp"


Figure::Figure(std::vector<Point> & points, int x, int y, char texture, unsigned char color): 
	points(points), 
	x(x), 
	y(y), 
	texture(texture),
	color(color)
{    
}

Figure::Figure()
{
}

std::vector<Point>& const Figure::getPoints()
{
    return points;
}

void Figure::RotateRight()
{
	int maxX = 0;
	int maxY = 0;

	for (Point& point : points)
	{
		int x = point.getX();
		int y = point.getY();
		if (maxX < x)
			maxX = x;
		if (maxY < y)
			maxY = y;
	}

	for (Point& point : points)
	{
		int oldX = point.getX();
		point.setX(point.getY());
		point.setY(maxX - oldX);
	}
}

void Figure::RotateLeft()
{
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

unsigned char Figure::getColor()
{
	return color;
}

void Figure::setColor(unsigned char newColor)
{
	color = newColor;
}

void Figure::setTexture(char newTexture)
{
	texture = newTexture;
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
