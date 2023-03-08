#pragma once

#include <XEngine.h>

class Link
{
public:
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	//Geters and Setters (Accessors and Mutators)
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }
	
	X::Math::Rect GetBoundingBox() const; 
	
private:
	X::TextureId mTextureId = 0;
	X::Math::Vector2 mPosition;

	float mMoveSpeed = 0.0f;
	float mHalfSpriteWidth = 0.0f;
	float mHalfSpriteHeight = 0.0f;
};

