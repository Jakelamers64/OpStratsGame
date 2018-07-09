#include "Player.h"

Vei2 Player::OnClick(const Vei2 screenPos, World& world)
{
	return world.BlockAtScreenPos(screenPos);
}
