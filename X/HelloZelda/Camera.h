#pragma once

#include <XEngine.h>

class Camera
{
public:
	// Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static Camera& Get();

public:
	X::Math::Vector2 ConvertToScreenPosition(const X::Math::Vector2& worldPosition) const;
	X::Math::Vector2 ConvertToWorldPosition(const X::Math::Vector2& screenPosition) const;

	void SetViewBound(const X::Math::Rect& viewBound);
	void SetViewPosition(const X::Math::Vector2& viewPosition);

private:
	X::Math::Rect mViewBound{ -FLT_MAX, -FLT_MAX, FLT_MAX, FLT_MAX };
	X::Math::Vector2 mOffset;
};

