#pragma once

#include <XEngine.h>

class Fighter
{
public:
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void Kill();
	void Spawn(const X::Math::Vector2& spawnPosition);

	//Geters and Setters (Accessors and Mutators)
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, mHalfSpriteWidth); }
	bool IsActive() const { return mActive; }
	float mMoveSpeed = 0.0f;

private:
	X::TextureId mTextureId = 0;
	X::Math::Vector2 mPosition;

	float mSpriteWidth = 0.0f;
	float mHalfSpriteWidth = 0.0f;
	bool mActive = false;
};

