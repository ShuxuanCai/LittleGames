#include "WalkState.h"
#include "Mario.h"

void WalkState::Load()
{
	mTextureId = X::LoadTexture("mario_walk_01.png");
}

void WalkState::Update(Mario& owner, float deltaTime)
{
	// Jumping
	if (X::IsKeyDown(X::Keys::SPACE))
	{
		owner.ChangeState(AnimationState::Jump);
	}

	// Moving left
	else if (X::IsKeyDown(X::Keys::A))
	{
		auto velocity = owner.GetVelocity();
		velocity.x = -owner.GetMoveSpeed() * deltaTime;

		owner.SetVelocity(velocity);
		owner.SetFacingLeft(true);
	}

	// Moving right
	else if (X::IsKeyDown(X::Keys::D))
	{
		auto velocity = owner.GetVelocity();
		velocity.x = owner.GetMoveSpeed() * deltaTime;

		owner.SetVelocity(velocity);
		owner.SetFacingLeft(false);
	}

	// In the right circumstances, alse check for transitioning
	// to AnimationState::Fall (walking off a ledge for example)
	else
	{
		owner.ChangeState(AnimationState::Idle);
	}
}
