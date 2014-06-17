#include "crafting.h"

#include <crafting/furniturerecipe.h>
#include <crafting/resourcerecipe.h>
#include <crafting/toolrecipe.h>
#include <entity/workbench.h>
#include <entity/furnace.h>
#include <entity/lantern.h>
#include <item/resource.h>
#include <item/tooltype.h>
#include <entity/anvil.h>
#include <entity/chest.h>
#include <entity/oven.h>

#include <QList>

QList<Recipe*> Crafting::anvilRecipes;
QList<Recipe*> Crafting::ovenRecipes;
QList<Recipe*> Crafting::furnaceRecipes;
QList<Recipe*> Crafting::workbenchRecipes;
bool Crafting::listsInitialized = false;

void Crafting::init()
{
	if(!listsInitialized) {
		workbenchRecipes.append((new FurnitureRecipe<Lantern>())->addCost(Resource::wood, 5)->addCost(Resource::slime, 10)->addCost(Resource::glass, 4));
		workbenchRecipes.append((new FurnitureRecipe<Oven>())->addCost(Resource::stone, 15));
		workbenchRecipes.append((new FurnitureRecipe<Furnace>())->addCost(Resource::stone, 20));
		workbenchRecipes.append((new FurnitureRecipe<Workbench>())->addCost(Resource::wood, 20));
		workbenchRecipes.append((new FurnitureRecipe<Chest>())->addCost(Resource::wood, 20));
		workbenchRecipes.append((new FurnitureRecipe<Anvil>())->addCost(Resource::ironIngot, 5));

		workbenchRecipes.append((new ToolRecipe(ToolType::sword,   0))->addCost(Resource::wood, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::axe,     0))->addCost(Resource::wood, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::hoe,     0))->addCost(Resource::wood, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::pickaxe, 0))->addCost(Resource::wood, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::shovel,  0))->addCost(Resource::wood, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::sword,   1))->addCost(Resource::wood, 5)->addCost(Resource::stone, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::axe,     1))->addCost(Resource::wood, 5)->addCost(Resource::stone, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::hoe,     1))->addCost(Resource::wood, 5)->addCost(Resource::stone, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::pickaxe, 1))->addCost(Resource::wood, 5)->addCost(Resource::stone, 5));
		workbenchRecipes.append((new ToolRecipe(ToolType::shovel,  1))->addCost(Resource::wood, 5)->addCost(Resource::stone, 5));

		anvilRecipes.append((new ToolRecipe(ToolType::sword,   2))->addCost(Resource::wood, 5)->addCost(Resource::ironIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::axe,     2))->addCost(Resource::wood, 5)->addCost(Resource::ironIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::hoe,     2))->addCost(Resource::wood, 5)->addCost(Resource::ironIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::pickaxe, 2))->addCost(Resource::wood, 5)->addCost(Resource::ironIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::shovel,  2))->addCost(Resource::wood, 5)->addCost(Resource::ironIngot, 5));

		anvilRecipes.append((new ToolRecipe(ToolType::sword,   3))->addCost(Resource::wood, 5)->addCost(Resource::goldIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::axe,     3))->addCost(Resource::wood, 5)->addCost(Resource::goldIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::hoe,     3))->addCost(Resource::wood, 5)->addCost(Resource::goldIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::pickaxe, 3))->addCost(Resource::wood, 5)->addCost(Resource::goldIngot, 5));
		anvilRecipes.append((new ToolRecipe(ToolType::shovel,  3))->addCost(Resource::wood, 5)->addCost(Resource::goldIngot, 5));

		anvilRecipes.append((new ToolRecipe(ToolType::sword,   4))->addCost(Resource::wood, 5)->addCost(Resource::gem, 50));
		anvilRecipes.append((new ToolRecipe(ToolType::axe,     4))->addCost(Resource::wood, 5)->addCost(Resource::gem, 50));
		anvilRecipes.append((new ToolRecipe(ToolType::hoe,     4))->addCost(Resource::wood, 5)->addCost(Resource::gem, 50));
		anvilRecipes.append((new ToolRecipe(ToolType::pickaxe, 4))->addCost(Resource::wood, 5)->addCost(Resource::gem, 50));
		anvilRecipes.append((new ToolRecipe(ToolType::shovel,  4))->addCost(Resource::wood, 5)->addCost(Resource::gem, 50));

		furnaceRecipes.append((new ResourceRecipe(Resource::ironIngot))->addCost(Resource::ironOre, 4)->addCost(Resource::coal, 1));
		furnaceRecipes.append((new ResourceRecipe(Resource::goldIngot))->addCost(Resource::goldOre, 4)->addCost(Resource::coal, 1));
		furnaceRecipes.append((new ResourceRecipe(Resource::glass    ))->addCost(Resource::sand,    4)->addCost(Resource::coal, 1));

		ovenRecipes.append((new ResourceRecipe(Resource::bread))->addCost(Resource::wheat, 4));

		listsInitialized = true;
	}
}
