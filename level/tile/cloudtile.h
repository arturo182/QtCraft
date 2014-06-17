#ifndef CLOUDTILE_H
#define CLOUDTILE_H

#include <level/tile/tile.h>

class CloudTile : public Tile
{
	public:
		CloudTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);
		bool mayPass(Level *level, int x, int y, Entity *e);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
};

#endif
