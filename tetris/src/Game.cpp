#include "Game.hpp"

//TODO: save and setup console and restore on destruction
Game::Game(IConsoleScene& scene) : activeScene(scene)
{
	outConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (outConsole == INVALID_HANDLE_VALUE)
	{
		LogHandler::LogError("Game faced with an error and faild: CreateConsoleScreenBuffer " + GetLastError());
		throw new std::exception("Internal exception while creating console buffer");
	}

	if (!SetConsoleActiveScreenBuffer(outConsole))
	{
		LogHandler::LogError("Game faced with an error and faild: SetConsoleActiveScreenBuffer " + GetLastError());
		throw new std::exception("Internal exception while setting active console");
	}

	//TODO: inverse logic
	CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo;
	if (!GetConsoleScreenBufferInfo(outConsole, &consoleBufferInfo))
	{
		LogHandler::LogError("Game faced with an error and faild: GetConsoleScreenBufferInfo " + GetLastError());
		throw new std::exception("Internal exception while getting active console info");
	}
	else
	{
		activeScene.SetSceneInfo(consoleBufferInfo.dwSize.X, consoleBufferInfo.dwSize.Y);
	}

	screenWidth = activeScene.Width();
	screenHeight = activeScene.Height();

	activeScene.Init();

	inputHandler.SetOnInputEvent([this](int button) {
		this->activeScene.KeyPressed(button);
		});
}


void Game::Update()
{
	std::this_thread::sleep_for(refreshTime);

	inputHandler.Update();
	activeScene.Update();

	COORD characterBufferSize = { screenWidth, screenHeight };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, screenWidth - 1, screenHeight - 1 };

	WriteConsoleOutputA(outConsole, activeScene.Buffer().data(), characterBufferSize, characterPosition, &consoleWriteArea);
}