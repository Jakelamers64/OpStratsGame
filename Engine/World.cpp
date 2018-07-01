#include "World.h"

World::World(Graphics& gfx,const int elevation_in)
	:
	elevation(elevation_in)
{
	for (int z = 0; z < elevation; ++z)
	{
		Layers.emplace_back(Level(gfx,z));
	}
}

void World::Draw(Graphics & gfx, const File toDraw)
{
	Layers[curEvel].Draw({ 1,1 },toDraw,0);
	Layers[curEvel + 1].Draw({ 1,1 }, toDraw,1);
}

Block & World::BlockAt(const Vei2 pos, int evel)
{
	return Layers[evel].BlockAt(pos);
}
