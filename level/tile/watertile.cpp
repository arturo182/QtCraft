#include "watertile.h"

#include <entity/entity.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

WaterTile::WaterTile(qint8 id) :
	Tile(id)
{
	connectsToSand = true;
	connectsToWater = true;
}

void WaterTile::render(Screen *screen, Level *level, int x, int y)
{
	//qsrand((tickCount + (x / 2 - y) * 4311) / 10 * 54687121 + x * 3271612 + y * 3412987161);

	int col = Color::get(5, 5, 115, 115);
	int transitionColor1 = Color::get(3, 5, level->dirtColor - 111, level->dirtColor);
	int transitionColor2 = Color::get(3, 5, level->sandColor - 110, level->sandColor);

	bool u = !level->getTile(x, y - 1)->connectsToWater;
	bool d = !level->getTile(x, y + 1)->connectsToWater;
	bool l = !level->getTile(x - 1, y)->connectsToWater;
	bool r = !level->getTile(x + 1, y)->connectsToWater;

	bool su = (u && level->getTile(x, y - 1)->connectsToSand);
	bool sd = (d && level->getTile(x, y + 1)->connectsToSand);
	bool sl = (l && level->getTile(x - 1, y)->connectsToSand);
	bool sr = (r && level->getTile(x + 1, y)->connectsToSand);

	if(!u && !l) {
		screen->render(x * 16 + 0, y * 16 + 0, qrand() % 4, col, qrand() % 4);
	} else {
		screen->render(x * 16 + 0, y * 16 + 0, (l ? 14 : 15) + (u ? 0 : 1) * 32, (su || sl) ? transitionColor2 : transitionColor1, 0);
	}

	if(!u && !r) {
		screen->render(x * 16 + 8, y * 16 + 0, qrand() % 4, col, qrand() % 4);
	} else {
		screen->render(x * 16 + 8, y * 16 + 0, (r ? 16 : 15) + (u ? 0 : 1) * 32, (su || sr) ? transitionColor2 : transitionColor1, 0);
	}

	if(!d && !l) {
		screen->render(x * 16 + 0, y * 16 + 8, qrand() % 4, col, qrand() % 4);
	} else {
		screen->render(x * 16 + 0, y * 16 + 8, (l ? 14 : 15) + (d ? 2 : 1) * 32, (sd || sl) ? transitionColor2 : transitionColor1, 0);
	}

	if(!d && !r) {
		screen->render(x * 16 + 8, y * 16 + 8, qrand() % 4, col, qrand() % 4);
	} else {
		screen->render(x * 16 + 8, y * 16 + 8, (r ? 16 : 15) + (d ? 2 : 1) * 32, (sd || sr) ? transitionColor2 : transitionColor1, 0);
	}
}

bool WaterTile::mayPass(Level *level, int x, int y, Entity *e)
{
	return e->canSwim();
}

void WaterTile::tick(Level *level, int xt, int yt)
{
	int xn = xt;
	int yn = yt;

	if(qrand() % 2 == 0) {
		xn += qrand() % 2 * 2 - 1;
	} else {
		yn += qrand() % 2 * 2 - 1;
	}

	if(level->getTile(xn, yn) == Tile::hole) {
		level->setTile(xn, yn, this, 0);
	}
}
