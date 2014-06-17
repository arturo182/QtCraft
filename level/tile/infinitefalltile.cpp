#include "infinitefalltile.h"

#include <entity/airwizard.h>

InfiniteFallTile::InfiniteFallTile(qint8 id) :
	Tile(id)
{
}

bool InfiniteFallTile::mayPass(Level *level, int x, int y, Entity *e)
{
	AirWizard *wizard = dynamic_cast<AirWizard*>(e);
	return wizard;
}
