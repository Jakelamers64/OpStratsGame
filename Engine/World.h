#pragma once
#include "Level.h"
#include "File.h"
#include <vector>

class World
{
public:
	World(Graphics& gfx,const int elevation);
	void Draw(Graphics& gfx,const File toDraw);
	void CalcPrime(const Vei2 pos, const int evel);
private:
	Block& BlockAt(const Vei2 pos,const int evel);
	void CheckNeighborsSetPrime(const Vei2 pos, const int evel);
	void CalcPrimeRecur(const Vei2 pos,const int evel);
	void CalcPrimeReset(const Vei2 pos, const int evel);
private:
	//z height in the 3d 
	int elevation;
	int curEvel = 0;
	//ogres are like my game they have layers
	std::vector<Level> Layers;
};