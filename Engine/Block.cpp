#include "Block.h"

Block::Block(const RectI sourceLoc_in)
	:
	sourceLoc(sourceLoc_in)
{
}

void Block::Draw(Graphics & gfx, Surface & surface, const Vei2& loc_in)
{
	//shift sprite so the middle is the seed loc for drawing instead of top left corner
	Vei2 loc = { loc_in.x - GetWidth() / 2,loc_in.y - GetHeight() / 2 };

	gfx.DrawSprite(loc.x,loc.y, sourceLoc, gfx.GetScreenRect(), surface, chroma);

	isDrawn = true;
}

int Block::GetWidth() const
{
	return sourceLoc.right - sourceLoc.left;
}

int Block::GetHeight() const
{
	return sourceLoc.bottom - sourceLoc.top;
}

Block::Contents Block::GetContent() const
{
	return content;
}

Block::Displayed Block::GetDisplay() const
{
	return display;
}

bool Block::GetIsDrawn() const
{
	return isDrawn;
}

void Block::SetContent(Contents val)
{
	content = val;
}

void Block::SetDisplayed(Displayed val)
{
	display = val;
}

void Block::SetIsDrawn(const bool val)
{
	isDrawn = val;
}
