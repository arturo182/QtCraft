#ifndef INFINITEFALLTILE_H
#define INFINITEFALLTILE_H

#include <level/tile/tile.h>

class InfiniteFallTile : public Tile
{
	public:
		InfiniteFallTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y) { }
		bool mayPass(Level *level, int x, int y, Entity *e);
};

#endif
