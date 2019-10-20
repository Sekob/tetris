#include "IFigure.hpp"

IFigure::IFigure(int x, int y)
{
	points.reserve(4);

	points.push_back({ 0,0,0 });
	points.push_back({ 0,1,0 });
	points.push_back({ 0,2,0 });
	points.push_back({ 0,3,0 });

	this->x = x;
	this->y = y;
}
