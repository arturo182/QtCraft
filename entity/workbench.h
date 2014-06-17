#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <entity/furniture.h>

class Workbench : public Furniture
{
	public:
		Workbench();

		bool use(Player *player, int attackDir);
};

#endif
