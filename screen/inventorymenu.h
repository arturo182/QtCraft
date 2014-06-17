#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include <screen/menu.h>

class Player;

class InventoryMenu : public Menu
{
	public:
		InventoryMenu(Player *player);

		void tick();
		void render(Screen *screen);

	private:
		Player *m_player;
		int m_selected;
};

#endif
