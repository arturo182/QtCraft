#ifndef SMASHPARTICLE_H
#define SMASHPARTICLE_H

#include <entity/entity.h>

class SmashParticle : public Entity
{
	public:
		SmashParticle(int x, int y);

		void tick();
		void render(Screen *screen);

	private:
		int m_time;
};

#endif
