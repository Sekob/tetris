#pragma once
#include <functional>
#include <windows.h>
#include <vector>

#include "IUpdatable.hpp"

#define IS_PUSHED -32767

class InputHandler: public IUpdatable
{
    std::function<void(int)> onInputEvent = nullptr;
    std::vector<int> interestingKeys = {VK_SPACE, VK_LEFT, VK_RIGHT, VK_DOWN};
public:
    virtual void Update() override;
    void SetOnInputEvent(std::function<void(int)> function);
};