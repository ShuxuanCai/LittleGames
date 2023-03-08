#pragma once

#include <XEngine.h>

// In a more fleshed out system, this would be
// a generic base class of some sort, like "GameObject"
class Mario;

class State
{
public:
	virtual ~State() {}

	//Standard Object Function
	virtual void Load() = 0;
	virtual void Unload();
	virtual void Update(Mario& owner, float deltaTime) = 0;
	virtual void Render(Mario& owner);

	virtual void Enter(Mario& owner);
	virtual void Exit(Mario& owner);

protected:
	X::TextureId mTextureId = 0;
};

// State* walkState = new WalkState();