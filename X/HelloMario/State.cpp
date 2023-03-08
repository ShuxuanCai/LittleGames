#include "State.h"

#include "Mario.h"

void State::Unload()
{
	mTextureId = 0;
}

void State::Render(Mario& owner)
{
	const X::Flip flipType = owner.IsFacingLeft() ? X::Flip::Horizontal : X::Flip::None;

	// Same with line 7
	/*X::Flip flipType2;
	if (owner.IsFacingLeft())
	{
		flipType2 = X::Flip::Horizontal;
	}
	else
	{
		flipType2 = X::Flip::None;
	}*/

	X::DrawSprite(mTextureId, owner.GetPosition(), X::Pivot::Bottom, flipType);
}

void State::Enter(Mario& owner)
{
	// This is where to begin sprite animation,
	// for example
}

void State::Exit(Mario& owner)
{
	// This is where to end sprite animation,
	// for example
}