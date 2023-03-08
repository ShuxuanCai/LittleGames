#pragma once

#include <XEngine.h>
#include "State.h"

class JumpState : public State
{
public:
	void Load() override;
	void Update(Mario& owner, float delaTime) override;

	void Enter(Mario& owner) override;
};

