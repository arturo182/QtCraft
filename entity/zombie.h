#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <entity/mob.h>

class Zombie : public Mob
{
	public:
		Zombie(int lvl);

		void tick();
		void render(Screen *screen);

	private:
		void touchedBy(Entity *entity);
		void die();

	private:
		int m_xa;
		int m_ya;
		int m_lvl;
		int m_randomWalkTime;
};

#endif
