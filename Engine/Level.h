#pragma once
#include "Surface.h"
#include "Graphics.h"
#include "Block.h"
#include <vector>
#include "Vec2.h"
#include "File.h"

class Level
{
public:
	Level(Graphics& gfx,const int levelEvel_in);
	void Draw(const RectI& rectToDraw, File toDraw, const int drawHeight);
	Block& BlockAtGridPos(const Vei2 gridpos);
	Vei2 BlockAtScreenPos(const Vei2 screenPos, const Vei2 origin);
	bool IsInBounds(const Vei2 gridPos) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	Vei2 GridToIso(const Vei2 screenPos, const Vei2 origin = {400,300});
	Vei2 IsoToGrid(const Vei2 screenPos, const Vei2 origin);
private:
	static constexpr int width = 10;
	static constexpr int height = 10;
	int levelEvel;
	std::vector<Block> blocks;
	Graphics& gfx;
};