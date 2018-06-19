#pragma once
#include "RectI.h"
#include "Graphics.h"
#include "Surface.h"
#include "Vei2.h"

class Block
{
public:
	Block(const RectI sourceLoc_in);

	enum class Contents
	{
		Empty = 0,
		Grass = 1
	};

	void Draw(Graphics& gfx,Surface& surface, const Vei2& loc);
	int GetWidth() const;
	int GetHeight() const;
	Contents GetContent() const;
	void SetContent(Contents val);
private:
	//were the sprite is in the bmp file
	RectI sourceLoc;
	Color chroma = { 255,0,255 };
	Contents content = Contents::Grass;
};