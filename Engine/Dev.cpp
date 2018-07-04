#include "Dev.h"

void Dev::DrawStats(const Vei2 pos, const Vei2 mousePos, const float dt, Graphics& gfx)
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
}
