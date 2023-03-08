#include "TileMap.h"
#include "Camera.h"

namespace
{
	// This should change based on the
	// texture size where is using
	const float tileSize = 32.0f;

	std::unique_ptr<TileMap> tileMapInstance;
}

void TileMap::StaticInitialize()
{
	XASSERT(tileMapInstance == nullptr, "TileMap already initialized!");
	tileMapInstance = std::make_unique<TileMap>();
}

void TileMap::StaticTerminate()
{
	tileMapInstance.reset();
}

TileMap& TileMap::Get()
{
	XASSERT(tileMapInstance != nullptr, "TileMap not yet created! Must call StaticInitialize first!");
	return *tileMapInstance;
}

void TileMap::Load(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName)
{
	LoadMap(mapName);
	LoadTexture(tilesetName);
}

void TileMap::Unload()
{
	mTiles.clear();

	mColumns = 0;
	mRows = 0;

	mMap.reset();
}

void TileMap::Update(float deltaTime)
{
	// Empty
}

void TileMap::Render()
{
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];

			const X::TextureId textureId = mTiles.at(tileIndex);
			const X::Math::Vector2 worldPosition = { x * tileSize, y * tileSize };
			const X::Math::Vector2 screenPosition = Camera::Get().ConvertToScreenPosition(worldPosition);

			X::DrawSprite(textureId, screenPosition, X::Pivot::TopLeft);
		}
	}
}

bool TileMap::IsCollidingWith(const X::Math::LineSegment& lineSegment) const
{
	const int startX = static_cast<int>(lineSegment.from.x / tileSize);
	const int startY = static_cast<int>(lineSegment.from.y / tileSize);
	const int endX = static_cast<int>(lineSegment.to.x / tileSize);
	const int endY = static_cast<int>(lineSegment.to.y / tileSize);

	// If out of bounds of the tile map
	if (startX < 0 || startX >= mColumns ||
		startY < 0 || startY >= mRows ||
		endX < 0 || endX >= mColumns ||
		endY < 0 || endY >= mRows)
	{
		return true;
	}

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			const int index = GetIndex(x, y);
			if (mMap[index] > 1 && mMap[index] != 6) // Not grass (0), not flower (1)
			{
				return true;
			}
		}
	}

	return false;
}

bool TileMap::IsCollidingWithGrass(const X::Math::LineSegment& lineSegment) const
{
	const int startX = static_cast<int>(lineSegment.from.x / tileSize);
	const int startY = static_cast<int>(lineSegment.from.y / tileSize);
	const int endX = static_cast<int>(lineSegment.to.x / tileSize);
	const int endY = static_cast<int>(lineSegment.to.y / tileSize);

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			const int index = GetIndex(x, y);
			if (mMap[index] == 6)
			{
				return true;
			}
		}
	}

	return false;
}

bool TileMap::IsCollidingWithDestination(const X::Math::LineSegment& lineSegment) const
{
	const int startX = static_cast<int>(lineSegment.from.x / tileSize);
	const int startY = static_cast<int>(lineSegment.from.y / tileSize);
	const int endX = static_cast<int>(lineSegment.to.x / tileSize);
	const int endY = static_cast<int>(lineSegment.to.y / tileSize);

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			const int index = GetIndex(x, y);
			if (mMap[index] == 7)
			{
				mMap[index] = 6;
				return true;
			}
		}
	}

	return false;
}


X::Math::Rect TileMap::GetBound() const
{
	return {
		0.0f,					// left
		0.0f,					// top
		mColumns * tileSize,	// right
		mRows * tileSize		// bottom
	};
}

void TileMap::LoadMap(const std::filesystem::path& fileName)
{
	if (mMap)
	{
		mMap.reset();
	}

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	fscanf_s(file, "Columns: %d\n", &mColumns);
	fscanf_s(file, "Rows: %d\n", &mRows);

	mMap = std::make_unique<int[]>(mColumns * mRows);

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = GetIndex(x, y);
			mMap[index] = fgetc(file) - '0';
		}

		fgetc(file);
	}

	fclose(file);
}

void TileMap::LoadTexture(const std::filesystem::path& fileName)
{
	mTiles.clear();

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	int count = 0;
	fscanf_s(file, "Count: %d\n", &count);

	for (int i = 0; i < count; ++i)
	{
		char buffer[256];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));

		mTiles.push_back(X::LoadTexture(buffer));
	}

	fclose(file);
}

int TileMap::GetIndex(int column, int row) const
{
	// Example:
	// if looking for column 1 and row 3 with 10 total columns
	// index = 1 + (3 * 10);
	// index = 31;

	return column + (row * mColumns);
}
