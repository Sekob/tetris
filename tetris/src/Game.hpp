#pragma once
#include <windows.h>
#include <vector>
#include <thread>

#include "Utils/LogHandler.hpp"
#include "Scene/IConsoleScene.hpp"
#include "BaseObjects/IUpdatable.hpp"
#include "BaseObjects/InputHandler.hpp"

#define IS_PUSHED -32767

using namespace std::chrono_literals;

class Game: public IUpdatable
{
	std::vector<char> screenBuffer;
	short screenWidth = 50;
	short screenHeight = 50;
	int ticks = 0;
	HANDLE outConsole;
	IConsoleScene& activeScene;
	
	InputHandler inputHandler;

	std::chrono::milliseconds refreshTime = 50ms;
public:
	Game(IConsoleScene& scene);
	//void SetScene(IConsoleScene & scene);
	virtual void Update() override;
};