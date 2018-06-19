#pragma once
#include "Surface.h"
#include "Graphics.h"
#include "Block.h"
#include <vector>
#include "Vec2.h"
#include "Vei2.h"


class Level
{
public:
	Level(Graphics& gfx);
	void Draw();
private:
	static constexpr int width = 10;
	static constexpr int height = 10;
	std::vector<Block> blocks;
	Surface& blocksBit = Surface("terrainTiles.bmp");
	Graphics& gfx;
	Vec2 center = Vec2( gfx.ScreenWidth / 2.0f ,gfx.ScreenHeight / 2.0f );
};