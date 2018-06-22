#include "World.h"

World::World(Graphics& gfx)
{
	for (int z = 0; z < height; ++z)
	{
		Layers.emplace_back(Level(gfx));
	}
}
