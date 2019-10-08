#include "MainScene.hpp"

void MainScene::FillObject(Figure& figure, char texture)
{
	int x = figure.getX();
	int y = figure.getY();
	auto points = figure.getPoints();
	for (auto& point : points)
	{
		int realX = x + point.getX();
		int realY = y - point.getY();
		int i = realY * width + realX;
		if (i >= 0)
			buffer[i] = texture;
	}
}


void MainScene::EraseFigure(Figure& figure)
{
	FillObject(figure, EMPTY_CELL);
}

void MainScene::DrawFigure(Figure& figure)
{
	FillObject(figure, figure.getTexture());
}

bool MainScene::CanMove(Figure& figure, int x, int y)
{
	std::vector<Point>& const points = figure.getPoints();
	bool newXY = x != figure.getX() || y != figure.getY();
	if (newXY)
		EraseFigure(figure);

	bool canMove = true;

	for (auto&& point : points)
	{
		int64_t realX = (int64_t)x + point.getX();
		int64_t realY = (int64_t)y - point.getY();
		int64_t i = realY * width + realX;
		if (i < 0 || i > buffer.size() - 1 || buffer[i] != EMPTY_CELL)
		{
			canMove = false;
			break;
		}
	}

	if (newXY)
		DrawFigure(figure);

	return canMove;
}

void MainScene::MoveOn(Figure& figure, int x, int y)
{
	if (!CanMove(figure, figure.getX() + x, figure.getY() + y))
		return;
	EraseFigure(figure);
	figure.MoveOn(x, y);
	DrawFigure(figure);
}


void MainScene::MoveRight(Figure& figure)
{
	MoveOn(figure, 1, 0);
}

void MainScene::MoveLeft(Figure& figure)
{
	MoveOn(figure, -1, 0);
}

void MainScene::MoveDown(Figure& figure)
{
	MoveOn(figure, 0, 1);
}

void MainScene::RotateFigure(Figure& figure)
{
	EraseFigure(figure);
	FigureUtils::Rotate(figure, FigureUtils::Right);
	DrawFigure(figure);
	if (!CanMove(figure, figure.getX(), figure.getY()))
	{
		EraseFigure(figure);
		FigureUtils::Rotate(figure, FigureUtils::Left);
		DrawFigure(figure);
	}
}

void MainScene::AddRandowFigure()
{
	srand(time(0));
	int randomIndex = 0 + rand() % availableFigures.size();
	Figure& figure = availableFigures[randomIndex];
	Figure newFigure = figure.Copy();
	figures.push_back(newFigure);
}

void MainScene::RemoveCompletedLines()
{

}

void MainScene::Init()
{
	int leftBorderX = width / 2 - 5;
	int rightBorderX = width / 2 + 5;
	int topBorder = height / 2 - 8;
	int bottomBorder = height / 2 + 8;

	//###
	// #
	std::vector<Point> points1;
	points1.reserve(4);

	Point point11(0, 1, 0);
	Point point12(1, 1, 0);
	Point point13(2, 1, 0);
	Point point14(1, 0, 0);

	points1.push_back(point11);
	points1.push_back(point12);
	points1.push_back(point13);
	points1.push_back(point14);
	Figure figure1(points1, leftBorderX + 4, topBorder);
	availableFigures.push_back(figure1);
	//

	//##
	// ##
	std::vector<Point> points2;
	points2.reserve(4);

	Point point21(0, 1, 0);
	Point point22(1, 1, 0);
	Point point23(2, 0, 0);
	Point point24(1, 0, 0);

	points2.push_back(point21);
	points2.push_back(point22);
	points2.push_back(point23);
	points2.push_back(point24);
	Figure figure2(points2, leftBorderX + 4, topBorder);
	availableFigures.push_back(figure2);
	//

	//##
	//##
	std::vector<Point> points3;
	points3.reserve(4);

	Point point31(0, 1, 0);
	Point point32(1, 1, 0);
	Point point33(1, 0, 0);
	Point point34(0, 0, 0);

	points3.push_back(point31);
	points3.push_back(point32);
	points3.push_back(point33);
	points3.push_back(point34);
	Figure figure3(points3, leftBorderX + 4, topBorder);
	availableFigures.push_back(figure3);
	//

	//#
	//#
	//##
	std::vector<Point> points4;
	points4.reserve(4);

	Point point41(0, 2, 0);
	Point point42(0, 1, 0);
	Point point43(1, 0, 0);
	Point point44(0, 0, 0);

	points4.push_back(point41);
	points4.push_back(point42);
	points4.push_back(point43);
	points4.push_back(point44);
	Figure figure4(points4, leftBorderX + 4, topBorder);
	availableFigures.push_back(figure4);
	//

	AddRandowFigure();

	buffer.resize((int64_t)width * height, EMPTY_CELL);

	for (int64_t i = topBorder; i < bottomBorder; i++)
	{
		buffer[i * width + leftBorderX] = BORDER_CELL;
		buffer[i * width + rightBorderX] = BORDER_CELL;
	}

	for (int i = leftBorderX; i <= rightBorderX; i++)
	{
		buffer[(int64_t)bottomBorder * width + i] = BORDER_CELL;
	}
}

void MainScene::Update()
{
	ticks++;
	Figure& activeFigure = figures.back();

	if (!CanMove(activeFigure, activeFigure.getX(), activeFigure.getY() + 1))
	{

		AddRandowFigure();
		return;
	}

	if (ticks < 20)
		return;

	MoveDown(activeFigure);

	ticks = 0;
}

int MainScene::Width()
{
	return width;
}

int MainScene::Height()
{
	return height;
}

std::vector<char>& MainScene::Buffer()
{
	return buffer;
}

void MainScene::SetSceneInfo(int width, int height)
{
	this->width = width;
	this->height = height;
}

void MainScene::KeyPressed(int key)
{
	Figure& activeFigure = figures.back();
	switch (key)
	{
	case VK_SPACE:
		RotateFigure(activeFigure);
		break;
	case VK_RIGHT:
		MoveRight(activeFigure);
		break;
	case VK_LEFT:
		MoveLeft(activeFigure);
		break;
	case VK_DOWN:
		MoveDown(activeFigure);
	default:
		break;
	}
}
