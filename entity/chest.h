#ifndef CHEST_H
#define CHEST_H

#include <entity/furniture.h>

class Inventory;

class Chest : public Furniture
{
	public:
		Chest();

		bool use(Player *player, int attackDir);

	public:
		Inventory *inventory;
};

#endif
