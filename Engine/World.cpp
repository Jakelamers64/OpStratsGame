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
	CalcPrime();
}

void World::Draw(const RectI& rectToDraw, Graphics & gfx, const File toDraw)
{
	//calls draw on the level you are curently on and the one above it 
	Layers[curEvel].Draw(rectToDraw,toDraw,0);
	Layers[curEvel + 1].Draw(rectToDraw, toDraw,1);
}

void World::CalcPrime()
{
	for (int z = 0; z < elevation; ++z)
	{
		for (int y = 0; y < Layers[z].GetHeight(); ++y)
		{
			for (int x = 0; x < Layers[z].GetWidth(); ++x)
			{
				CheckNeighborsSetPrime({ x,y }, z);
			}
		}
	}
}

Vei2 World::BlockAtScreenPos(const Vei2 screenPos)
{
	//orgin for curlvl + 1
	Vei2 originPlus1 = { origin.x,origin.y - 32 };

	Vei2 gridPos = Layers[curEvel + 1].BlockAtScreenPos(screenPos, originPlus1);

	if (Layers[curEvel + 1].IsInBounds(gridPos))
	{
		if (Layers[curEvel + 1].BlockAtGridPos(gridPos).GetContent() == Block::Contents::Empty)
		{
			return Layers[curEvel].BlockAtScreenPos(screenPos, origin);
		}
		return gridPos;
	}
	else
	{
		return { -69,-69 };
	}
}

Block& World::BlockAtGridPos(const Vei2 pos, int evel)
{
	return Layers[evel].BlockAtGridPos(pos);
}

void World::CheckNeighborsSetPrime(const Vei2 pos, const int evel)
{
	assert(pos.x >= 0);
	assert(pos.x < Layers[evel].GetWidth());
	assert(pos.y >= 0);
	assert(pos.y < Layers[evel].GetHeight());
	assert(evel >= 0);
	assert(evel < elevation);

	if (Layers[evel].BlockAtGridPos(pos).GetContent() != Block::Contents::Empty)
	{
		if (evel + 1 < elevation)
		{
			//check the one above to the left to the right and then calc display for bottom stack
			if (Layers[evel + 1].BlockAtGridPos(pos).GetContent() != Block::Contents::Empty)
			{
				//take into account the edge blocks on the bottom and right
				if (pos.x + 1 < Layers[evel].GetWidth() &&
					pos.y + 1 < Layers[evel].GetHeight())
				{
					//check to see if nothing should be displayed
					if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::Nothing);
					}
					//if the block to the right is empty
					else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoPrime);
					}
					//if the block down is empty
					else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreePrime);
					}
					//if both the block to the right and down are empty
					else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
					}
				}
				// if the both below and to the right of the block are out of bounds
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
				}
				//if the right is out of bounds and below is empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
				}
				//if the right is out of bounds and below is not empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoPrime);
				}
				//if the right is empty and below out of bounds
				else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::TwoThreePrime);
				}
				//if the right is not empty and below is out of bounds 
				else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreePrime);
				}
			}
			//if the block above is empty
			else if (Layers[evel + 1].BlockAtGridPos(pos).GetContent() == Block::Contents::Empty)
			{
				//take into account the edge blocks on the bottom and right
				if (pos.x + 1 < Layers[evel].GetWidth() &&
					pos.y + 1 < Layers[evel].GetHeight())
				{
					//if the blocks left and right are both not empty
					if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OnePrime);
					}
					//if the block to the right is empty
					else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
					}
					//if the block down is empty
					else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
					}
					//if both the block to the right and down are empty
					else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
						Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
					{
						Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
					}
				}
				// if the both below and to the right of the block are out of bounds
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
				//if the right is out of bounds and below is empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
				//if the right is out of bounds and below is not empty
				else if (pos.x + 1 >= Layers[evel].GetWidth() &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
				}
				//if the right is empty and below out of bounds
				else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
				//if the right is not empty and below is out of bounds 
				else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					pos.y + 1 >= Layers[evel].GetHeight())
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
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
				if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OnePrime);
				}
				//if the block to the right is empty
				else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
				}
				//if the block down is empty
				else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
				}
				//if both the block to the right and down are empty
				else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
					Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
				{
					Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
				}
			}
			// if the both below and to the right of the block are out of bounds
			else if (pos.x + 1 >= Layers[evel].GetWidth() &&
				pos.y + 1 >= Layers[evel].GetHeight())
			{
				Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
			}
			//if the right is out of bounds and below is empty
			else if (pos.x + 1 >= Layers[evel].GetWidth() &&
				Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() == Block::Contents::Empty)
			{
				Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
			}
			//if the right is out of bounds and below is not empty
			else if (pos.x + 1 >= Layers[evel].GetWidth() &&
				Layers[evel].BlockAtGridPos({ pos.x,pos.y + 1 }).GetContent() != Block::Contents::Empty)
			{
				Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::OneTwoPrime);
			}
			//if the right is empty and below out of bounds
			else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() == Block::Contents::Empty &&
				pos.y + 1 >= Layers[evel].GetHeight())
			{
				Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::all);
			}
			//if the right is not empty and below is out of bounds 
			else if (Layers[evel].BlockAtGridPos({ pos.x + 1,pos.y }).GetContent() != Block::Contents::Empty &&
				pos.y + 1 >= Layers[evel].GetHeight())
			{
				Layers[evel].BlockAtGridPos({ pos.x,pos.y }).SetDisplayed(Block::Displayed::ThreeOnePrime);
			}
		}
	}
	else
	{
		Layers[evel].BlockAtGridPos(pos).SetDisplayed(Block::Displayed::Nothing);
	}
}