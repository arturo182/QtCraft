#ifndef CRAFTINGMENU_H
#define CRAFTINGMENU_H

#include <screen/menu.h>

#include <QList>

class Player;
class Recipe;

class CraftingMenu : public Menu
{
	public:
		CraftingMenu(QList<Recipe*> recipes, Player *player);

		void tick();
		void render(Screen *screen);

	private:
		Player *m_player;
		QList<Recipe*> m_recipes;
		int m_selected;
};

#endif
