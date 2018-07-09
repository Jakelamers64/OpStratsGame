#include "Block.h"
#include <assert.h>

Block::Block(const Contents contents_in, const Displayed display_in, Vei2 gridPos)
	:
	content(contents_in),
	display(display_in),
	pos(gridPos)
{
}

void Block::Draw(Graphics& gfx, Surface& surface, const Vei2& loc_in, const int drawHeight)
{
	//shift sprite so the middle is the seed loc for drawing instead of top left corner
	Vei2 loc = { loc_in.x - GetWidth() / 2,loc_in.y - GetHeight() / 4 };

	//see what should be drawn
	if (Block::Contents::Empty != content && Block::Displayed::Nothing != display)
	{
		if (Block::Contents::Stone == content)
		{
			gfx.DrawSprite(loc.x, loc.y - 32 * drawHeight, GetPrimeRect(display, content), gfx.GetScreenRect(), surface, chroma);
		}
	}
}

int Block::GetWidth() const
{
	return GetPrimeRect(display,content).right - GetPrimeRect(display, content).left;
}

int Block::GetHeight() const
{
	return GetPrimeRect(display, content).bottom - GetPrimeRect(display, content).top;
}

Block::Contents Block::GetContent() const
{
	return content;
}

Block::Displayed Block::GetDisplay() const
{
	return display;
}

bool Block::GetHasCalcNeighbors() const
{
	return hasCalcNeighbors;
}

Vei2 Block::GetPos() const
{
	return pos;
}

void Block::SetContent(Contents val)
{
	content = val;
}

void Block::SetDisplayed(Displayed val)
{
	display = val;
	hasCalcNeighbors = true;

}

void Block::SetHasCalcNeighbors(const bool val)
{
	hasCalcNeighbors = val;
}

RectI Block::GetPrimeRect(const Displayed display,const Contents content) const
{
	assert(int(display) >= 0);
	assert(int(display) < 8);
	assert(int(content) >= 0);
	assert(int(content) <= 1);
	//returns rect of the sprite based on primes
	return RectI( 64 * int(display),64 + 64 * int(display),64 * int(content),64 + 64 * int(content));
}
