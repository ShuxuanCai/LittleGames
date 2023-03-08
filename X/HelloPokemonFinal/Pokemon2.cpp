#include "Pokemon2.h"

void Pokemon2::Load()
{
	mTextureId = X::LoadTexture("char.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
}

void Pokemon2::Unload()
{
}

void Pokemon2::Update(float deltaTime)
{

}

void Pokemon2::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Pokemon2::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;

	mActive = true;
}

void Pokemon2::Kill()
{
	mActive = false;
}

