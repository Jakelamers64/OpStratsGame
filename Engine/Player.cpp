#include "Player.h"
#include <cmath>

Vei2 Player::ConvertIsoToGrid(const Vei2 screenPos, Graphics& gfx)
{
	//http://clintbellanger.net/articles/isometric_math/
	return {(screenPos.x / 32 + (screenPos.y + 8) / 16) / 2 - 15,((screenPos.y + 8) / 16 - (screenPos.x / 32)) / 2 - 3 };
}