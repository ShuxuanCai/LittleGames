#include "Link.h"
#include "TileMap.h"
#include "Camera.h"

void Link::Load()
{
	mTextureId = X::LoadTexture("zelda.png");
	mMoveSpeed = 250.0f;
	mHalfSpriteWidth = X::GetSpriteWidth(mTextureId) / 2.0f;
	mHalfSpriteHeight = X::GetSpriteHeight(mTextureId) / 2.0f;
}

void Link::Unload()
{

}

void Link::Update(float deltaTime)
{
	// Generic movement strategy when AABB collision is involved:
	// - Predict what the displacement WILL be based on player input
	// - Check for collision
	// - If collision occurs, set displacement to 0
	// - Add displacement to the position

	// Check for input and record amount of displacement
	X::Math::Vector2 displacement;
	if (X::IsKeyDown(X::Keys::W))
	{
		displacement.y -= mMoveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::A))
	{
		displacement.x -= mMoveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::S))
	{
		displacement.y += mMoveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::D))
	{
		displacement.x += mMoveSpeed * deltaTime;
	}

	// Check for collision
	const X::Math::Rect currentBoundingBox = GetBoundingBox();

	// Right edge
	if (displacement.x > 0.0f)
	{
		X::Math::LineSegment rightEdge{
			currentBoundingBox.max.x + displacement.x,
			currentBoundingBox.min.y,
			currentBoundingBox.max.x + displacement.x,
			currentBoundingBox.max.y
		};

		if (TileMap::Get().IsCollidingWith(rightEdge))
		{
			displacement.x = 0.0f;
		}
	}

	// Left edge
	if (displacement.x < 0.0f)
	{
		X::Math::LineSegment leftEdge{
			currentBoundingBox.min.x + displacement.x,
			currentBoundingBox.min.y,
			currentBoundingBox.min.x + displacement.x,
			currentBoundingBox.max.y
		};

		if (TileMap::Get().IsCollidingWith(leftEdge))
		{
			displacement.x = 0.0f;
		}
	}

	// Bottom edge
	if (displacement.y > 0.0f)
	{
		X::Math::LineSegment bottomEdge{
			currentBoundingBox.min.x,
			currentBoundingBox.max.y + displacement.y,
			currentBoundingBox.max.x, 
			currentBoundingBox.max.y + displacement.y
		};

		if (TileMap::Get().IsCollidingWith(bottomEdge))
		{
			displacement.y = 0.0f;
		}
	}

	// Top edge
	if (displacement.y < 0.0f)
	{
		X::Math::LineSegment topEdge{
			currentBoundingBox.min.x,
			currentBoundingBox.min.y + displacement.y,
			currentBoundingBox.max.x,
			currentBoundingBox.min.y + displacement.y
		};

		if (TileMap::Get().IsCollidingWith(topEdge))
		{
			displacement.y = 0.0f;
		}
	}

	// Add displacement to the position
	mPosition += displacement;
}

void Link::Render()
{
	const X::Math::Vector2 screenPosition = Camera::Get().ConvertToScreenPosition(mPosition);

	X::DrawSprite(mTextureId, screenPosition);
}

X::Math::Rect Link::GetBoundingBox() const
{
	// Construst a bounding box around Link
	return {
		mPosition.x - mHalfSpriteWidth,		// Left
		mPosition.y - mHalfSpriteHeight,	// Top
		mPosition.x + mHalfSpriteWidth,		// Right
		mPosition.y + mHalfSpriteHeight		// Bottom
	};
}
