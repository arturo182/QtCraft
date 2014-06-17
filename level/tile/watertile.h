#ifndef WATERTILE_H
#define WATERTILE_H

#include <level/tile/tile.h>

class WaterTile : public Tile
{
	public:
		WaterTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);
		bool mayPass(Level *level, int x, int y, Entity *e);
		void tick(Level *level, int xt, int yt);
};

#endif
