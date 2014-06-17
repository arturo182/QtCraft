#include "oven.h"

#include <screen/craftingmenu.h>
#include <crafting/crafting.h>
#include <entity/player.h>
#include <gfx/color.h>
#include <game.h>

Oven::Oven() :
	Furniture("Oven")
{
	col = Color::get(-1, 0, 332, 442);
	sprite = 2;
	xr = 3;
	yr = 2;
}

bool Oven::use(Player *player, int attackDir)
{
	player->game->setMenu(new CraftingMenu(Crafting::ovenRecipes, player));

	return true;
}
