#ifndef LEVELTRANSITIONMENU_H
#define LEVELTRANSITIONMENU_H

#include <screen/menu.h>

class LevelTransitionMenu : public Menu
{
	public:
		LevelTransitionMenu(int dir);

		void tick();
		void render(Screen *screen);

	private:
		int m_dir;
		int m_time;
};

#endif
