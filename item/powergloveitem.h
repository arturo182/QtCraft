#ifndef POWERGLOVEITEM_H
#define POWERGLOVEITEM_H

#include <item/item.h>

class PowerGloveItem : public Item
{
	public:
		int getColor() const;
		int getSprite() const;
		QString getName() const;

		void renderIcon(Screen *screen, int x, int y);
		void renderInventory(Screen *screen, const int &x, const int &y) const;

		bool interact(Player *player, Entity *entity, int attackDir);
};

#endif
