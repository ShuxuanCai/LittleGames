#include <XEngine.h>

#include "Camera.h"
#include "TileMap.h"
#include "Link.h"

Link link;

void GameInit()
{
	Camera::StaticInitialize();

	link.Load();
	link.SetPosition({ 300.0f,300.0f });

	TileMap::StaticInitialize();
	TileMap::Get().Load("level_02.txt", "tileset_01.txt");
}

bool GameLoop(float deltaTime)
{
	TileMap::Get().Update(deltaTime);
	link.Update(deltaTime);

	Camera::Get().SetViewBound(TileMap::Get().GetBound());
	Camera::Get().SetViewPosition(link.GetPosition());

	TileMap::Get().Render();
	link.Render();

	// Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	TileMap::Get().Unload();
	TileMap::StaticTerminate();

	link.Unload();

	Camera::StaticTerminate();
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