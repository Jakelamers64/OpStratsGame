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
		OnePrime = 0,
		TwoPrime = 1,
		ThreePrime = 2,
		OneTwoPrime = 3,
		TwoThreePrime = 4,
		ThreeOnePrime = 5,
		All = 6,
		Nothing = 7,
	};

	enum class Contents
	{
		Stone = 0,
		Empty = 1
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
	RectI GetPrimeRect(const Displayed display, const Contents content) const;
private:
	bool isDrawn = false;
	Color chroma = { 255,0,255 };
	Contents content;
	Displayed display = Displayed::OnePrime;
};