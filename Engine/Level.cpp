#include "Level.h"
#include <algorithm>

Level::Level(Graphics & gfx)
	:
	gfx(gfx)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			blocks.emplace_back(Block({ 0,64,704,768 }));
			if (y < 1)
			{
				BlockAt({ x,y }).SetDisplayed(Block::Displayed::Nothing);
			}
			if (y > height - 1)
			{
				BlockAt({ x,y }).SetDisplayed(Block::Displayed::Nothing);
			}
			if (x < 1)
			{
				BlockAt({ x,y }).SetDisplayed(Block::Displayed::Nothing);
			}
			if (x > width - 1)
			{
				BlockAt({ x,y }).SetDisplayed(Block::Displayed::Nothing);
			}
		}
	}
}

void Level::Draw(const Vei2 gridpos_in)
{
	const int xStart = std::max(0, gridpos_in.x - 1);
	const int yStart = std::max(0, gridpos_in.y - 1);
	const int xEnd = std::min(width - 1, gridpos_in.x + 1);
	const int yEnd = std::min(height - 1, gridpos_in.y + 1);

	if (BlockAt(gridpos_in).GetDisplay() != Block::Displayed::Nothing)
	{
		if (BlockAt(gridpos_in).GetIsDrawn() == false)
		{
			for (Vei2 gridpos = { xStart,yStart }; gridpos.y <= yEnd; ++gridpos.y)
			{
				for (gridpos.x = xStart; gridpos.x <= xEnd; ++gridpos.x)
				{
					if (gridpos_in != gridpos)
					{
						Draw(gridpos);
						BlockAt({ gridpos_in.x,gridpos_in.y }).Draw(gfx, blocksBit, GridToIso(gridpos_in));
					}
				}
			}
		}
	}
}

void Level::DrawReset(const Vei2 gridpos_in)
{
	const int xStart = std::max(0, gridpos_in.x - 1);
	const int yStart = std::max(0, gridpos_in.y - 1);
	const int xEnd = std::min(width - 1, gridpos_in.x + 1);
	const int yEnd = std::min(height - 1, gridpos_in.y + 1);

	if (BlockAt(gridpos_in).GetIsDrawn() == true)
	{
		for (Vei2 gridpos = { xStart,yStart }; gridpos.y <= yEnd; ++gridpos.y)
		{
			for (gridpos.x = xStart; gridpos.x <= xEnd; ++gridpos.x)
			{
				if (gridpos_in != gridpos)
				{
					DrawReset(gridpos);
					BlockAt({ gridpos_in.x,gridpos_in.y }).SetIsDrawn(false);
				}
			}
		}
	}
}

Block& Level::BlockAt(const Vei2 gridpos)
{
	return blocks[gridpos.y * width + gridpos.x];
}

Vei2 Level::GridToIso(const Vei2 gridpos)
{
	return Vei2(
		gfx.GetCenter().x + (gridpos.x - gridpos.y) * BlockAt(gridpos).GetWidth() / 2,
		gfx.GetCenter().y + (gridpos.x + gridpos.y) * BlockAt(gridpos).GetWidth() / 4
	);
}


/*
//converts 2d to 2.5d should probably be moved
for (Vec2 pos = { 0,0 }; pos.y < height; ++pos.y)
{
for (pos.x = 0; pos.x < width; ++pos.x)
{
int curBlockN = int(pos.y * width + pos.x);
if (blocks[curBlockN].GetContent() != Block::Contents::Empty)
{
//convert 2d grid to 2.5d isometric projection
Vec2 screenPos = {
gfx.GetCenter().x + (pos.x - pos.y) * blocks[curBlockN].GetWidth() / 2,
gfx.GetCenter().y + (pos.x + pos.y) * blocks[curBlockN].GetWidth() / 4
};
blocks[curBlockN].Draw(gfx, blocksBit, { int(screenPos.x),int(screenPos.y) });
}
}
}
*/