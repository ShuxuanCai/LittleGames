#pragma once

#include <XEngine.h>

class TileMap
{
public:
	// Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static TileMap& Get();

public:
	//Standard Object Function
	void Load(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName);
	void Unload();
	void Update(float deltaTime);
	void Render();

	bool IsCollidingWith(const X::Math::LineSegment& lineSegment) const;
	bool IsCollidingWithGrass(const X::Math::LineSegment& lineSegment) const;
	bool IsCollidingWithDestination(const X::Math::LineSegment& lineSegment) const;

	X::Math::Rect GetBound() const;

private:
	void LoadMap(const std::filesystem::path& fileName);
	void LoadTexture(const std::filesystem::path& fileName);

	int GetIndex(int column, int row) const;

	std::unique_ptr<int[]> mMap = nullptr;
	int mColumns = 0;
	int mRows = 0;

	std::vector<X::TextureId> mTiles;
};


