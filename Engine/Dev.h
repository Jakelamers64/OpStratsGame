#pragma once
#include "Font.h"
#include "Graphics.h"
#include <string.h>

class Dev
{
public:
	void DrawStats(const Vei2 pos, const Vei2 mousePos, const float dt, Graphics& gfx);
private:
	Font font = "Fixedsys16x28.bmp";
};