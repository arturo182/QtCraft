#include "powergloveitem.h"

#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>
#include <entity/furniture.h>

int PowerGloveItem::getColor() const
{
	return Color::get(-1, 100, 320, 430);
}

int PowerGloveItem::getSprite() const
{
	return 135;
}

QString PowerGloveItem::getName() const
{
	return "Pow glove";
}

void PowerGloveItem::renderIcon(Screen *screen, int x, int y)
{
	screen->render(x, y, getSprite(), getColor(), 0);
}

void PowerGloveItem::renderInventory(Screen *screen, const int &x, const int &y) const
{
	screen->render(x, y, getSprite(), getColor(), 0);
	Font::draw(getName(), screen, x + 8, y, Color::get(-1, 555, 555, 555));
}

bool PowerGloveItem::interact(Player *player, Entity *entity, int attackDir)
{
	if(Furniture *f = dynamic_cast<Furniture*>(entity)) {
		f->take(player);

		return true;
	}

	return false;
}
