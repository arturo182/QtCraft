#include "rocktile.h"

#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
#include <entity/itementity.h>
#include <item/resourceitem.h>
#include <item/resource.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

RockTile::RockTile(qint8 id) :
	Tile(id)
{
}

void RockTile::render(Screen *screen, Level *level, int x, int y)
{
	int col = Color::get(444, 444, 333, 333);
	int transitionColor = Color::get(111, 444, 555, level->dirtColor);

	bool u = (level->getTile(x, y - 1) != this);
	bool d = (level->getTile(x, y + 1) != this);
	bool l = (level->getTile(x - 1, y) != this);
	bool r = (level->getTile(x + 1, y) != this);

	bool ul = (level->getTile(x - 1, y - 1) != this);
	bool dl = (level->getTile(x - 1, y + 1) != this);
	bool ur = (level->getTile(x + 1, y - 1) != this);
	bool dr = (level->getTile(x + 1, y + 1) != this);

	if(!u && !l) {
		if(!ul) {
			screen->render(x * 16 + 0, y * 16 + 0, 0, col, 0);
		} else {
			screen->render(x * 16 + 0, y * 16 + 0, 7, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 0, y * 16 + 0, (l ? 6 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);
	}

	if(!u && !r) {
		if(!ur) {
			screen->render(x * 16 + 8, y * 16 + 0, 1, col, 0);
		} else {
			screen->render(x * 16 + 8, y * 16 + 0, 8, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 8, y * 16 + 0, (r ? 4 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);
	}

	if(!d && !l) {
		if(!dl) {
			screen->render(x * 16 + 0, y * 16 + 8, 2, col, 0);
		} else {
			screen->render(x * 16 + 0, y * 16 + 8, 39, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 0, y * 16 + 8, (l ? 6 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	}

	if(!d && !r) {
		if(!dr) {
			screen->render(x * 16 + 8, y * 16 + 8, 3, col, 0);
		} else {
			screen->render(x * 16 + 8, y * 16 + 8, 40, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 8, y * 16 + 8, (r ? 4 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	}
}

bool RockTile::mayPass(Level *level, int x, int y, Entity *e)
{
	return false;
}

bool RockTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if((tool->type == ToolType::pickaxe) && (player->payStamina(4 - tool->level))) {
			hurt(level, xt, yt, qrand() % 10 + tool->level * 5 + 10);

			return true;
		}
	}

	return false;
}

void RockTile::hurt(Level *level, int x, int y, int dmg)
{
	int damage = level->getData(x, y) + dmg;
	level->add(new SmashParticle(x * 16 + 8, y * 16 + 8));
	level->add(new TextParticle(dmg, x * 16 + 8, y * 16 + 8, Color::get(-1, 500, 500, 500)));

	if(damage >= 50) {
		int count = qrand() % 4 + 1;
		for(int i = 0; i < count; ++i) {
			level->add(new ItemEntity(new ResourceItem(Resource::stone), x * 16 + qrand() % 10 + 3, y * 16 + qrand() % 10 + 3));
		}

		count = qrand() % 2;
		for(int i = 0; i < count; ++i) {
			level->add(new ItemEntity(new ResourceItem(Resource::coal), x * 16 + qrand() % 10 + 3, y * 16 + qrand() % 10 + 3));
		}

		level->setTile(x, y, Tile::dirt, 0);
	} else {
		level->setData(x, y, damage);
	}
}

void RockTile::tick(Level *level, int xt, int yt)
{
	int damage = level->getData(xt, yt);
	if(damage > 0) {
		level->setData(xt, yt, damage - 1);
	}
}
