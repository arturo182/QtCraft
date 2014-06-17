#include "chest.h"

#include <screen/containermenu.h>
#include <entity/inventory.h>
#include <entity/player.h>
#include <gfx/color.h>
#include <game.h>

Chest::Chest() :
	Furniture("Chest"),
	inventory(new Inventory)
{
	col = Color::get(-1, 110, 331, 552);
	sprite = 1;
}

bool Chest::use(Player *player, int attackDir)
{
	player->game->setMenu(new ContainerMenu(player, "Chest", inventory));

	return true;
}
