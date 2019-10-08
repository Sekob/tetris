#include "Game.hpp"

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
}


void Game::Update()
{
	std::this_thread::sleep_for(refreshTime);

	if (GetAsyncKeyState(VK_SPACE) == IS_PUSHED)
		activeScene.KeyPressed(VK_SPACE);
	if (GetAsyncKeyState(VK_LEFT) == IS_PUSHED)
		activeScene.KeyPressed(VK_LEFT);
	if (GetAsyncKeyState(VK_RIGHT) == IS_PUSHED)
		activeScene.KeyPressed(VK_RIGHT);
	if (GetAsyncKeyState(VK_DOWN) == IS_PUSHED)
		activeScene.KeyPressed(VK_DOWN);

	DWORD written = 0;
	activeScene.Update();
	WriteConsoleOutputCharacter(this->outConsole, activeScene.Buffer().data(), this->screenHeight * this->screenWidth, { 0,0 }, &written);
}