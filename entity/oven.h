#ifndef OVEN_H
#define OVEN_H

#include <entity/furniture.h>

class Oven : public Furniture
{
	public:
		Oven();

		bool use(Player *player, int attackDir);
};

#endif
