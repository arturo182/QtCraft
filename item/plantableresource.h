#ifndef PLANTABLERESOURCE_H
#define PLANTABLERESOURCE_H

#include <item/resource.h>

#include <QList>

class PlantableResource : public Resource
{
	public:
		PlantableResource(QString name, int sprite, int color, Tile *targetTile, QList<Tile*> sourceTiles);

		bool interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir);

	private:
		QList<Tile*> m_sourceTiles;
		Tile *m_targetTile;
};

#endif
