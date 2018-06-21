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
	void Draw(const Vei2 gridpos);
	void DrawReset(const Vei2 gridpos);
private:
	Block& BlockAt(const Vei2 gridpos);
	Vei2 GridToIso(const Vei2 gridpos);
private:
	static constexpr int width = 10;
	static constexpr int height = 5;
	std::vector<Block> blocks;
	Surface& blocksBit = Surface("terrainTiles.bmp");
	Graphics& gfx;
};