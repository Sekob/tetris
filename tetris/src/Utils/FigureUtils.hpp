#pragma once
#include "../BaseObjects/Figure.hpp"
#include "../BaseObjects/Point.hpp"

static class FigureUtils
{
	static void RotateToRight(Figure& const figure);
public:
	enum Direction { Left, Right };
	static void Rotate(Figure& const figure, Direction direction);
};
