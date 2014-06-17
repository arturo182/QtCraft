#include "furnace.h"

#include <screen/craftingmenu.h>
#include <crafting/crafting.h>
#include <entity/player.h>
#include <gfx/color.h>
#include <game.h>

Furnace::Furnace() :
	Furniture("Furnace")
{
	col = Color::get(-1, 0, 222, 333);
	sprite = 3;
	xr = 3;
	yr = 2;
}

bool Furnace::use(Player *player, int attackDir)
{
	player->game->setMenu(new CraftingMenu(Crafting::furnaceRecipes, player));
	return true;
}
