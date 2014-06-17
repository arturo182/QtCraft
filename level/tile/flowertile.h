#ifndef FLOWERTILE_H
#define FLOWERTILE_H

#include <level/tile/grasstile.h>

class FlowerTile : public GrassTile
{
	public:
		FlowerTile(qint8 id);

		void render(Screen *screen, Level *level, int x, int y);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);
};

#endif
