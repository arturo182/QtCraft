#ifndef RESOURCEITEM_H
#define RESOURCEITEM_H

#include <item/item.h>

class Resource;

class ResourceItem : public Item
{
	public:
		ResourceItem(Resource *resource);
		ResourceItem(Resource *resource, int count);

		int getColor() const;
		int getSprite() const;
		QString getName() const;
		bool isDepleted() const;

		void renderIcon(Screen *screen, int x, int y);
		void renderInventory(Screen *screen, const int &x, const int &y) const;

		bool interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir);

	public:
		Resource *resource;
		int count;
};

#endif
