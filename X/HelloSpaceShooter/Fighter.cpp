#include "Fighter.h"

void Fighter::Load()
{
	mTextureId = X::LoadTexture("fighter.png");

	mPosition = { 640.0f, 500.0f };

	mMoveSpeed = 500.0f;

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
}

void Fighter::Unload()
{
}

void Fighter::Update(float deltaTime)
{
	if (X::IsKeyDown(X::Keys::W))
	{
		mPosition.y -= mMoveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::A))
	{
		mPosition.x -= mMoveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::S))
	{
		mPosition.y += mMoveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::D))
	{
		mPosition.x += mMoveSpeed * deltaTime;
	}

	const uint32_t screenWidth = X::GetScreenWidth();
	const uint32_t screenHeight = X::GetScreenHeight();
	const float halfSpriteWidth = X::GetSpriteWidth(mTextureId) / 2.0f;
	const float halfSpriteHeight = X::GetSpriteHeight(mTextureId) / 2.0f;

	//Right side of screen 
	if (mPosition.x > screenWidth - halfSpriteWidth)
	{
		mPosition.x = screenWidth - halfSpriteWidth;
	}

	//Left side of screen 
	if (mPosition.x < halfSpriteWidth)
	{
		mPosition.x = halfSpriteWidth;
	}

	//Bottom side of screen 
	if (mPosition.y > screenHeight - halfSpriteHeight)
	{
		mPosition.y = screenHeight - halfSpriteHeight;
	}

	//Top side of screen 
	if (mPosition.y < halfSpriteHeight)
	{
		mPosition.y = halfSpriteHeight;
	}
}

void Fighter::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Fighter::Kill()
{
	mActive = false;
}

void Fighter::Spawn(const X::Math::Vector2& spawnPosition)
{
	mPosition = spawnPosition;

	mActive = true;
}