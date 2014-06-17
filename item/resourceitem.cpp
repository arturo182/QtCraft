#include "resourceitem.h"

#include <item/resource.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>

#include <QDebug>

ResourceItem::ResourceItem(Resource *resource):
	count(1)
{
	this->resource = resource;
}

ResourceItem::ResourceItem(Resource *resource, int count)
{
	this->resource = resource;
	this->count = count;
}

int ResourceItem::getColor() const
{
	return resource->color;
}

int ResourceItem::getSprite() const
{
	return resource->sprite;
}

QString ResourceItem::getName() const
{
	return resource->name;
}

bool ResourceItem::isDepleted() const
{
	return count <= 0;
}

void ResourceItem::renderIcon(Screen *screen, int x, int y)
{
	screen->render(x, y, resource->sprite, resource->color, 0);
}

void ResourceItem::renderInventory(Screen *screen, const int &x, const int &y) const
{
	screen->render(x, y, resource->sprite, resource->color, 0);
	Font::draw(resource->name, screen, x + 32, y, Color::get(-1, 555, 555, 555));

	int cc = count;
	if(cc > 999) {
		cc = 999;
	}

	Font::draw(cc, screen, x + 8, y, Color::get(-1, 444, 444, 444));
}

bool ResourceItem::interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir)
{
	if(resource->interactOn(tile, level, xt, yt, player, attackDir)) {
		count -= 1;

		return true;
	}

	return false;
}
