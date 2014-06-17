#ifndef HOLETILE_H
#define HOLETILE_H

#include <level/tile/tile.h>

class HoleTile : public Tile
{
	public:
		HoleTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);

		bool mayPass(Level *level, int x, int y, Entity *e);
};

#endif
