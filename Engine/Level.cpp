#include "Level.h"
#include <algorithm>
#include <assert.h>

Level::Level(Graphics & gfx, const int levelEvel_in)
	:
	gfx(gfx),
	levelEvel(levelEvel_in)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (levelEvel_in == 0)
			{
				blocks.emplace_back(Block::Contents::Stone,Block::Displayed::TwoThreePrime);
			}
			if (levelEvel_in == 1)
			{
				blocks.emplace_back(Block::Contents::Stone,Block::Displayed::all);
			}
		}
	}
}

void Level::Draw(const RectI& rectToDraw, File toDraw,const int drawHeight)
{
	assert(rectToDraw.left >= 0);
	assert(rectToDraw.top >= 0);
	assert(rectToDraw.right < width);
	assert(rectToDraw.bottom < height);

	for (Vei2 gridPos = { rectToDraw.left ,rectToDraw.top }; gridPos.y <= rectToDraw.bottom; ++gridPos.y)
	{
		for (gridPos.x = rectToDraw.left; gridPos.x <= rectToDraw.right; ++gridPos.x)
		{
			BlockAt({ gridPos.x,gridPos.y }).Draw(gfx, toDraw.GetFile(), GridToIso(gridPos), drawHeight);
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

int Level::GetWidth() const
{
	return width;
}

int Level::GetHeight() const
{
	return height;
}

Vei2 Level::GridToIso(const Vei2 gridpos)
{
	assert(gridpos.x >= 0);
	assert(gridpos.y >= 0);
	assert(gridpos.x < width);
	assert(gridpos.y < height);

	//calc iso shift from center
	return Vei2(
		gfx.GetCenter().x + ((gridpos.x - gridpos.y) * BlockAt(gridpos).GetWidth() / 2),
		gfx.GetCenter().y + ((gridpos.x + gridpos.y) * BlockAt(gridpos).GetWidth() / 4)
	);
}
