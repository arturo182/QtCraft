#ifndef INSTRUCTIONSMENU_H
#define INSTRUCTIONSMENU_H

#include <screen/menu.h>

class InstructionsMenu : public Menu
{
	public:
		InstructionsMenu();

		void tick();
		void render(Screen *screen);

};

#endif
