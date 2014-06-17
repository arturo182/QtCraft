#ifndef TREETILE_H
#define TREETILE_H

#include <level/tile/tile.h>

class TreeTile : public Tile
{
	public:
		TreeTile(qint8 id);

		void tick(Level *level, int xt, int yt);
		void render(Screen *screen, Level *level, int x, int y);

		bool mayPass(Level *level, int x, int y, Entity *e);
		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);
		void hurt(Level *level, int x, int y, int dmg);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);

};

#endif
