#ifndef CONTAINERMENU_H
#define CONTAINERMENU_H

#include <screen/menu.h>

class Inventory;
class Player;

class ContainerMenu : public Menu
{
	public:
		ContainerMenu(Player *player, QString title, Inventory *container);

		void tick();
		void render(Screen *screen);

	private:
		Player *m_player;
		Inventory *m_container;
		int m_selected;
		QString m_title;
		int m_oSelected;
		int m_window;
};

#endif
