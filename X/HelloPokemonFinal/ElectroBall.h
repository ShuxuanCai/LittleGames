#pragma once

#include <XEngine.h>

class ElectroBall
{
public:
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	//Class specific function
	void Fires(const X::Math::Vector2& position, const X::Math::Vector2& velocity);
	void Spawn(const X::Math::Vector2& spawnPosition);
	void Kill();
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, mHalfSpriteWidth); }

	//Getters and Setters
	bool IsActive() const { return mActive; }

private:
	X::TextureId mTextureId = 0;

	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;
	float mSpriteWidth = 0.0f;
	float mHalfSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;

	bool mActive = false;
};

