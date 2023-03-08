#include "Fire.h"

void Fire::Load()
{
	mTextureId = X::LoadTexture("Ember.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
	mSpriteHeight = X::GetSpriteHeight(mTextureId);
}

void Fire::Unload()
{

}

void Fire::Update(float deltaTime)
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

void Fire::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Fire::Fires(const X::Math::Vector2& position, const X::Math::Vector2& velocity)
{
	mPosition = position;
	mVelocity = velocity;

	mActive = true;
}

void Fire::Kill()
{
	mActive = false;
}


void Fire::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;

	mActive = true;
}