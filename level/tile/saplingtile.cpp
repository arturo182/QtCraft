#include "saplingtile.h"

#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

SaplingTile::SaplingTile(qint8 id, Tile *onType, Tile *growsTo) :
	Tile(id)
{
	m_onType = onType;
	m_growsTo = growsTo;

	connectsToSand = onType->connectsToSand;
	connectsToGrass = onType->connectsToGrass;
	connectsToWater = onType->connectsToWater;
	connectsToLava = onType->connectsToLava;
}

void SaplingTile::render(Screen *screen, Level *level, int x, int y)
{
	m_onType->render(screen, level, x, y);

	int col = Color::get(10, 40, 50, -1);
	screen->render(x * 16 + 4, y * 16 + 4, 107, col, 0);
}

void SaplingTile::tick(Level *level, int xt, int yt)
{
	int age = level->getData(xt, yt) + 1;
	if(age > 100) {
		level->setTile(xt, yt, m_growsTo, 0);
	} else {
		level->setData(xt, yt, age);
	}
}

void SaplingTile::hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir)
{
	level->setTile(x, y, m_onType, 0);
}
