#include "BossBullets.h"

void BossBullets::Load()
{
	mTextureId = X::LoadTexture("bullet2.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);
}

void BossBullets::Unload()
{

}

void BossBullets::Update(float deltaTime)
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

void BossBullets::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void BossBullets::Fire(const X::Math::Vector2& position, const X::Math::Vector2& velocity)
{
	mPosition = position;
	mVelocity = velocity;

	mActive = true;
}

void BossBullets::Kill()
{
	mActive = false;
}
