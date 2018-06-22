#pragma once
#include "Level.h"
#include <vector>

class World
{
public:
	World(Graphics& gfx);
private:
	//z height in the 3d 
	int height;
	//ogres are like my game they have layers
	std::vector<Level> Layers;
};