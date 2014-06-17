#ifndef SANDTILE_H
#define SANDTILE_H

#include <level/tile/tile.h>

class SandTile : public Tile
{
	public:
		SandTile(qint8 id);

		void tick(Level *level, int x, int y);
		void render(Screen *screen, Level *level, int x, int y);

		void steppedOn(Level *level, int xt, int yt, Entity *entity);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
};

#endif
