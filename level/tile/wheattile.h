#ifndef WHEATTILE_H
#define WHEATTILE_H

#include <level/tile/tile.h>

class WheatTile : public Tile
{
	public:
		WheatTile(qint8 id);

		void tick(Level *level, int xt, int yt);
		void render(Screen *screen, Level *level, int x, int y);

		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
		void steppedOn(Level *level, int xt, int yt, Entity *entity);
		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);

	private:
		void harvest(Level *level, int x, int y);
};

#endif
