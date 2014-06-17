#ifndef FURNACE_H
#define FURNACE_H

#include <entity/furniture.h>

class Furnace : public Furniture
{
	public:
		Furnace();

		bool use(Player *player, int attackDir);
};

#endif
