#ifndef ORETILE_H
#define ORETILE_H

#include <level/tile/tile.h>

class Resource;

class OreTile : public Tile
{
	public:
		OreTile(qint8 id, Resource *toDrop);

		void render(Screen *screen, Level *level, int x, int y);
		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);
		void hurt(Level *level, int x, int y, int dmg);

		bool mayPass(Level *level, int x, int y, Entity *e);
		bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
		void bumpedInto(Level *level, int xt, int yt, Entity *entity);

	private:
		Resource *m_toDrop;
		int m_color;
};

#endif
