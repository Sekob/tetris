#pragma once
#include <vector>

#include "Point.hpp"

class Figure
{
private:
	int x = 0;
	int y = 0;
    std::vector<Point>  points;
	char texture = '#';

public:
    Figure(std::vector<Point> & points, int x, int y, char texture = '#');
    std::vector<Point>& const getPoints();
	void RotateRight();
	void RotateLeft();
	void MoveOn(int x, int y);
	int getX();
	int getY();
	char getTexture();
	void setTexture(char newTexture);
	Figure Copy();
};
 