#ifndef DIRTTILE_H
#define DIRTTILE_H

#include <level/tile/tile.h>

class DirtTile : public Tile
{
	public:
		DirtTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);

		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
};

#endif
