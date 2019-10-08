#pragma once
#include <vector>
#include <stdio.h>
#include <windows.h>

#include "src/BaseObjects/Point.hpp"
#include "src/BaseObjects/Figure.hpp"
#include "src/Utils/FigureUtils.hpp"
#include "src/Game.hpp"
#include "src/Scene/MainScene.hpp"


int main() {
	MainScene scene;

	Game* game = new Game(scene);

	while (true)
		game->Update();

	delete game;
	return 0;
}