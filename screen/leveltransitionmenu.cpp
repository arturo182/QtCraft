#include "leveltransitionmenu.h"

#include <gfx/screen.h>
#include <game.h>

LevelTransitionMenu::LevelTransitionMenu(int dir) :
	m_time(0)
{
	m_dir = dir;
}

void LevelTransitionMenu::tick()
{
	m_time += 2;

	if(m_time == 30) {
		game->changeLevel(m_dir);
	}

	if(m_time == 60) {
		game->setMenu(0);

		//delete this;
	}
}

void LevelTransitionMenu::render(Screen *screen)
{
	for(int x = 0; x < 20; ++x) {
		for(int y = 0; y < 15; ++y) {
			int dd = (y + x % 2 * 2 + x / 3) - m_time;
			if(dd < 0 && dd > -30) {
				if(m_dir > 0) {
					screen->render(x * 8, y * 8, 0, 0, 0);
				} else {
					screen->render(x * 8, screen->h - y * 8 - 8, 0, 0, 0);
				}
			}
		}
	}
}
