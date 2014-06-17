#include "plantableresource.h"

#include <level/tile/tile.h>
#include <level/level.h>

#include <QDebug>

PlantableResource::PlantableResource(QString name, int sprite, int color, Tile *targetTile, QList<Tile*> sourceTiles) :
	Resource(name, sprite, color)
{
	m_targetTile = targetTile;
	m_sourceTiles = sourceTiles;
}

bool PlantableResource::interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir)
{
	if(m_sourceTiles.contains(tile)) {
		level->setTile(xt, yt, m_targetTile, 0);

		return true;
	}

	return false;
}
