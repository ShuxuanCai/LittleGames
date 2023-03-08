#include "FallState.h"

#include "Mario.h"

void FallState::Load()
{
	mTextureId = X::LoadTexture("mario_fall_01.png");
}

void FallState::Update(Mario& owner, float deltaTime)
{
	// Moving left
	if (X::IsKeyDown(X::Keys::A))
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

	// No horizontal movement
	else
	{
		auto velocity = owner.GetVelocity();
		velocity.x = 0.0f;

		owner.SetVelocity(velocity);
	}
}
