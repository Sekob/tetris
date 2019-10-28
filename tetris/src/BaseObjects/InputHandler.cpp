#include "InputHandler.hpp"

void InputHandler::Update()
{
    if (onInputEvent)
    {
        if (GetAsyncKeyState(VK_SPACE) == IS_PUSHED)
            onInputEvent(VK_SPACE);
        if (GetAsyncKeyState(VK_LEFT) == IS_PUSHED)
            onInputEvent(VK_LEFT);
        if (GetAsyncKeyState(VK_RIGHT) == IS_PUSHED)
            onInputEvent(VK_RIGHT);
        if (GetAsyncKeyState(VK_DOWN) == IS_PUSHED)
            onInputEvent(VK_DOWN);
    }
}

void InputHandler::SetOnInputEvent(std::function<void(int)> function)
{
    onInputEvent = function;
}
