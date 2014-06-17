#include "cloudtile.h"

#include <entity/itementity.h>
#include <item/resourceitem.h>
#include <entity/player.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <item/resource.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

CloudTile::CloudTile(qint8 id) :
	Tile(id)
{

}

void CloudTile::render(Screen *screen, Level *level, int x, int y)
{
	int col = Color::get(444, 444, 555, 555);
	int transitionColor = Color::get(333, 444, 555, -1);

	bool u = (level->getTile(x, y - 1) == Tile::infiniteFall);
	bool d = (level->getTile(x, y + 1) == Tile::infiniteFall);
	bool l = (level->getTile(x - 1, y) == Tile::infiniteFall);
	bool r = (level->getTile(x + 1, y) == Tile::infiniteFall);

	bool ul = (level->getTile(x - 1, y - 1) == Tile::infiniteFall);
	bool dl = (level->getTile(x - 1, y + 1) == Tile::infiniteFall);
	bool ur = (level->getTile(x + 1, y - 1) == Tile::infiniteFall);
	bool dr = (level->getTile(x + 1, y + 1) == Tile::infiniteFall);

	if(!u && !l) {
		if(!ul) {
			screen->render(x * 16 + 0, y * 16 + 0, 17, col, 0);
		} else {
			screen->render(x * 16 + 0, y * 16 + 0, 7 + 0 * 32, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 0, y * 16 + 0, (l ? 6 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);
	}

	if(!u && !r) {
		if(!ur) {
			screen->render(x * 16 + 8, y * 16 + 0, 18, col, 0);
		} else {
			screen->render(x * 16 + 8, y * 16 + 0, 8 + 0 * 32, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 8, y * 16 + 0, (r ? 4 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);
	}

	if(!d && !l) {
		if(!dl) {
			screen->render(x * 16 + 0, y * 16 + 8, 20, col, 0);
		} else {
			screen->render(x * 16 + 0, y * 16 + 8, 7 + 1 * 32, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 0, y * 16 + 8, (l ? 6 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	}

	if(!d && !r) {
		if(!dr) {
			screen->render(x * 16 + 8, y * 16 + 8, 19, col, 0);
		} else {
			screen->render(x * 16 + 8, y * 16 + 8, 8 + 1 * 32, transitionColor, 3);
		}
	} else {
		screen->render(x * 16 + 8, y * 16 + 8, (r ? 4 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	}
}

bool CloudTile::mayPass(Level *level, int x, int y, Entity *e)
{
	return true;
}

bool CloudTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if(tool->type == ToolType::shovel) {
			if(player->payStamina(5)) {
				// level.setTile(xt, yt, Tile.infiniteFall, 0);
				int count = qrand() % 2 + 1;
				for(int i = 0; i < count; ++i) {
					level->add(new ItemEntity(new ResourceItem(Resource::cloud), xt * 16 + qrand() % 10 + 3, yt * 16 + qrand() % 10 + 3));
				}

				return true;
			}
		}
	}
	return false;
}
