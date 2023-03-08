#include "IdleState.h"

#include "Mario.h"

void IdleState::Load()
{
	mTextureId = X::LoadTexture("mario_idle_01.png");
}

void IdleState::Update(Mario& owner, float delaTime)
{
	// Jumping
	if (X::IsKeyDown(X::Keys::SPACE))
	{
		owner.ChangeState(AnimationState::Jump);
	}
	// Moving left or right
	else if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::D))
	{
		owner.ChangeState(AnimationState::Walk);
	}
}

void IdleState::Enter(Mario& owner)
{
	State::Enter(owner);

	owner.SetVelocity(X::Math::Vector2());
}

