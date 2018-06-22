#pragma once
#include "RectI.h"
#include "Graphics.h"
#include "Surface.h"
#include "Vei2.h"

class Block
{
public:
	enum class Displayed
	{
		Nothing = 0,
		OnePrime = 1,
		TwoPrime = 2,
		ThreePrime = 3,
		OneTwoPrime = 4,
		TwoThreePrime = 5,
		ThreeOnePrime = 6,
		All = 7
	};

	enum class Contents
	{
		Empty = 0,
		Grass = 1,
		Stone = 2
	};

	Block(const Contents contents_in);
	void Draw(Graphics& gfx,Surface& surface, const Vei2& loc);
	int GetWidth() const;
	int GetHeight() const;
	Contents GetContent() const;
	Displayed GetDisplay() const;
	bool GetIsDrawn() const;
	void SetContent(Contents val);
	void SetDisplayed(Displayed val);
	void SetIsDrawn(const bool val);
private:
	bool isDrawn = false;
	//were the sprite is in the bmp file
	RectI stone = { 0,64,128,192 };
	RectI stone2 = { 256,320,896,960 };
	Color chroma = { 255,0,255 };
	Contents content;
	Displayed display = Displayed::All;
};