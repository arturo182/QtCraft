#ifndef SPARK_H
#define SPARK_H

#include <entity/entity.h>

class AirWizard;

class Spark : public Entity
{
	public:
		Spark(AirWizard *owner, double xa, double ya);

		void tick();
		void render(Screen *screen);

		bool isBlockableBy(Mob *mob);

	public:
		double xa;
		double ya;
		double xx;
		double yy;

	private:
		int m_lifeTime;
		int m_time;
		AirWizard *m_owner;

};

#endif
