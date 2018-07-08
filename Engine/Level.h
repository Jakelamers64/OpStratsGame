#pragma once
#include "Surface.h"
#include "Graphics.h"
#include "Block.h"
#include <vector>
#include "Vec2.h"
#include "Vei2.h"
#include "File.h"

class Level
{
public:
	Level(Graphics& gfx,const int levelEvel_in);
	void Draw(const RectI& rectToDraw, File toDraw, const int drawHeight);
	Block& BlockAtGridPos(const Vei2 gridpos);
	Block& BlockAtScreenPos(const Vei2 screenPos);
	int GetWidth() const;
	int GetHeight() const;
private:
	Vei2 GridToIso(const Vei2 gridpos);
	Vei2 IsoToGrid(const Vei2 screenPos);
private:
	static constexpr int width = 10;
	static constexpr int height = 10;
	int levelEvel;
	std::vector<Block> blocks;
	Graphics& gfx;
};