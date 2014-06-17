#include "lantern.h"

#include <gfx/color.h>

Lantern::Lantern() :
	Furniture("Lantern")
{
	col = Color::get(-1, 0, 111, 555);
	sprite = 5;
	xr = 3;
	yr = 2;
}

int Lantern::getLightRadius()
{
	return 8;
}
