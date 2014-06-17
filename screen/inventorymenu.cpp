#include "inventorymenu.h"

#include <entity/inventory.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <inputhandler.h>
#include <entity/player.h>
#include <gfx/font.h>
#include <game.h>

InventoryMenu::InventoryMenu(Player *player) :
	m_selected(0)
{
	m_player = player;

	if(player->activeItem) {
		player->inventory->add(0, player->activeItem);
		player->activeItem = 0;
	}
}

void InventoryMenu::tick()
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

	int len = m_player->inventory->items.size();
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
	  Item *item = m_player->inventory->items.takeAt(m_selected);
	  m_player->activeItem = item;
	  game->setMenu(0);

	  //delete this;
	}
}

void InventoryMenu::render(Screen *screen)
{
	Font::renderFrame(screen, "inventory", 1, 1, 12, 11);

	renderItemList<Item>(screen, 1, 1, 12, 11, m_player->inventory->items, m_selected);
}
