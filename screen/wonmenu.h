#ifndef WONMENU_H
#define WONMENU_H

#include <screen/menu.h>

class WonMenu : public Menu
{
	public:
		WonMenu();

		void tick();
		void render(Screen *screen);

	private:
		int m_inputDelay;
};

#endif
