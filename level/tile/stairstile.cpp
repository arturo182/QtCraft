#include "stairstile.h"

#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

StairsTile::StairsTile(qint8 id, bool leadsUp) :
	Tile(id)
{
	this->leadsUp = leadsUp;
}

void StairsTile::render(Screen *screen, Level *level, int x, int y)
{
	int color = Color::get(level->dirtColor, 0, 333, 444);
	int xt = 0;
	if(leadsUp) {
		xt = 2;
	}

	screen->render(x * 16 + 0, y * 16 + 0, xt + 64, color, 0);
	screen->render(x * 16 + 8, y * 16 + 0, xt + 1 + 64, color, 0);
	screen->render(x * 16 + 0, y * 16 + 8, xt + 96, color, 0);
	screen->render(x * 16 + 8, y * 16 + 8, xt + 1 + 96, color, 0);
}
