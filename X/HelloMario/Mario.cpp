#include "Mario.h"

#include "IdleState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "FallState.h"

void Mario::Load()
{
	mPosition = { 300.0f, 50.0f };
	mMoveSpeed = 300.0f;

	// Load all satates (this order must match the enum)
	mStates.push_back(std::make_shared<IdleState>());
	mStates.push_back(std::make_shared<WalkState>());
	mStates.push_back(std::make_shared<JumpState>());
	mStates.push_back(std::make_shared<FallState>());

	for (auto&& state : mStates)
	{
		state->Load();
	}

	// Set to a default state
	ChangeState(AnimationState::Fall);
}

void Mario::Unload()
{
	for (auto&& state : mStates)
	{
		state->Unload();
	}

	mStates.clear();
	mCurrentState.reset();
}

void Mario::Update(float deltaTime)
{
	mCurrentState->Update(*this, deltaTime);

	ApplyGravity(deltaTime);
	StopIfOutOfBounds();
}

void Mario::Render()
{
	mCurrentState->Render(*this);
}

void Mario::ChangeState(const AnimationState state)
{
	// Lookup state within our vector of states
	std::shared_ptr<State> newState = mStates.at(static_cast<int>(state));

	// Check if we are already in this state
	if (mCurrentState == newState)
	{
		// We are already in this state!
		// If so, do nothing
		return;
	}

	// Exit our current state
	if (mCurrentState != nullptr)
	{
		mCurrentState->Exit(*this);
	}

	// Enter the new state
	mCurrentState = newState;
	if (mCurrentState != nullptr)
	{
		mCurrentState->Enter(*this);
	}
}

void Mario::ApplyGravity(float deltaTime)
{
	// Incrementally increase Y value (to fall downwards)
	mVelocity.y += 100.0f * deltaTime;

	// Cap the value to not fall too fast
	mVelocity.y = X::Math::Min(20.0f, mVelocity.y);
}

void Mario::StopIfOutOfBounds()
{
	// Note: We're only going to account for the floor.
	// Depending on your game requirements, you might
	// need to care about horizontal collision (or just
	// use a TileMap).

	// Update our x position by adding our x velocity
	// that is calculated in update.
	mPosition.x += mVelocity.x;

	// For our y position, check if we are in contact
	// with the bottom of the screen
	const float screenHeight = static_cast<float>(X::GetScreenHeight());
	if (mVelocity.y > 0.0f && mPosition.y >= screenHeight)
	{
		mPosition.y = screenHeight;
		mVelocity.y = 0.0f;

		// If falling, change to Idle
		if (mCurrentState == mStates.at(static_cast<int>(AnimationState::Fall)))
		{
			ChangeState(AnimationState::Idle);
		}
	}

	else // No vertical collision
	{
		// Update our y position by adding our y velocity
		// that is calculated in update
		mPosition.y += mVelocity.y;
	}
}
