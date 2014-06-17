#include "workbench.h"

#include <screen/craftingmenu.h>
#include <crafting/crafting.h>
#include <entity/player.h>
#include <gfx/color.h>
#include <game.h>

Workbench::Workbench() :
	Furniture("Workbench")
{
	col = Color::get(-1, 100, 321, 431);
	sprite = 4;
	xr = 3;
	yr = 2;
}

bool Workbench::use(Player *player, int attackDir)
{
	player->game->setMenu(new CraftingMenu(Crafting::workbenchRecipes, player));
	return true;
}
