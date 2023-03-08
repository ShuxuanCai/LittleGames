#include "Pokemon3.h"

void Pokemon3::Load()
{
	mTextureId = X::LoadTexture("Elekid.png");
	XASSERT(mTextureId != 0, "Could not find texture! Did you spell the name wrong?");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
}

void Pokemon3::Unload()
{
}

void Pokemon3::Update(float deltaTime)
{

}

void Pokemon3::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Pokemon3::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;

	mActive = true;
}

void Pokemon3::Kill()
{
	mActive = false;
}


