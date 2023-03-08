#include "TileMap.h"

namespace
{
	// This should change based on the
	// texture size where is using
	const float tileSize = 32.0f;

	const int testMapColumns = 10;
	const int testMapRows = 10;

	int selectedTileIndex = 0;

	// This is a 1D array
	int testMap[testMapColumns * testMapRows] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 2, 3, 0,
		0, 0, 0, 0, 0, 0, 0, 4, 5, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
}

void TileMap::Load()
{
	// In the future, we will load this from a .txt file
	// For now, we'll just use the testMap
	mColumns = testMapColumns;
	mRow = testMapRows;

	// Do a deep copy of testMap.
	// Note: iterating through the Y value first (rows)
	//		 in order to read the array from left to right
	mMap = new int[mColumns * mRow];
	for (int y = 0; y < mRow; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = GetIndex(x, y);
			mMap[index] = testMap[index];
		}
	}

	mTiles.push_back(X::LoadTexture("grass.png"));	//0
	mTiles.push_back(X::LoadTexture("flower.png")); //1
	mTiles.push_back(X::LoadTexture("tree0.png"));	//2
	mTiles.push_back(X::LoadTexture("tree1.png"));	//3
	mTiles.push_back(X::LoadTexture("tree2.png"));	//4
	mTiles.push_back(X::LoadTexture("tree3.png"));	//5
}

void TileMap::Unload()
{
	mColumns = 0;
	mRow = 0;

	delete[] mMap;
	mMap = nullptr;

	mTiles.clear();
}

void TileMap::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ONE))
	{
		//Grass
		selectedTileIndex = 0;
	}
	else if (X::IsKeyPressed(X::Keys::TWO))
	{
		//Flower
		selectedTileIndex = 1;
	}

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const int mouseX = X::GetMouseScreenX();
		const int mouseY = X::GetMouseScreenY();
		
		const int columnSelected = mouseX / tileSize;
		const int rowSelected = mouseY / tileSize;

		if (columnSelected >= 0 && columnSelected < mColumns
			&& rowSelected >= 0 && rowSelected < mRow)
		{
			const int mapIndex = GetIndex(columnSelected, rowSelected);
			mMap[mapIndex] = selectedTileIndex;
		}
	}
}

void TileMap::Render()
{
	for (int y = 0; y < mRow; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];

			const X::TextureId textureId = mTiles.at(tileIndex);
			const X::Math::Vector2 position = { x * tileSize, y * tileSize };

			X::DrawSprite(textureId, position, X::Pivot::TopLeft);
		}
	}
}

int TileMap::GetIndex(int column, int row) const
{
	// Example:
	// if looking for column 1 and row 3 with 10 total columns
	// index = 1 + (3 * 10);
	// index = 31;

	return column + (row * mColumns);
}