#ifndef CACTUSTILE_H
#define CACTUSTILE_H

#include <level/tile/tile.h>

class CactusTile : public Tile
{
	public:
		CactusTile(qint8 id);

		void tick(Level *level, int xt, int yt);
		void render(Screen *screen, Level *level, int x, int y);

		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);
		bool mayPass(Level *level, int x, int y, Entity *e);
		void bumpedInto(Level *level, int xt, int yt, Entity *entity);
};

#endif
