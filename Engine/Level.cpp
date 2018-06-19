#include "Level.h"

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

void Level::Draw()
{
	for (Vec2 pos = { 0,0 }; pos.y < height; ++pos.y)
	{
		for (pos.x = 0; pos.x < width; ++pos.x)
		{
			int curBlockN = int(pos.y * width + pos.x);
			//convert 2d grid to 2.5d isometric projection
			Vec2 screenPos = { center.x - (pos.x + pos.y) * blocks[curBlockN].GetWidth() / 2,
				center.y + (pos.x * 0.5f - pos.y * 0.5f) * blocks[curBlockN].GetHeight() / 2 };

			blocks[curBlockN].Draw(gfx, blocksBit, { int(screenPos.x),int(screenPos.y) });
		}
	}
}
