#pragma once
#include "RectI.h"
#include "Graphics.h"
#include "Surface.h"
#include "Vei2.h"

class Block
{
public:
	Block(const RectI sourceLoc_in);
	void Draw(Graphics& gfx,Surface& surface, const Vei2& loc);
	int GetWidth() const;
	int GetHeight() const;
private:
	//were the sprite is in the bmp file
	RectI sourceLoc;
	Color chroma = { 255,0,255 };
};