#ifndef FURNITUREITEM_H
#define FURNITUREITEM_H

#include <item/item.h>

class Furniture;

class FurnitureItem : public Item
{
	public:
		FurnitureItem(Furniture *furniture);

		int getColor() const;
		int getSprite() const;
		QString getName() const;
		bool canAttack() const;
		bool isDepleted() const;

		void renderIcon(Screen *screen, int x, int y);
		void renderInventory(Screen *screen, const int &x, const int &y) const;

		bool interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir);

	public:
		Furniture *furniture;
		bool placed;
};

#endif
