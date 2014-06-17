#include "cactustile.h"

#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
#include <entity/itementity.h>
#include <item/resourceitem.h>
#include <entity/entity.h>
#include <item/resource.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

CactusTile::CactusTile(qint8 id) :
	Tile(id)
{
	connectsToSand = true;
}

void CactusTile::tick(Level *level, int xt, int yt)
{
	int damage = level->getData(xt, yt);
	if(damage > 0) {
		level->setData(xt, yt, damage - 1);
	}
}

void CactusTile::render(Screen *screen, Level *level, int x, int y)
{
	int col = Color::get(20, 40, 50, level->sandColor);

	screen->render(x * 16 + 0, y * 16 + 0, 72, col, 0);
	screen->render(x * 16 + 8, y * 16 + 0, 73, col, 0);
	screen->render(x * 16 + 0, y * 16 + 8, 104, col, 0);
	screen->render(x * 16 + 8, y * 16 + 8, 105, col, 0);
}

void CactusTile::hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir)
{
	int damage = level->getData(x, y) + dmg;
	level->add(new SmashParticle(x * 16 + 8, y * 16 + 8));
	level->add(new TextParticle(dmg, x * 16 + 8, y * 16 + 8, Color::get(-1, 500, 500, 500)));

	if(damage >= 10) {
		int count = qrand() % 2 + 1;
		for(int i = 0; i < count; ++i) {
			level->add(new ItemEntity(new ResourceItem(Resource::cactusFlower), x * 16 + qrand() % 10 + 3, y * 16 + qrand() % 10 + 3));
		}

		level->setTile(x, y, Tile::sand, 0);
	} else {
		level->setData(x, y, damage);
	}
}

bool CactusTile::mayPass(Level *level, int x, int y, Entity *e)
{
	return false;
}

void CactusTile::bumpedInto(Level *level, int xt, int yt, Entity *entity)
{
	entity->hurt(this, xt, yt, 1);
}
