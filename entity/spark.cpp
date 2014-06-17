#include "spark.h"

#include <entity/airwizard.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

#include <qglobal.h>

Spark::Spark(AirWizard *owner, double xa, double ya) :
	m_time(0)
{
	m_owner = owner;

	this->x = owner->x;
	this->y = owner->y;
	xx = this->x;
	yy = this->y;
	xr = 0;
	yr = 0;

	this->xa = xa;
	this->ya = ya;

	m_lifeTime = 60 * 10 + qrand() % 30;
}

void Spark::tick()
{
	++m_time;

	if(m_time >= m_lifeTime) {
		remove();

		return;
	}

	xx += xa;
	yy += ya;

	x = xx;
	y = yy;

	QList<Entity*> toHit = level->getEntities(x, y, x, y);
	for (int i = 0; i < toHit.size(); ++i) {
		Entity *e = toHit[i];
		if(Mob *mob = dynamic_cast<Mob*>(e)) {
			AirWizard *wizard = dynamic_cast<AirWizard*>(e);
			if(!wizard) {
				e->hurt(m_owner, 1, mob->dir ^ 1);
			}
		}
	}
}

void Spark::render(Screen *screen)
{
	if(m_time >= m_lifeTime - 6 * 20) {
		if(m_time / 6 % 2 == 0) {
			return;
		}
	}

	int xt = 8;
	int yt = 13;

	screen->render(x - 4, y - 4 - 2, xt + yt * 32, Color::get(-1, 555, 555, 555), qrand() % 4);
	screen->render(x - 4, y - 4 + 2, xt + yt * 32, Color::get(-1, 000, 000, 000), qrand() % 4);
}

bool Spark::isBlockableBy(Mob *mob)
{
	return false;
}
