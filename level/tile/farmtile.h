#ifndef FARMTILE_H
#define FARMTILE_H

#include <level/tile/tile.h>

class FarmTile : public Tile
{
	public:
		FarmTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);
		void tick(Level *level, int xt, int yt);

		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
		void steppedOn(Level *level, int xt, int yt, Entity *entity);
};

#endif
