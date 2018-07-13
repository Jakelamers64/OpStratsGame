#pragma once
#include "Level.h"
#include "File.h"
#include <vector>

class World
{
public:
	World(Graphics& gfx,const int elevation);
	void Draw(const RectI& rectToDraw, Graphics & gfx, const File toDraw);
	void CalcPrime();
	Block& BlockAtGridPos(const Vei2 pos, const int evel);
	Vei2 BlockAtScreenPos(const Vei2 screenPos);
private:
	void CheckNeighborsSetPrime(const Vei2 pos, const int evel);
private:
	//z height in the 3d 
	int elevation;
	int curEvel = 0;
	//ogres are like my game they have layers
	std::vector<Level> Layers;
	//origin right now
	Vei2 origin = { 400,300 };
};