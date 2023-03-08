#include "Boss.h"

void Boss::Load()
{
	mTextureId = X::LoadTexture("bullet_bill.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
}

void Boss::Unload()
{
}

void Boss::Update(float deltaTime)
{
	if (mActive)
	{
		mPosition += mVelocity * deltaTime;

		const uint32_t screenWidth = X::GetScreenWidth();
		const uint32_t screenHeight = X::GetScreenHeight();
		const float halfSpriteWidth = X::GetSpriteWidth(mTextureId) / 2.0f;
		const float halfSpriteHeight = X::GetSpriteHeight(mTextureId) / 2.0f;

		//Right side of screen 
		if (mPosition.x > screenWidth - halfSpriteWidth)
		{
			mPosition.x = screenWidth - halfSpriteWidth;
			mVelocity.x = -200.0f;
		}

		//Left side of screen 
		if (mPosition.x < halfSpriteWidth)
		{
			mPosition.x = halfSpriteWidth;
			mVelocity.x = 200.0f;
		}
	}
}

void Boss::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Boss::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;
	mVelocity = X::Math::Vector2(200.0f, 0.0f);

	mActive = true;
}

void Boss::Kill()
{
	mActive = false;
}

