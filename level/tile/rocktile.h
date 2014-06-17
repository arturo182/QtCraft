#ifndef ROCKTILE_H
#define ROCKTILE_H

#include <level/tile/tile.h>

class RockTile : public Tile
{
	public:
		RockTile(qint8 id);

		void tick(Level *level, int xt, int yt);
		void render(Screen *screen, Level *level, int x, int y);

		bool mayPass(Level *level, int x, int y, Entity *e);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
		void hurt(Level *level, int x, int y, int dmg);
};

#endif
