#include "Camera.h"

namespace
{
	std::unique_ptr<Camera> cameraInstance = nullptr;
}

void Camera::StaticInitialize()
{
	XASSERT(cameraInstance == nullptr, "Camera already initialized!");
	cameraInstance = std::make_unique<Camera>();
}

void Camera::StaticTerminate()
{
	cameraInstance.reset();
}

Camera& Camera::Get()
{
	XASSERT(cameraInstance != nullptr, "Camera not yet created! Must call StaticInitialize first!");
	return *cameraInstance;
}

X::Math::Vector2 Camera::ConvertToScreenPosition(const X::Math::Vector2& worldPosition) const
{
	return worldPosition - mOffset;
}

X::Math::Vector2 Camera::ConvertToWorldPosition(const X::Math::Vector2& screenPosition) const
{
	return screenPosition + mOffset;
}

void Camera::SetViewBound(const X::Math::Rect& viewBound)
{
	mViewBound = viewBound;

	const float screenWidth = static_cast<float>(X::GetScreenWidth());
	const float screenHeight = static_cast<float>(X::GetScreenHeight());

	if (mViewBound.right - mViewBound.left < screenWidth)
	{
		mViewBound.right = mViewBound.left + screenWidth;
	}

	if (mViewBound.bottom - mViewBound.top < screenHeight)
	{
		mViewBound.bottom = mViewBound.top + screenHeight;
	}
}

void Camera::SetViewPosition(const X::Math::Vector2& viewPosition)
{
	const float screenWidth = static_cast<float>(X::GetScreenWidth());
	const float screenHeight = static_cast<float>(X::GetScreenHeight());

	const X::Math::Vector2 halfScreenSize{ screenWidth / 2.0f, screenHeight / 2.0f };

	// Compute the position offset
	mOffset = viewPosition - halfScreenSize;

	// Ensure offset is within our view bound
	if (mOffset.x < mViewBound.left)
	{
		mOffset.x = mViewBound.left;
	}

	if (mOffset.y < mViewBound.top)
	{
		mOffset.y = mViewBound.top;
	}

	if (mOffset.x > mViewBound.right - screenWidth)
	{
		mOffset.x = mViewBound.right - screenWidth;
	}

	if (mOffset.y > mViewBound.bottom - screenHeight)
	{
		mOffset.y = mViewBound.bottom - screenHeight;
	}
}