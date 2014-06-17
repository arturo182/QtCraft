#include "resourcerecipe.h"

#include <item/resourceitem.h>
#include <entity/inventory.h>
#include <entity/player.h>

ResourceRecipe::ResourceRecipe(Resource *resource) :
	Recipe(new ResourceItem(resource, 1))
{
	m_resource = resource;
}

void ResourceRecipe::craft(Player *player)
{
	player->inventory->add(0, new ResourceItem(m_resource, 1));
}
