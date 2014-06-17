#include "smashparticle.h"

#include <gfx/screen.h>
#include <gfx/color.h>
#include <sound.h>

SmashParticle::SmashParticle(int x, int y) :
	m_time(0)
{
	this->x = x;
	this->y = y;

	Sound::monsterHurt->play();
}

void SmashParticle::tick()
{
	++m_time;

	if(m_time > 10) {
		remove();
	}
}

void SmashParticle::render(Screen *screen)
{
	int col = Color::get(-1, 555, 555, 555);
	screen->render(x - 8, y - 8, 389, col, 2);
	screen->render(x - 0, y - 8, 389, col, 3);
	screen->render(x - 8, y - 0, 389, col, 0);
	screen->render(x - 0, y - 0, 389, col, 1);
}
