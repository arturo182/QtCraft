#ifndef INVENTORY_H
#define INVENTORY_H

#include <QList>

class ResourceItem;
class Resource;
class Item;

class Inventory
{
	public:
		Inventory() { }

		void add(Item *item);
		void add(int slot, Item *item);
		int count(Item *item);

		bool hasResources(Resource *r, int count);
		bool removeResource(Resource *r, int count);

	public:
		QList<Item*> items;

	private:
		ResourceItem *findResource(Resource *resource);
};

#endif
