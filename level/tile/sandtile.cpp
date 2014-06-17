#include "sandtile.h"

#include <entity/itementity.h>
#include <item/resourceitem.h>
#include <item/resource.h>
#include <entity/player.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

SandTile::SandTile(qint8 id) :
	Tile(id)
{
	connectsToSand = true;
}

void SandTile::tick(Level *level, int x, int y)
{
	int d = level->getData(x, y);
	if(d > 0) {
		level->setData(x, y, d - 1);
	}
}

void SandTile::render(Screen *screen, Level *level, int x, int y)
{
	int col = Color::get(level->sandColor + 2, level->sandColor, level->sandColor - 110, level->sandColor - 110);
	int transitionColor = Color::get(level->sandColor - 110, level->sandColor, level->sandColor - 110, level->dirtColor);

	bool u = !level->getTile(x, y - 1)->connectsToSand;
	bool d = !level->getTile(x, y + 1)->connectsToSand;
	bool l = !level->getTile(x - 1, y)->connectsToSand;
	bool r = !level->getTile(x + 1, y)->connectsToSand;

	bool steppedOn = level->getData(x, y) > 0;

	if(!u && !l) {
		if(!steppedOn) {
			screen->render(x * 16 + 0, y * 16 + 0, 0, col, 0);
		} else {
			screen->render(x * 16 + 0, y * 16 + 0, 35, col, 0);
		}
	} else {
		screen->render(x * 16 + 0, y * 16 + 0, (l ? 11 : 12) + (u ? 0 : 1) * 32, transitionColor, 0);
	}

	if(!u && !r) {
		screen->render(x * 16 + 8, y * 16 + 0, 1, col, 0);
	} else {
		screen->render(x * 16 + 8, y * 16 + 0, (r ? 13 : 12) + (u ? 0 : 1) * 32, transitionColor, 0);
	}

	if(!d && !l) {
		screen->render(x * 16 + 0, y * 16 + 8, 2, col, 0);
	} else {
		screen->render(x * 16 + 0, y * 16 + 8, (l ? 11 : 12) + (d ? 2 : 1) * 32, transitionColor, 0);
	}

	if(!d && !r) {
		if(!steppedOn) {
			screen->render(x * 16 + 8, y * 16 + 8, 3, col, 0);
		} else {
			screen->render(x * 16 + 8, y * 16 + 8, 35, col, 0);
		}
	} else {
		screen->render(x * 16 + 8, y * 16 + 8, (r ? 13 : 12) + (d ? 2 : 1) * 32, transitionColor, 0);
	}
}

void SandTile::steppedOn(Level *level, int xt, int yt, Entity *entity)
{
	Mob *mob = dynamic_cast<Mob*>(entity);
	if(mob) {
		level->setData(xt, yt, 10);
	}
}

bool SandTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if((tool->type == ToolType::shovel) && (player->payStamina(4 - tool->level))) {
			level->setTile(xt, yt, Tile::dirt, 0);
			level->add(new ItemEntity(new ResourceItem(Resource::sand), xt * 16 + qrand() % 10 + 3, yt * 16 + qrand() % 10 + 3));

			return true;
		}
	}

	return false;
}
