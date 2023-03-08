#pragma once

#include <XEngine.h>

#include "State.h"

enum class AnimationState
{
	None = -1,
	Idle,
	Walk,
	Jump,
	Fall
};

class Mario
{
public :
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void ChangeState(const AnimationState state);

	void SetVelocity(const X::Math::Vector2& velocity) { mVelocity = velocity; }
	void SetFacingLeft(const bool facingLeft) { mIsFacingLeft = facingLeft; }

	const X::Math::Vector2& GetPosition() const { return mPosition; }
	const X::Math::Vector2& GetVelocity() const { return mVelocity; }
	float GetMoveSpeed() const { return mMoveSpeed; }
	bool IsFacingLeft() const { return mIsFacingLeft; }

private:
	void ApplyGravity(float deltaTime);
	void StopIfOutOfBounds();

private:
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;

	float mMoveSpeed = 0.0f;
	bool mIsFacingLeft = false;

	std::shared_ptr<State> mCurrentState;
	std::vector<std::shared_ptr<State>> mStates;
};

