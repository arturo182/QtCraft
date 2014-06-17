#ifndef STAIRSTILE_H
#define STAIRSTILE_H

#include <level/tile/tile.h>

class StairsTile : public Tile
{
	public:
		StairsTile(qint8 id, bool leadsUp);

		void render(Screen *screen, Level *level, int x, int y);

	public:
		bool leadsUp;
};

#endif
