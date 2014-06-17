#ifndef LANTERN_H
#define LANTERN_H

#include <entity/furniture.h>

class Lantern : public Furniture
{
	public:
		Lantern();

		int getLightRadius();
};

#endif
