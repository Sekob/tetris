#pragma once
#include <windows.h>

#include "IConsoleScene.hpp"
#include <ctime>

#include "../BaseObjects/Figure.hpp"
#include "../Utils/FigureUtils.hpp"


#define EMPTY_CELL ' '
#define BORDER_CELL '#'

class MainScene : public IConsoleScene {
	int width = 50;
	int height = 25;
	int ticks = 0;

	int leftBorderX = width / 2 - 5;
	int rightBorderX = width / 2 + 5;
	int topBorderY = height / 2 - 8;
	int bottomBorderY = height / 2 + 8;

	std::vector<char> buffer;
	std::vector<Figure> figures;
	std::vector<Figure> availableFigures;

	void EraseFigure(Figure& figure);
	void DrawFigure(Figure& figure);
	void FillObject(Figure& figure, char texture);
	bool CanMove(Figure& figure, int x, int y);
	void MoveOn(Figure& figure, int x, int y);
	void MoveRight(Figure& figure);
	void MoveLeft(Figure& figure);
	void MoveDown(Figure& figure);
	void RotateFigure(Figure& figure);
	void AddRandomFigure();
	void RemoveCompletedLines();
	void MoveUncompletedLine(int from, int to);
	bool CheckLine(int i);
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual int Width() override;
	virtual int Height() override;
	virtual std::vector<char>& Buffer() override;
	void SetSceneInfo(int width, int height) override;
	void KeyPressed(int key) override;
};