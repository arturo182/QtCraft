#ifndef SLIME_H
#define SLIME_H

#include <entity/mob.h>

class Slime : public Mob
{
	public:
		Slime(int lvl);

		void tick();
		void render(Screen *screen);

	protected:
		void die();
		void touchedBy(Entity *entity);

	private:
		int m_xa;
		int m_ya;
		int m_jumpTime;
		int m_lvl;
};

#endif
