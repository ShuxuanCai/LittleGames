#include "ElectroBall.h"

void ElectroBall::Load()
{
	mTextureId = X::LoadTexture("ElectroBall.png");
	//mTextureId = X::LoadTexture("Ember.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
}

void ElectroBall::Unload()
{

}

void ElectroBall::Update(float deltaTime)
{
	if (mActive)
	{
		mPosition += mVelocity * deltaTime;

		const uint32_t screenWidth = X::GetScreenWidth();
		const uint32_t screenHeight = X::GetScreenHeight();

		if (mPosition.x > screenWidth + mSpriteWidth
			|| mPosition.x < -mSpriteWidth
			|| mPosition.y > screenHeight + mSpriteHeight
			|| mPosition.y < -mSpriteHeight)
		{
			Kill();
		}
	}
}

void ElectroBall::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void ElectroBall::Fires(const X::Math::Vector2& position, const X::Math::Vector2& velocity)
{
	mPosition = position;
	mVelocity = velocity;

	mActive = true;
}

void ElectroBall::Kill()
{
	mActive = false;
}


void ElectroBall::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;

	mActive = true;
}