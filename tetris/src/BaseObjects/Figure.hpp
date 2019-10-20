#pragma once
#include <vector>

#include "Point.hpp"

class Figure
{
protected:
	int x = 0;
	int y = 0;
    std::vector<Point>  points;
	char texture = '#';
	unsigned char color = 0;

public:
    Figure(std::vector<Point> & points, int x, int y, char texture = '#', unsigned char color= 255);
	Figure();
    std::vector<Point>& getPoints();
	void RotateRight();
	void RotateLeft();
	void MoveOn(int x, int y);
	int getX();
	int getY();
	char getTexture();
	unsigned char getColor();
	void setColor(unsigned char newColor);
	void setTexture(char newTexture);
	Figure Copy();
};
 