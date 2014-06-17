#ifndef ABOUTMENU_H
#define ABOUTMENU_H

#include <screen/menu.h>

class AboutMenu : public Menu
{
	public:
		AboutMenu();

		void tick();
		void render(Screen *screen);

};

#endif
