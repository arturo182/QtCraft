#include "craftingmenu.h"

#include <item/resourceitem.h>
#include <entity/inventory.h>
#include <crafting/recipe.h>
#include <entity/player.h>
#include <inputhandler.h>
#include <gfx/screen.h>
#include <sound.h>
#include <game.h>

bool recipeSorter(Recipe *r1, Recipe *r2)
{
	if(r1->canCraft && !r2->canCraft) {
		return true;
	} else if(!r1->canCraft && r2->canCraft) {
		return false;
	} else {
		return r1->resultTemplate->getName() < r2->resultTemplate->getName();
	}
}

CraftingMenu::CraftingMenu(QList<Recipe *> recipes, Player *player) :
	m_selected(0)
{
	m_player = player;
	m_recipes = QList<Recipe*>(recipes);

	for(int i = 0; i < recipes.size(); ++i) {
		m_recipes[i]->checkCanCraft(player);
	}

	qSort(m_recipes.begin(), m_recipes.end(), recipeSorter);
}

void CraftingMenu::tick()
{
	if(input->menu->clicked) {
		game->setMenu(0);
		//delete this;
	}

	if(input->up->clicked) {
		m_selected -= 1;
	}

	if(input->down->clicked) {
		m_selected += 1;
	}

	int len = m_recipes.size();
	if(len == 0) {
		m_selected = 0;
	}

	if(m_selected < 0) {
		m_selected += len;
	}

	if(m_selected >= len) {
		m_selected -= len;
	}

	if((input->attack->clicked) && (len > 0)) {
		Recipe *r = m_recipes[m_selected];
		r->checkCanCraft(m_player);

		if(r->canCraft) {
			r->deductCost(m_player);
			r->craft(m_player);

			Sound::craft->play();
		}

		for(int i = 0; i < m_recipes.size(); ++i) {
			m_recipes[i]->checkCanCraft(m_player);
		}
	}
}

void CraftingMenu::render(Screen *screen)
{
	Font::renderFrame(screen, "Have", 12, 1, 19, 3);
	Font::renderFrame(screen, "Cost", 12, 4, 19, 11);
	Font::renderFrame(screen, "Crafting", 0, 1, 11, 11);

	renderItemList<Recipe>(screen, 0, 1, 11, 11, m_recipes, m_selected);

	if(m_recipes.size() > 0) {
		Recipe *recipe = m_recipes[m_selected];
		int hasResultItems = m_player->inventory->count(recipe->resultTemplate);
		int xo = 104;

		screen->render(xo, 16, recipe->resultTemplate->getSprite(), recipe->resultTemplate->getColor(), 0);
		Font::draw(hasResultItems, screen, xo + 8, 16, Color::get(-1, 555, 555, 555));

		QVector<Item*> costs = recipe->costs;
		for(int i = 0; i < costs.size(); ++i) {
			Item *item = costs[i];

			int yo = (5 + i) * 8;
			screen->render(xo, yo, item->getSprite(), item->getColor(), 0);

			int requiredAmt = 1;
			if(ResourceItem *ri = dynamic_cast<ResourceItem*>(item)) {
				requiredAmt = ri->count;
			}

			int has = m_player->inventory->count(item);
			int color = Color::get(-1, 555, 555, 555);
			if(has < requiredAmt) {
				color = Color::get(-1, 222, 222, 222);
			}

			if(has > 99) {
				has = 99;
			}

			Font::draw(QString("%1/%2").arg(requiredAmt).arg(has), screen, xo + 8, yo, color);
		}
	}
}
