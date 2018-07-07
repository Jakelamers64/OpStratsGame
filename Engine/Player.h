#pragma once
#include "Vec2.h"
#include "Vei2.h"
#include "Block.h"
#include "Graphics.h"

class Player
{
public:
	Vei2 ConvertIsoToGrid(const Vei2 screenPos, Graphics& gfx);
private:
};