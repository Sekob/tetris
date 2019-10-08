#pragma once
#include <vector>

class IConsoleScene
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual int Width() = 0;
	virtual int Height() = 0;
	virtual std::vector<char>& Buffer() = 0;
	virtual void SetSceneInfo(int width, int height) = 0;
	//TODO: Create Input system
	virtual void KeyPressed(int key) = 0;
};

