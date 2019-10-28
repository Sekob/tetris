#pragma once
#include <functional>
#include <windows.h>

#include "IUpdatable.hpp"

#define IS_PUSHED -32767

class InputHandler: public IUpdatable
{
    std::function<void(int)> onInputEvent = nullptr;
public:
    virtual void Update() override;
    void SetOnInputEvent(std::function<void(int)> function);
};