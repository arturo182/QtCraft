#ifndef GRASSTILE_H
#define GRASSTILE_H

#include <level/tile/tile.h>

class GrassTile : public Tile
{
	public:
		GrassTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);
		void tick(Level *level, int xt, int yt);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
};

#endif
