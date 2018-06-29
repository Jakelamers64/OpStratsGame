#pragma once
#include "Level.h"
#include "File.h"
#include <vector>

class World
{
public:
	World(Graphics& gfx,const int elevation);
	void Draw(Graphics& gfx,const File toDraw);
private:
	//z height in the 3d 
	int elevation;
	int curEvel = 0;
	//ogres are like my game they have layers
	std::vector<Level> Layers;
};