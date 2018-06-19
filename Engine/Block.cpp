#include "Block.h"

Block::Block(const RectI sourceLoc_in)
	:
	sourceLoc(sourceLoc_in)
{
}

void Block::Draw(Graphics & gfx, Surface & surface, const Vei2& loc_in)
{

	gfx.DrawSprite(loc_in.x,loc_in.y, sourceLoc, gfx.GetScreenRect(), surface, chroma);
}

int Block::GetWidth() const
{
	return sourceLoc.right - sourceLoc.left;
}

int Block::GetHeight() const
{
	return sourceLoc.bottom - sourceLoc.top;
}
