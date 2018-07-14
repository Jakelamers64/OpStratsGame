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
				blocks.emplace_back(Block::Contents::Stone, Block::Displayed::TwoThreePrime,Vei2(x,y));
			}
			if (levelEvel_in == 1)
			{
				blocks.emplace_back(Block::Contents::Stone,Block::Displayed::all,Vei2(x, y));
			}
		}
	}
	/* 
	test code that allows you to view layer below
	if (levelEvel_in == 1)
	{
		for (int y = 1; y < height - 1; ++y)
		{
			for (int x = 1; x < width - 1; ++x)
			{
				BlockAtGridPos({ x,y }).SetContent(Block::Contents::Empty);
				BlockAtGridPos({ x,y }).SetDisplayed(Block::Displayed::Nothing);
			}
		}
		BlockAtGridPos({ 5,5 }).SetContent(Block::Contents::Stone);
		BlockAtGridPos({ 5,5 }).SetDisplayed(Block::Displayed::all);
	}
	*/
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
			BlockAtGridPos({ gridPos.x,gridPos.y }).Draw(gfx, toDraw.GetFile(), GridToIso(gridPos), drawHeight);
		}
	}
}

Block& Level::BlockAtGridPos(const Vei2 gridpos)
{
	assert(gridpos.x >= 0);
	assert(gridpos.y >= 0);
	assert(gridpos.x < width);
	assert(gridpos.y < height);

	return blocks[gridpos.y * width + gridpos.x];
}

Vei2 Level::BlockAtScreenPos(const Vei2 screenPos, const Vei2 origin)
{
	return IsoToGrid(screenPos,origin);
}

bool Level::IsInBounds(const Vei2 gridPos) const
{
	return gridPos.x >= 0 &&
		gridPos.y >= 0 &&
		gridPos.x < width &&
		gridPos.y < height;
}

int Level::GetWidth() const
{
	return width;
}

int Level::GetHeight() const
{
	return height;
}

Vei2 Level::GridToIso(const Vei2 gridpos, const Vei2 origin)
{
	assert(gridpos.x >= 0);
	assert(gridpos.y >= 0);
	assert(gridpos.x < width);
	assert(gridpos.y < height);

	//calc iso shift from center
	return Vei2(
		origin.x + ((gridpos.x - gridpos.y) * BlockAtGridPos(gridpos).GetWidth() / 2),
		origin.y + ((gridpos.x + gridpos.y) * BlockAtGridPos(gridpos).GetWidth() / 4)
	);
}

Vei2 Level::IsoToGrid(const Vei2 screenPos, const Vei2 origin)
{
	//adjust for origin
	Vei2 originShift = Vei2(
		//x start
		((origin.x / (BlockAtGridPos({ 0,0 }).GetWidth() / 2)) +
		(origin.y / (BlockAtGridPos({ 0,0 }).GetHeight() / 4))) / 2,
		//x end
		//y start
		((origin.y / (BlockAtGridPos({ 0,0 }).GetHeight() / 4)) -
		(origin.x / (BlockAtGridPos({ 0,0 }).GetWidth() / 2))) / 2
		//y end
	);
	//url for where I got the base for this code
	//http://clintbellanger.net/articles/isometric_math/
	return Vei2(
		//x start
		(
		(screenPos.x / (BlockAtGridPos({0,0}).GetWidth() / 2)) + 
			(screenPos.y / (BlockAtGridPos({ 0,0 }).GetHeight() / 4))
			) / 2 - originShift.x,
		//x end
		//y start
		(
		((screenPos.y + 8) / (BlockAtGridPos({ 0,0 }).GetHeight() / 4)) - 
			(screenPos.x / (BlockAtGridPos({ 0,0 }).GetWidth() / 2))
			) / 2 - originShift.y
		//y end
	);
}
