#include "ZFigure.hpp"

ZFigure::ZFigure(int x, int y)
{
	points.reserve(4);

	points.push_back({ 1,1,0 });
	points.push_back({ 0,1,0 });
	points.push_back({ 1,0,0 });
	points.push_back({ 2,0,0 });

	this->x = x;
	this->y = y;
}
