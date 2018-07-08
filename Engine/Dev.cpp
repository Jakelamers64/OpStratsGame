#include "Dev.h"

void Dev::DrawStats(const Vei2 pos, const Vei2 mousePos, const float dt, Graphics& gfx,World& world)
{
	//get the frame time to be output
	std::string frameTime = std::to_string(dt);
	//output frame time 
	font.DrawText(frameTime, pos, gfx);
	//convet mouse pos to string
	std::string mousePosX = std::to_string(mousePos.x);
	std::string mousePosY = std::to_string(mousePos.y);
	//out put pos
	font.DrawText(mousePosX, { pos.x,pos.y + font.GetGlyphHeight() }, gfx);
	font.DrawText(mousePosY, { pos.x,pos.y + font.GetGlyphHeight() * 2 }, gfx);
	//convert mousePos into gridpos then output
	Vei2 playerGridPos = player.OnClick(mousePos,world);
	//x
	std::string playerGridPosXStr = std::to_string(playerGridPos.x);
	font.DrawText(playerGridPosXStr, { pos.x,pos.y + font.GetGlyphHeight() * 3 }, gfx);
	//y
	std::string playerGridPosYStr = std::to_string(playerGridPos.y);
	font.DrawText(playerGridPosYStr, { pos.x,pos.y + font.GetGlyphHeight() * 4 }, gfx);
}
