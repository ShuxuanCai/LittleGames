#pragma once

#include <XEngine.h>
#include "State.h"

class FallState : public State
{
public:
	void Load() override;
	void Update(Mario& owner, float delaTime) override;
};

