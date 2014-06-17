#ifndef DEADMENU_H
#define DEADMENU_H

#include <screen/menu.h>

class DeadMenu : public Menu
{
	public:
		DeadMenu();

		void tick();
		void render(Screen *screen);

	private:
		int m_inputDelay;
};

#endif
