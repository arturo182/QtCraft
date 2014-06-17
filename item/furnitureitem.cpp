#include "furnitureitem.h"

#include <entity/furniture.h>
#include <level/tile/tile.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>

FurnitureItem::FurnitureItem(Furniture *furniture) :
	placed(false)
{
	this->furniture = furniture;
}

int FurnitureItem::getColor() const
{
	return furniture->col;
}

int FurnitureItem::getSprite() const
{
	return furniture->sprite + 320;
}

QString FurnitureItem::getName() const
{
	return furniture->name;
}

bool FurnitureItem::canAttack() const
{
	return false;
}

bool FurnitureItem::isDepleted() const
{
	return placed;
}

void FurnitureItem::renderIcon(Screen *screen, int x, int y)
{
	screen->render(x, y, getSprite(), getColor(), 0);
}

void FurnitureItem::renderInventory(Screen *screen, const int &x, const int &y) const
{
	screen->render(x, y, getSprite(), getColor(), 0);
	Font::draw(furniture->name, screen, x + 8, y, Color::get(-1, 555, 555, 555));
}

bool FurnitureItem::interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir)
{
	if(tile->mayPass(level, xt, yt, furniture)) {
		furniture->x = (xt * 16 + 8);
		furniture->y = (yt * 16 + 8);

		level->add(furniture);
		placed = true;

		return true;
	}

	return false;
}
