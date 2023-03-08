#pragma once

#include <XEngine.h>

class TileMap
{
public:
	//Standard Object Function
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

private:
	int GetIndex(int column, int row) const;

	int* mMap = nullptr;
	int mColumns = 0;
	int mRow = 0;

	std::vector<X::TextureId> mTiles;
};
