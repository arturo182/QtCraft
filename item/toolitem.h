#ifndef TOOLITEM_H
#define TOOLITEM_H

#include <item/item.h>

class ToolType;

class ToolItem : public Item
{
	public:
		static QStringList LEVEL_NAMES;
		static QList<int> LEVEL_COLORS;

	public:
		ToolItem(ToolType *type, int level);

		int getColor() const;
		int getSprite() const;
		QString getName() const;
		int getAttackDamageBonus(Entity *e);

		bool matches(Item *item);
		bool canAttack();

		void renderIcon(Screen *screen, int x, int y);
		void renderInventory(Screen *screen, const int &x, const int &y) const;
		void onTake(ItemEntity *itemEntity) { }

	public:
		ToolType *type;
		int level;
};

#endif
