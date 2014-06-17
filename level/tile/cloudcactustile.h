#ifndef CLOUDCACTUSTILE_H
#define CLOUDCACTUSTILE_H

#include <level/tile/tile.h>

class CloudCactusTile : public Tile
{
	public:
		CloudCactusTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);
		bool mayPass(Level *level, int x, int y, Entity *e);

		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);
		void hurt(Level *level, int x, int y, int dmg);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);

		void bumpedInto(Level *level, int xt, int yt, Entity *entity);

};

#endif
