#include "FigureUtils.hpp"

void FigureUtils::RotateToRight(Figure& const figure)
{
	int maxX = 0;
	int maxY = 0;
	std::vector<Point>& const points = figure.getPoints();

	for (Point & point : points)
	{
		int x = point.getX();
		int y = point.getY();
		if (maxX < x)
			maxX = x;
		if (maxY < y)
			maxY = y;
	}
	
	for(Point& point : points)
	{
		int oldX = point.getX();
		point.setX(point.getY());
		point.setY(maxX - oldX);
	}
}

void FigureUtils::Rotate(Figure& const figure, Direction direction)
{
	if (direction == Direction::Right)
	{
		RotateToRight(figure);
		return;
	}
}