#include "dirttile.h"

#include <item/resourceitem.h>
#include <entity/itementity.h>
#include <item/resource.h>
#include <entity/player.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <sound.h>

DirtTile::DirtTile(qint8 id) :
	Tile(id)
{
}

void DirtTile::render(Screen *screen, Level *level, int x, int y)
{
	int col = Color::get(level->dirtColor, level->dirtColor, level->dirtColor - 111, level->dirtColor - 111);

	screen->render(x * 16 + 0, y * 16 + 0, 0, col, 0);
	screen->render(x * 16 + 8, y * 16 + 0, 1, col, 0);
	screen->render(x * 16 + 0, y * 16 + 8, 2, col, 0);
	screen->render(x * 16 + 8, y * 16 + 8, 3, col, 0);
}

bool DirtTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if((tool->type == ToolType::shovel) && (player->payStamina(4 - tool->level))) {
			level->setTile(xt, yt, Tile::hole, 0);
			level->add(new ItemEntity(new ResourceItem(Resource::dirt), xt * 16 + qrand() % 10 + 3, yt * 16 + qrand() % 10 + 3));

			Sound::monsterHurt->play();

			return true;
		}

		if((tool->type == ToolType::hoe) && (player->payStamina(4 - tool->level))) {
			level->setTile(xt, yt, Tile::farmland, 0);

			Sound::monsterHurt->play();

			return true;
		}
	}

	return false;
}
