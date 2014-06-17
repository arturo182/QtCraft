#ifndef AIRWIZARD_H
#define AIRWIZARD_H

#include <entity/mob.h>

class AirWizard : public Mob
{
	public:
		AirWizard();

		void tick();
		void render(Screen *screen);

		void touchedBy(Entity *entity);

	private:
		void doHurt(int dmg, int attackDir);
		void die();

	private:
		int m_xa;
		int m_ya;
		int m_randomWalkTime;
		int m_attackDelay;
		int m_attackTime;
		int m_attackType;
};

#endif
