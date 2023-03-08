#include "JumpState.h"

#include "Mario.h"

namespace
{
	constexpr float JUMP_SPEED = -30.0f;
}

void JumpState::Load()
{
	mTextureId = X::LoadTexture("mario_jump_01.png");
}

void JumpState::Update(Mario& owner, float deltaTime)
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
	
	// When y velocity is 0, it means we've reached the zenith
	// of the jump, so switch to fall state
	if (owner.GetVelocity().y >= 0.0f)
	{
		owner.ChangeState(AnimationState::Fall);
	}
}

void JumpState::Enter(Mario& owner)
{
	State::Enter(owner);

	auto velocity = owner.GetVelocity();
	velocity.y = JUMP_SPEED;

	owner.SetVelocity(velocity);
}
