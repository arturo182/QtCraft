#include "containermenu.h"

#include <entity/inventory.h>
#include <entity/player.h>
#include <inputhandler.h>
#include <gfx/screen.h>
#include <item/item.h>
#include <game.h>

ContainerMenu::ContainerMenu(Player *player, QString title, Inventory *container) :
	m_selected(0),
	m_oSelected(0),
	m_window(0)
{
	m_player = player;
	m_title = title;
	m_container = container;
}

void ContainerMenu::tick()
{
	if(input->menu->clicked) {
		game->setMenu(0);
	}

	if(input->left->clicked) {
		m_window = 0;

		int tmp = m_selected;
		m_selected = m_oSelected;
		m_oSelected = tmp;
	}

	if(input->right->clicked) {
		m_window = 1;

		int tmp = m_selected;
		m_selected = m_oSelected;
		m_oSelected = tmp;
	}

	Inventory *i =  (m_window == 1) ? m_player->inventory : m_container;
	Inventory *i2 = (m_window == 0) ? m_player->inventory : m_container;

	int len = i->items.size();
	if(m_selected < 0) {
		m_selected = 0;
	}

	if(m_selected >= len) {
		m_selected = (len - 1);
	}

	if(input->up->clicked) {
		m_selected -= 1;
	}

	if(input->down->clicked) {
		m_selected += 1;
	}

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
		i2->add(m_oSelected, i->items.takeAt(m_selected));

		if(m_selected >= i->items.size()) {
			m_selected = (i->items.size() - 1);
		}
	}
}

void ContainerMenu::render(Screen *screen)
{
	if(m_window == 1) {
		screen->setOffset(48, 0);
	}

	Font::renderFrame(screen, m_title, 1, 1, 12, 11);
	renderItemList<Item>(screen, 1, 1, 12, 11, m_container->items, (m_window == 0) ? m_selected : -m_oSelected - 1);

	Font::renderFrame(screen, "inventory", 13, 1, 24, 11);
	renderItemList<Item>(screen, 13, 1, 24, 11, m_player->inventory->items, (m_window == 1) ? m_selected : -m_oSelected - 1);

	screen->setOffset(0, 0);
}
