#include "Block.h"

Block::Block(const Contents contents_in)
	:
	content(contents_in)
{
}

void Block::Draw(Graphics & gfx, Surface & surface, const Vei2& loc_in)
{
	//shift sprite so the middle is the seed loc for drawing instead of top left corner
	Vei2 loc = { loc_in.x - GetWidth() / 2,loc_in.y - GetHeight() / 2 };

	//see what should be drawn
	if (Block::Contents::Empty != content)
	{
		if (Block::Contents::Stone == content)
		{
			gfx.DrawSprite(loc.x, loc.y, stone2, gfx.GetScreenRect(), surface, chroma);
		}
	}
	else
	{
		gfx.DrawSprite(loc.x, loc.y, stone, gfx.GetScreenRect(), surface, chroma);
	}

	isDrawn = true;
}

int Block::GetWidth() const
{
	return stone.right - stone.left;
}

int Block::GetHeight() const
{
	return stone.bottom - stone.top;
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
