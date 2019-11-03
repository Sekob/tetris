#include "InputHandler.hpp"

void InputHandler::Update()
{
    if (!onInputEvent)
        return;
    
    for(int key : interestingKeys)
    {
        if(GetAsyncKeyState(key) == IS_PUSHED)
            onInputEvent(key);
    }
}

void InputHandler::SetOnInputEvent(std::function<void(int)> function)
{
    onInputEvent = function;
}
