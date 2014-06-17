#ifndef FURNITURERECIPE_H
#define FURNITURERECIPE_H

#include <item/furnitureitem.h>
#include <entity/inventory.h>
#include <crafting/recipe.h>
#include <entity/player.h>

template<class T>
class FurnitureRecipe : public Recipe
{
	public:
		FurnitureRecipe() : Recipe(new FurnitureItem(new T())) { }

		void craft(Player *player)
		{
			player->inventory->add(0, new FurnitureItem(new T()));
		}
};

#endif
