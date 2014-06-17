#include "farmtile.h"

#include <item/toolitem.h>
#include <item/tooltype.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

FarmTile::FarmTile(qint8 id) :
	Tile(id)
{

}

void FarmTile::render(Screen *screen, Level *level, int x, int y)
{
	int col = Color::get(level->dirtColor - 121, level->dirtColor - 11, level->dirtColor, level->dirtColor + 111);

	screen->render(x * 16 + 0, y * 16 + 0, 34, col, 1);
	screen->render(x * 16 + 8, y * 16 + 0, 34, col, 0);
	screen->render(x * 16 + 0, y * 16 + 8, 34, col, 0);
	screen->render(x * 16 + 8, y * 16 + 8, 34, col, 1);
}

void FarmTile::tick(Level *level, int xt, int yt)
{
	int age = level->getData(xt, yt);
	if(age < 5) {
		level->setData(xt, yt, age + 1);
	}
}

bool FarmTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if((tool->type == ToolType::shovel) && (player->payStamina(4 - tool->level))) {
			level->setTile(xt, yt, Tile::dirt, 0);

			return true;
		}
	}

	return false;
}

void FarmTile::steppedOn(Level *level, int xt, int yt, Entity *entity)
{
	if(qrand() % 60 != 0) {
		return;
	}

	if(level->getData(xt, yt) < 5) {
		return;
	}

	level->setTile(xt, yt, Tile::dirt, 0);
}
