#include "flowertile.h"

#include <item/resourceitem.h>
#include <entity/itementity.h>
#include <item/resource.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

FlowerTile::FlowerTile(qint8 id) :
	GrassTile(id)
{
	tiles[id] = this;
	connectsToGrass = true;
}

void FlowerTile::render(Screen *screen, Level *level, int x, int y)
{
	GrassTile::render(screen, level, x, y);

	int data = level->getData(x, y);
	int shape = data / 16 % 2;
	int flowerCol = Color::get(10, level->grassColor, 555, 440);

	if(shape == 0) {
		screen->render(x * 16 + 0, y * 16 + 0, 33, flowerCol, 0);
	}

	if(shape == 1) {
		screen->render(x * 16 + 8, y * 16 + 0, 33, flowerCol, 0);
	}

	if(shape == 1) {
		screen->render(x * 16 + 0, y * 16 + 8, 33, flowerCol, 0);
	}

	if(shape == 0) {
		screen->render(x * 16 + 8, y * 16 + 8, 33, flowerCol, 0);
	}
}

bool FlowerTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if((tool->type == ToolType::shovel) && (player->payStamina(4 - tool->level))) {
			level->add(new ItemEntity(new ResourceItem(Resource::flower), xt * 16 + qrand() % 10 + 3, yt * 16 + qrand() % 10 + 3));
			level->add(new ItemEntity(new ResourceItem(Resource::flower), xt * 16 + qrand() % 10 + 3, yt * 16 + qrand() % 10 + 3));
			level->setTile(xt, yt, Tile::grass, 0);

			return true;
		}
	}

	return false;
}

void FlowerTile::hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir)
{
	int count = qrand() % 2 + 1;
	for(int i = 0; i < count; ++i) {
		level->add(new ItemEntity(new ResourceItem(Resource::flower), x * 16 + qrand() % 10 + 3, y * 16 + qrand() % 10 + 3));
	}

	level->setTile(x, y, Tile::grass, 0);
}
