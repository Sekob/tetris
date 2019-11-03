#pragma once

#include "IUpdatable.hpp"

class ScoreBoard: public IUpdatable
{
public:
    virtual void Update() override;
};
