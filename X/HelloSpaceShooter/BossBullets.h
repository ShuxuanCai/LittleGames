#pragma once

#include <XEngine.h>

class BossBullets
{
public:
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	//Class specific function
	void Fire(const X::Math::Vector2& position, const X::Math::Vector2& velocity);
	void Kill();
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, 10.0f); }

	//Getters and Setters
	bool IsActive() const { return mActive; }

private:
	X::TextureId mTextureId = 0;

	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;

	bool mActive = false;
	float mSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;
	float mDelay = 0.0f;
};



