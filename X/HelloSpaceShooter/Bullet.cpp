#include "Bullet.h"
#include "Boss.h"

void Bullet::Load()
{
	mTextureId = X::LoadTexture("bullet1.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);
}

void Bullet::Unload()
{

}

void Bullet::Update(float deltaTime)
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

void Bullet::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Bullet::Fire(const X::Math::Vector2& position, const X::Math::Vector2& velocity)
{
	mPosition = position;
	mVelocity = velocity;
	bossPosition = boss.GetPosition();

	mActive = true;
}

void Bullet::Kill()
{
	mActive = false;
}