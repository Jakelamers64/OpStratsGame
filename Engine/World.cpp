#include "World.h"
#include <assert.h>
#include <algorithm>

World::World(Graphics& gfx,const int elevation_in)
	:
	elevation(elevation_in)
{
	for (int z = 0; z < elevation; ++z)
	{
		Layers.emplace_back(Level(gfx,z));
	}
	CalcPrime({ 3,3 }, 1);
}

void World::Draw(Graphics & gfx, const File toDraw)
{
	Layers[curEvel].Draw({ 0,9,0,9 },toDraw,0);
	Layers[curEvel + 1].Draw({ 0,9,0,9 }, toDraw,1);
}

void World::CalcPrime(const Vei2 pos, const int evel)
{
	assert(pos.x >= 0);
	assert(pos.x < Layers[evel].GetWidth());
	assert(pos.y >= 0);
	assert(pos.y < Layers[evel].GetHeight());
	assert(evel >= 0);
	assert(evel < elevation);

	CalcPrimeRecur(pos, evel);
	CalcPrimeReset(pos, evel);
}

Block & World::BlockAt(const Vei2 pos, int evel)
{
	return Layers[evel].BlockAt(pos);
}

void World::CheckNeighborsSetPrime(const Vei2 pos, const int evel)
{
	assert(pos.x >= 0);
	assert(pos.x < Layers[evel].GetWidth());
	assert(pos.y >= 0);
	assert(pos.y < Layers[evel].GetHeight());
	assert(evel >= 0);
	assert(evel < elevation);

	if (Layers[evel].BlockAt(pos).GetContent() != Block::Contents::Empty)
	{
		if (evel + 1 < elevation)
		{
			//check the one above to the left to the right and then calc display for bottom stack
			if (Layers[evel + 1].BlockAt(pos).GetContent() != Block::Contents::Empty)
			{
				//take into account the edge blocks on the bottom and right
				if (pos.x + 1 < Layers[evel].GetWidth() &&
					pos.y + 1 < Layers[evel].GetHeight())
				{
					//check to see if nothing should be displayed
					if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::Nothing);
					}
					//if the block to the right is empty
					else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoPrime);
					}
					//if the block down is empty
					else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreePrime);
					}
					//if both the block to the right and down are empty
					else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
					}
				}
				// if the both below and to the right of the block are out of bounds
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
				}
				//if the right is out of bounds and below is empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
				}
				//if the right is out of bounds and below is not empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoPrime);
				}
				//if the right is empty and below out of bounds
				else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
				}
				//if the right is not empty and below is out of bounds 
				else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreePrime);
				}
			}
			//if the block above is empty
			else if (Layers[evel + 1].BlockAt(pos).GetContent() == Block::Contents::Empty)
			{
				//take into account the edge blocks on the bottom and right
				if (pos.x + 1 < Layers[evel].GetWidth() &&
					pos.y + 1 < Layers[evel].GetHeight())
				{
					//if the blocks left and right are both not empty
					if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OnePrime);
					}
					//if the block to the right is empty
					else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
					}
					//if the block down is empty
					else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
					}
					//if both the block to the right and down are empty
					else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
					}
				}
				// if the both below and to the right of the block are out of bounds
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
				//if the right is out of bounds and below is empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
				//if the right is out of bounds and below is not empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
				}
				//if the right is empty and below out of bounds
				else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
				//if the right is not empty and below is out of bounds 
				else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
				}
			}
		}
		if (evel + 1 >= elevation)
		{
			//take into account the edge blocks on the bottom and right
			if (pos.x + 1 < Layers[evel].GetWidth() &&
				pos.y + 1 < Layers[evel].GetHeight())
			{
				//if the blocks left and right are both not empty
				if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OnePrime);
				}
				//if the block to the right is empty
				else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
				}
				//if the block down is empty
				else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
				}
				//if both the block to the right and down are empty
				else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
			}
			// if the both below and to the right of the block are out of bounds
			else if (pos.x + 1 >= Layers[evel].GetWidth() &&
				pos.y + 1 >= Layers[evel].GetHeight())
			{
				Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
			}
			//if the right is out of bounds and below is empty
			else if (pos.x + 1 >= Layers[evel].GetWidth() &&
				Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
			{
				Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
			}
			//if the right is out of bounds and below is not empty
			else if (pos.x + 1 >= Layers[evel].GetWidth() &&
				Layers[evel].BlockAt({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
			{
				Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
			}
			//if the right is empty and below out of bounds
			else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
				pos.y + 1 >= Layers[evel].GetHeight())
			{
				Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
			}
			//if the right is not empty and below is out of bounds 
			else if (Layers[evel].BlockAt({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
				pos.y + 1 >= Layers[evel].GetHeight())
			{
				Layers[evel].BlockAt({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
			}
		}
	}
	else
	{
		Layers[evel].BlockAt(pos).SetDisplayed(Block::Displayed::Nothing);
	}
}

void World::CalcPrimeRecur(const Vei2 gridpos_in, const int evel)
{
	const int xStart = std::max(0, gridpos_in.x - 1);
	const int yStart = std::max(0, gridpos_in.y - 1);
	const int zStart = std::max(0, evel - 1);
	const int xEnd = std::min(Layers[evel].GetWidth() - 1, gridpos_in.x + 1);
	const int yEnd = std::min(Layers[evel].GetHeight() - 1, gridpos_in.y + 1);
	const int zEnd = std::min(elevation - 1, evel + 1);

	if (BlockAt({ gridpos_in.x,gridpos_in.y }, evel).GetHasCalcNeighbors() == false)
	{
		CheckNeighborsSetPrime(gridpos_in,evel);

		for (int z = zStart; z <= zEnd; ++z)
		{
			for (Vei2 gridpos = { xStart,yStart }; gridpos.y <= yEnd; ++gridpos.y)
			{
				for (gridpos.x = xStart; gridpos.x <= xEnd; ++gridpos.x)
				{
					if (gridpos_in != gridpos)
					{
						CalcPrimeRecur(gridpos, z);
					}
				}
			}
		}
	}
}

void World::CalcPrimeReset(const Vei2 gridpos_in, const int evel)
{
	const int xStart = std::max(0, gridpos_in.x - 1);
	const int yStart = std::max(0, gridpos_in.y - 1);
	const int zStart = std::max(0, evel - 1);
	const int xEnd = std::min(Layers[evel].GetWidth() - 1, gridpos_in.x + 1);
	const int yEnd = std::min(Layers[evel].GetHeight() - 1, gridpos_in.y + 1);
	const int zEnd = std::min(elevation - 1, evel + 1);

	if (BlockAt({ gridpos_in.x,gridpos_in.y }, evel).GetHasCalcNeighbors() == true)
	{
		BlockAt({ gridpos_in.x,gridpos_in.y }, evel).SetHasCalcNeighbors(false);

		for (int z = zStart; z <= zEnd; ++z)
		{
			for (Vei2 gridpos = { xStart,yStart }; gridpos.y <= yEnd; ++gridpos.y)
			{
				for (gridpos.x = xStart; gridpos.x <= xEnd; ++gridpos.x)
				{
					if (gridpos_in != gridpos)
					{
						CalcPrimeRecur(gridpos, z);
					}
				}
			}
		}
	}
}
