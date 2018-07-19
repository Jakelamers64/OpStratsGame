#pragma once
#include "Vec2.h"
#include "World.h"
#include "Graphics.h"
#include "Surface.h"
#include "Rect.h"

class Player
{
public:
	void OnHover(World& world, const Vei2& pos, Graphics& gfx) const;
	Vei2 OnClick(const Vei2 screenPos, World& world);
private:
	int curEvel = 1;
	Surface cursor = Surface("cursorComp.bmp");
	Vei2 selected; 
};