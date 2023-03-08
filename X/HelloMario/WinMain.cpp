#include <XEngine.h>

#include "Mario.h"

Mario mario;

void GameInit()
{
	mario.Load();
}

bool GameLoop(float deltaTime)
{
	mario.Update(deltaTime);
	mario.Render();

	// Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	mario.Unload();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}