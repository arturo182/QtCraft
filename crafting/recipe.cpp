#include "recipe.h"

#include <item/resourceitem.h>
#include <entity/inventory.h>
#include <item/resource.h>
#include <entity/player.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>

Recipe::Recipe(Item *resultTemplate) :
	canCraft(false)
{
	this->resultTemplate = resultTemplate;
}

Recipe *Recipe::addCost(Resource *resource, int count)
{
	costs.append(new ResourceItem(resource, count));

	return this;
}

void Recipe::checkCanCraft(Player *player)
{
	for(int i = 0; i < costs.size(); ++i) {
		Item *item = costs[i];

		if(ResourceItem *ri = dynamic_cast<ResourceItem*>(item)) {
			if(!player->inventory->hasResources(ri->resource, ri->count)) {
				canCraft = false;

				return;
			}
		}
	}

	canCraft = true;
}

void Recipe::deductCost(Player *player)
{
	for(int i = 0; i < costs.size(); ++i) {
		Item *item = costs[i];

		if(ResourceItem *ri = dynamic_cast<ResourceItem*>(item)) {
			player->inventory->removeResource(ri->resource, ri->count);
		}
	}
}

void Recipe::renderInventory(Screen *screen, const int &x, const int &y) const
{
	screen->render(x, y, resultTemplate->getSprite(), resultTemplate->getColor(), 0);

	int textColor = canCraft ? Color::get(-1, 555, 555, 555) : Color::get(-1, 222, 222, 222);
	Font::draw(resultTemplate->getName(), screen, x + 8, y, textColor);
}
