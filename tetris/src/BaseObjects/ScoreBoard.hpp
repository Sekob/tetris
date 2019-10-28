#pragma once

#include "BaseObjects/IUpdatable.hpp"

class ScoreBoard: public IUpdatable
{
public:
    virtual void Update() override;
};
