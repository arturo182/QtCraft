#ifndef HARDROCKTILE_H
#define HARDROCKTILE_H

#include <level/tile/tile.h>

class HardRockTile : public Tile
{
	public:
		HardRockTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);
		void tick(Level *level, int xt, int yt);

		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);
		void hurt(Level *level, int x, int y, int dmg);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
		bool mayPass(Level *level, int x, int y, Entity *e);
};

#endif
