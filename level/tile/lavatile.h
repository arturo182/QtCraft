#ifndef LAVATILE_H
#define LAVATILE_H

#include <level/tile/tile.h>

class LavaTile : public Tile
{
	public:
		LavaTile(qint8 id);

		void tick(Level *level, int xt, int yt);
		void render(Screen *screen, Level *level, int x, int y);
		bool mayPass(Level *level, int x, int y, Entity *e);
		int getLightRadius(Level *level, int x, int y);

};

#endif
