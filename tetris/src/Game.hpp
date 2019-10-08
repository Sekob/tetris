#pragma once
#include <windows.h>
#include <vector>
#include <thread>

#include "Utils/LogHandler.hpp"
#include "Scene/IConsoleScene.hpp"

#define IS_PUSHED -32767

using namespace std::chrono_literals;

class Game
{
	std::vector<char> screenBuffer;
	short screenWidth = 50;
	short screenHeight = 50;
	int ticks = 0;
	HANDLE outConsole;
	IConsoleScene& activeScene;

	std::chrono::milliseconds refreshTime = 50ms;
public:
	Game(IConsoleScene& scene);
	//void SetScene(IConsoleScene & scene);
	void Update();
};