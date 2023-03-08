#include "Pokemon1.h"

void Pokemon1::Load()
{
	mTextureId = X::LoadTexture("pikachu_02.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
}

void Pokemon1::Unload()
{
}

void Pokemon1::Update(float deltaTime)
{
	
}

void Pokemon1::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Pokemon1::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;

	mActive = true;
}

void Pokemon1::Kill()
{
	mActive = false;
}

