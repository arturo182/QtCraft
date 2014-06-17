#include "wheattile.h"

#include <entity/itementity.h>
#include <item/resourceitem.h>
#include <item/resource.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

WheatTile::WheatTile(qint8 id) :
	Tile(id)
{
}

void WheatTile::tick(Level *level, int xt, int yt)
{
	if(qrand() % 2 == 0) {
		return;
	}

	int age = level->getData(xt, yt);
	if(age < 50) {
		level->setData(xt, yt, age + 1);
	}
}

void WheatTile::render(Screen *screen, Level *level, int x, int y)
{
	int age = level->getData(x, y);
	int col = Color::get(level->dirtColor - 121, level->dirtColor - 11, level->dirtColor, 50);
	int icon = age / 10;

	if(icon >= 3) {
		col = Color::get(level->dirtColor - 121, level->dirtColor - 11, 50 + icon * 100, 40 + (icon - 3) * 2 * 100);

		if(age == 50) {
			col = Color::get(0, 0, 50 + icon * 100, 40 + (icon - 3) * 2 * 100);
		}

		icon = 3;
	}

	screen->render(x * 16 + 0, y * 16 + 0, 100 + icon, col, 0);
	screen->render(x * 16 + 8, y * 16 + 0, 100 + icon, col, 0);
	screen->render(x * 16 + 0, y * 16 + 8, 100 + icon, col, 1);
	screen->render(x * 16 + 8, y * 16 + 8, 100 + icon, col, 1);
}

bool WheatTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if((tool->type == ToolType::shovel) && (player->payStamina(4 - tool->level))) {
			level->setTile(xt, yt, Tile::dirt, 0);

			return true;
		}
	}

	return false;
}

void WheatTile::steppedOn(Level *level, int xt, int yt, Entity *entity)
{
	if(qrand() % 60 != 0) {
		return;
	}

	if(level->getData(xt, yt) < 2) {
		return;
	}

	harvest(level, xt, yt);
}

void WheatTile::hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir)
{
	harvest(level, x, y);
}

void WheatTile::harvest(Level *level, int x, int y)
{
	int age = level->getData(x, y);

	int count = qrand() % 2;
	for(int i = 0; i < count; ++i) {
		level->add(new ItemEntity(new ResourceItem(Resource::seeds), x * 16 + qrand() % 10 + 3, y * 16 + qrand() % 10 + 3));
	}

	count = 0;
	if(age == 50) {
		count = qrand() % 3 + 2;
	} else if(age >= 40) {
		count = qrand() % 2 + 1;
	}

	for(int i = 0; i < count; ++i) {
		level->add(new ItemEntity(new ResourceItem(Resource::wheat), x * 16 + qrand() % 10 + 3, y * 16 + qrand() % 10 + 3));
	}

	level->setTile(x, y, Tile::dirt, 0);
}
