#include "anvil.h"

#include <screen/craftingmenu.h>
#include <crafting/crafting.h>
#include <entity/player.h>
#include <gfx/color.h>
#include <game.h>

Anvil::Anvil() :
	Furniture("Anvil")
{
	col = Color::get(-1, 0, 111, 222);
	sprite = 0;
	xr = 3;
	yr = 2;
}

bool Anvil::use(Player *player, int attackDir)
{
	player->game->setMenu(new CraftingMenu(Crafting::anvilRecipes, player));

	return true;
}
