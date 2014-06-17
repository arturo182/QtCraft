#ifndef SAPLINGTILE_H
#define SAPLINGTILE_H

#include <level/tile/tile.h>

class SaplingTile : public Tile
{
	public:
		SaplingTile(qint8 id, Tile *onType, Tile *growsTo);

		void render(Screen *screen, Level *level, int x, int y);
		void tick(Level *level, int xt, int yt);
		void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir);

	private:
		Tile *m_onType;
		Tile *m_growsTo;
};

#endif
