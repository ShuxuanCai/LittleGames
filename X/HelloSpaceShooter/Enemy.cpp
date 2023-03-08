#include "Enemy.h"

void Enemy::Load()
{
	mTextureId = X::LoadTexture("carrier_01.png");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;

	mDelay = X::RandomFloat(1.0f, 3.0f);
}

void Enemy::Unload()
{
}

void Enemy::Update(float deltaTime)
{
	if (mActive)
	{
		mPosition += mVelocity * deltaTime;

		mDelay -= deltaTime;
		if (mDelay <= 0.0f)
		{
			//Flip the x value for our current velocity
			mVelocity.x *= -1.0f;

			//Reset the delay to a random number between 1 and 3 seconds
			mDelay = X::RandomFloat(1.0f, 3.0f);
		}

		const uint32_t screenWidth = X::GetScreenWidth();
		const uint32_t screenHeight = X::GetScreenHeight();

		//Ignore the top of the screen.
		if (mPosition.x > screenWidth + mSpriteWidth
			|| mPosition.x < -mSpriteWidth
			|| mPosition.y > screenHeight + mSpriteHeight)
		{
			Kill();
		}
	}
}

void Enemy::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Enemy::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;
	float velocityX = X::RandomFloat(-200.0f, 200.0f);
	mVelocity = X::Math::Vector2(velocityX, 200.0f);
	
	mActive = true;
}

void Enemy::Kill()
{
	mActive = false;
}

