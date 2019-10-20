#include "MainScene.hpp"

void MainScene::FillObject(Figure& figure, char texture, unsigned char color)
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
		{
			buffer[i].Char.AsciiChar = texture;
			buffer[i].Attributes = color;
		}
	}
}


void MainScene::EraseFigure(Figure& figure)
{
	FillObject(figure, EMPTY_CELL, EMPTY_COLOR);
}

void MainScene::DrawFigure(Figure& figure)
{
	FillObject(figure, figure.getTexture(), figure.getColor());
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
		int realX = x + point.getX();
		int realY = y - point.getY();
		int i = realY * width + realX;
		if (i < 0 || i > buffer.size() - 1 || (unsigned char)buffer[i].Char.AsciiChar != EMPTY_CELL)
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
	figure.RotateRight();
	DrawFigure(figure);
	if (!CanMove(figure, figure.getX(), figure.getY()))
	{
		EraseFigure(figure);
		figure.RotateLeft();
		DrawFigure(figure);
	}
}

void MainScene::AddRandomFigure()
{
	srand(time(0));
	int randomIndex = 0 + rand() % availableFigures.size();
	Figure& figure = availableFigures[randomIndex];
	Figure newFigure = figure.Copy();

	srand(time(0));
	randomIndex = 0 + rand() % textures.size();
	newFigure.setTexture(textures[randomIndex]);

	srand(time(0));
	randomIndex = 0 + rand() % colors.size();
	newFigure.setColor(colors[randomIndex]);

	figures.push_back(newFigure);
}



void MainScene::RemoveCompletedLines()
{
	int lineGap = 0;
	int lastRow = bottomBorderY - 1;
	for (size_t i = lastRow; i > topBorderY; i--)
	{
		if (CheckLine(i))
		{
			lineGap++;
		}
		else if (lineGap != 0)
		{
			MoveUncompletedLine(i, i + lineGap);
		}
	}
}

void MainScene::MoveUncompletedLine(int from, int to)
{
	int sourceCell = 0;
	int targetCell = 0;
	int firstCellInRow = leftBorderX + 1;
	for (size_t i = firstCellInRow; i < rightBorderX; i++)
	{
		targetCell = to * width + i;
		sourceCell = from * width + i;
		buffer[targetCell] = buffer[sourceCell];
		buffer[sourceCell].Char.AsciiChar = EMPTY_CELL;
		buffer[sourceCell].Attributes = EMPTY_COLOR;
	}
}

bool MainScene::CheckLine(int i)
{
	int cellIndex = 0;
	int firstCellInRow = leftBorderX + 1;
	for (size_t j = firstCellInRow; j < rightBorderX; j++)
	{
		cellIndex = i * width + j;
		if ((unsigned char)buffer[cellIndex].Char.AsciiChar == EMPTY_CELL)
			return false;
	}
	return true;
}

void MainScene::Init()
{
	IFigure ifigure(leftBorderX + 4, topBorderY);
	availableFigures.push_back(ifigure);

	TFigure tfigure(leftBorderX + 4, topBorderY);
	availableFigures.push_back(tfigure);

	SFigure sfigure(leftBorderX + 4, topBorderY);
	availableFigures.push_back(sfigure);

	ZFigure zfigure(leftBorderX + 4, topBorderY);
	availableFigures.push_back(zfigure);

	OFigure ofigure(leftBorderX + 4, topBorderY);
	availableFigures.push_back(ofigure);

	LFigure lfigure(leftBorderX + 4, topBorderY);
	availableFigures.push_back(lfigure);

	JFigure Jfigure(leftBorderX + 4, topBorderY);
	availableFigures.push_back(Jfigure);


	AddRandomFigure();

	CHAR_INFO emptyChar;
	emptyChar.Char.AsciiChar = EMPTY_CELL;
	emptyChar.Attributes = EMPTY_COLOR;

	buffer.resize((int64_t)width * height, emptyChar);

	int leftBorderCellIndex = 0;
	int rightBorderCellIndex = 0;

	CHAR_INFO borderCell;
	borderCell.Char.AsciiChar = BORDER_CELL;
	borderCell.Attributes = FULL_WHITE_COLOR;
	for (size_t i = topBorderY; i < bottomBorderY; i++)
	{
		leftBorderCellIndex = i * width + leftBorderX;
		rightBorderCellIndex = i * width + rightBorderX;

		buffer[leftBorderCellIndex] = borderCell;
		buffer[rightBorderCellIndex] = borderCell;
	}

	int bottomBorderCellIndex = 0;
	for (size_t i = leftBorderX; i <= rightBorderX; i++)
	{
		bottomBorderCellIndex = bottomBorderY * width + i;
		buffer[bottomBorderCellIndex].Char.AsciiChar = BORDER_CELL;
		buffer[bottomBorderCellIndex].Attributes = FULL_WHITE_COLOR;
	}
}

void MainScene::Update()
{
	ticks++;
	Figure& activeFigure = figures.back();

	if (!CanMove(activeFigure, activeFigure.getX(), activeFigure.getY() + 1))
	{
		RemoveCompletedLines();
		AddRandomFigure();
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

std::vector<CHAR_INFO>& MainScene::Buffer()
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
