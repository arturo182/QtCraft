#include "toolitem.h"

#include <item/tooltype.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>

#include <QStringList>

QStringList ToolItem::LEVEL_NAMES = QStringList() << "Wood"
												  << "Rock"
												  << "Iron"
												  << "Gold"
												  << "Gem";

QList<int> ToolItem::LEVEL_COLORS = QList<int>() << Color::get(-1, 100, 321, 431)
												 << Color::get(-1, 100, 321, 111)
												 << Color::get(-1, 100, 321, 555)
												 << Color::get(-1, 100, 321, 550)
												 << Color::get(-1, 100, 321, 45);

ToolItem::ToolItem(ToolType *type, int level)
{
	this->type = type;
	this->level = level;
}

int ToolItem::getColor() const
{
	return LEVEL_COLORS[level];
}

int ToolItem::getSprite() const
{
	return type->sprite + 160;
}

QString ToolItem::getName() const
{
	return LEVEL_NAMES[level] + " " + type->name;
}

int ToolItem::getAttackDamageBonus(Entity *e)
{
	if(type == ToolType::axe) {
		return (level + 1) * 2 + qrand() % 4;
	}

	if(type == ToolType::sword) {
		return (level + 1) * 3 + qrand() % (2 + level * level * 2);
	}

	return 1;
}

bool ToolItem::matches(Item *item)
{
	if(ToolItem *other = dynamic_cast<ToolItem*>(item)) {
		if(other->type != type) {
			return false;
		}

		return other->level == level;
	}

	return false;
}

bool ToolItem::canAttack()
{
	return true;
}

void ToolItem::renderIcon(Screen *screen, int x, int y)
{
	screen->render(x, y, getSprite(), getColor(), 0);
}

void ToolItem::renderInventory(Screen *screen, const int &x, const int &y) const
{
	screen->render(x, y, getSprite(), getColor(), 0);
	Font::draw(getName(), screen, x + 8, y, Color::get(-1, 555, 555, 555));
}
