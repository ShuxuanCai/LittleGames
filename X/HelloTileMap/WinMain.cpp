#include <XEngine.h>
#include "TileMap.h"

TileMap myMap;

void GameInit()
{
	myMap.Load();
}

bool GameLoop(float deltaTime)
{
	myMap.Update(deltaTime);
	myMap.Render();

	// Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	myMap.Unload();
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