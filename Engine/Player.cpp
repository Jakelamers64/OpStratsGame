#include "Player.h"
#include "SpriteEffect.h"

void Player::OnHover(World & world, const Vei2 & screenPos, Graphics& gfx) const
{
	//get block you are hovering on 
	Vei2 gridpos = world.IsoToGrid(screenPos, { world.GetOrigin().x,world.GetOrigin().y - world.GetBrickHeight() / 2 });
	//make sure the block is in the square put to screen
	if (gridpos.x >= 0 &&
		gridpos.y >= 0 &&
		gridpos.x < world.GetWidth() && 
		gridpos.y < world.GetLength())
	{
		//get the loc to draw to screen
		Vei2 pos = world.GridToIso({ gridpos.x,gridpos.y }, { world.GetOrigin().x,world.GetOrigin().y - world.GetBrickHeight() / 2 });
		//draw sprite to show which block will be selected
		gfx.DrawSprite(pos.x - world.GetBrickWidth() / 2, pos.y - world.GetBrickHeight() / 4, RectI(64*6,64*7,0,64), gfx.GetScreenRect(), cursor, SpriteEffect::Ghost(Colors::Magenta));
	}
}

Vei2 Player::OnClick(const Vei2 screenPos, World& world)
{
	return world.IsoToGrid(screenPos, { world.GetOrigin().x,world.GetOrigin().y - world.GetBrickHeight() / 2 });
}
