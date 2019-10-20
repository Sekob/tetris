#pragma once
#include <windows.h>
#include <ctime>

#include "IConsoleScene.hpp"
#include "../BaseObjects/Figure.hpp"
#include "../Figures/LFigure.hpp"
#include "../Figures/JFigure.hpp"
#include "../Figures/OFigure.hpp"
#include "../Figures/TFigure.hpp"
#include "../Figures/SFigure.hpp"
#include "../Figures/ZFigure.hpp"
#include "../Figures/IFigure.hpp"

#define EMPTY_CELL (unsigned char)219
#define EMPTY_COLOR 0
#define BORDER_CELL '#'
#define FULL_WHITE_COLOR (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

class MainScene : public IConsoleScene {
	int width = 50;
	int height = 25;
	int ticks = 0;

	int leftBorderX = width / 2 - 5;
	int rightBorderX = width / 2 + 5;
	int topBorderY = height / 2 - 8;
	int bottomBorderY = height / 2 + 8;

	std::vector<CHAR_INFO> buffer;
	std::vector<Figure> figures;
	std::vector<Figure> availableFigures;

	std::vector<char> textures = { 'A', 'B', 'C', 'D', 'F', 'G', 'E' };
	std::vector<unsigned char> colors = { FOREGROUND_RED | BACKGROUND_RED,
										  FOREGROUND_GREEN | BACKGROUND_GREEN,
										  FOREGROUND_BLUE | BACKGROUND_BLUE,
										  FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN,
										  FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE,
										  FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN };
	void EraseFigure(Figure& figure);
	void DrawFigure(Figure& figure);
	void FillObject(Figure& figure, char texture, unsigned char color);
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
	virtual std::vector<CHAR_INFO>& Buffer() override;
	void SetSceneInfo(int width, int height) override;
	void KeyPressed(int key) override;
};