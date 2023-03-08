#pragma once

#include <XEngine.h>

class Pokemon3
{
public:
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void Spawn(const X::Math::Vector2& spawnPosition);
	void Kill();
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, mHalfSpriteWidth); }

	const X::Math::Vector2& GetPosition() const { return mPosition; }
	const int& GetHp() const { return hp; }

	bool IsActive() const { return mActive; }

private:
	X::TextureId mTextureId = 0;

	X::Math::Vector2 mPosition;
	float mSpriteWidth = 0.0f;
	float mHalfSpriteWidth = 0.0f;

	int hp = 100;

	bool mActive = false;
};



