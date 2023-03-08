#pragma once
#include <XEngine.h>

class Boss
{
public:
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	//Class Specific Functions
	void Spawn(const X::Math::Vector2& spawnPosition);
	void Kill();
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, mHalfSpriteWidth); }

	//Geters and Setters (Accessors and Mutators)
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }

	bool IsActive() const { return mActive; }

private:
	X::TextureId mTextureId = 0;

	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;

	bool mActive = false;
	//float mDelay = 0.0f;
	float mHalfSpriteWidth = 0.0f;
	float mSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;
};


