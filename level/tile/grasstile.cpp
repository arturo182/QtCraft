#include "grasstile.h"

#include <item/resourceitem.h>
#include <entity/itementity.h>
#include <item/resource.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <sound.h>

GrassTile::GrassTile(qint8 id) :
	Tile(id)
{
	connectsToGrass = true;
}

void GrassTile::render(Screen *screen, Level *level, int x, int y)
{
	int col = Color::get(level->grassColor, level->grassColor, level->grassColor + 111, level->grassColor + 111);
	int transitionColor = Color::get(level->grassColor - 111, level->grassColor, level->grassColor + 111, level->dirtColor);

	bool u = !level->getTile(x, y - 1)->connectsToGrass;
	bool d = !level->getTile(x, y + 1)->connectsToGrass;
	bool l = !level->getTile(x - 1, y)->connectsToGrass;
	bool r = !level->getTile(x + 1, y)->connectsToGrass;

	if(!u && !l) {
		screen->render(x * 16 + 0, y * 16 + 0, 0, col, 0);
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
		screen->render(x * 16 + 8, y * 16 + 8, 3, col, 0);
	} else {
		screen->render(x * 16 + 8, y * 16 + 8, (r ? 13 : 12) + (d ? 2 : 1) * 32, transitionColor, 0);
	}
}

void GrassTile::tick(Level *level, int xt, int yt)
{
	if(qrand() % 40 != 0) {
		return;
	}

	int xn = xt;
	int yn = yt;

	if(qrand() % 2 == 0) {
		xn += qrand() % 2 * 2 - 1;
	} else {
		yn += qrand() % 2 * 2 - 1;
	}

	if(level->getTile(xn, yn) == Tile::dirt) {
		level->setTile(xn, yn, this, 0);
	}
}

bool GrassTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if((tool->type == ToolType::shovel) && (player->payStamina(4 - tool->level))) {
			level->setTile(xt, yt, Tile::dirt, 0);

			Sound::monsterHurt->play();

			if(qrand() % 5 == 0) {
				level->add(new ItemEntity(new ResourceItem(Resource::seeds), xt * 16 + qrand() % 10 + 3, yt * 16 + qrand() % 10 + 3));
				return true;
			}
		}

		if((tool->type == ToolType::hoe) && (player->payStamina(4 - tool->level))) {
			Sound::monsterHurt->play();

			if(qrand() % 5 == 0) {
				level->add(new ItemEntity(new ResourceItem(Resource::seeds), xt * 16 + qrand() % 10 + 3, yt * 16 + qrand() % 10 + 3));
				return true;
			}

			level->setTile(xt, yt, Tile::farmland, 0);
			return true;
		}
	}

	return false;
}
