#include "Level.h"
#include <algorithm>
#include <assert.h>

Level::Level(Graphics & gfx)
	:
	gfx(gfx)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			blocks.emplace_back(Block({ 0,64,704,768 }));
		}
	}
}

void Level::Draw(const Vei2 gridpos_in)
{
	assert(gridpos_in.x >= 0);
	assert(gridpos_in.y >= 0);
	assert(gridpos_in.x < width);
	assert(gridpos_in.y < height);

	DrawRecur(gridpos_in);
	DrawReset(gridpos_in);
}

void Level::DrawReset(const Vei2 gridpos_in)
{
	const int xStart = std::max(0, gridpos_in.x - 1);
	const int yStart = std::max(0, gridpos_in.y - 1);
	const int xEnd = std::min(width - 1, gridpos_in.x + 1);
	const int yEnd = std::min(height - 1, gridpos_in.y + 1);

	BlockAt({ gridpos_in.x,gridpos_in.y }).SetIsDrawn(false);
	for (Vei2 gridpos = { xStart,yStart }; gridpos.y <= yEnd; ++gridpos.y)
	{
		for (gridpos.x = xStart; gridpos.x <= xEnd; ++gridpos.x)
		{
			if (gridpos_in != gridpos)
			{
				if (BlockAt(gridpos).GetIsDrawn() == true)
				{
					DrawReset(gridpos);
				}
			}
		}
	}
}

void Level::DrawRecur(const Vei2 gridpos_in)
{
	//calc the box that can be called around the pos
	const int xStart = std::max(0, gridpos_in.x - 1);
	const int yStart = std::max(0, gridpos_in.y - 1);
	const int xEnd = std::min(width - 1, gridpos_in.x + 1);
	const int yEnd = std::min(height - 1, gridpos_in.y + 1);

	//draws sprite then sets isdrawn = to true so we can get out of the loop
	BlockAt({ gridpos_in.x,gridpos_in.y }).Draw(gfx, blocksBit, GridToIso(gridpos_in));

	for (Vei2 gridpos = { xStart,yStart }; gridpos.y <= yEnd; ++gridpos.y)
	{
		for (gridpos.x = xStart; gridpos.x <= xEnd; ++gridpos.x)
		{
			if (gridpos_in != gridpos)
			{
				if (BlockAt(gridpos).GetIsDrawn() == false)
				{
					DrawRecur(gridpos);
				}
			}
		}
	}
}

Block& Level::BlockAt(const Vei2 gridpos)
{
	assert(gridpos.x >= 0);
	assert(gridpos.y >= 0);
	assert(gridpos.x < width);
	assert(gridpos.y < height);
	return blocks[gridpos.y * width + gridpos.x];
}

Vei2 Level::GridToIso(const Vei2 gridpos)
{
	assert(gridpos.x >= 0);
	assert(gridpos.y >= 0);
	assert(gridpos.x < width);
	assert(gridpos.y < height);

	//calc iso shift from center
	return Vei2(
		gfx.GetCenter().x + (gridpos.x - gridpos.y) * BlockAt(gridpos).GetWidth() / 2,
		gfx.GetCenter().y + (gridpos.x + gridpos.y) * BlockAt(gridpos).GetWidth() / 4
	);
}
