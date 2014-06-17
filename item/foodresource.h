#ifndef FOODRESOURCE_H
#define FOODRESOURCE_H

#include <item/resource.h>

class FoodResource : public Resource
{
	public:
		FoodResource(QString name, int sprite, int colot, int heal, int staminaCost);

		bool interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir);

	private:
		int m_heal;
		int m_staminaCost;
};

#endif
