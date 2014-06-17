#ifndef ANVIL_H
#define ANVIL_H

#include <entity/furniture.h>

class Anvil : public Furniture
{
	public:
		Anvil();

		bool use(Player *player, int attackDir);
};

#endif
