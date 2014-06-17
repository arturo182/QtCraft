#include "airwizard.h"

#include <entity/player.h>
#include <entity/spark.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <sound.h>

#include <qmath.h>

AirWizard::AirWizard() :
	m_xa(0),
	m_ya(0),
	m_randomWalkTime(0),
	m_attackDelay(0),
	m_attackTime(0),
	m_attackType(0)
{
	x = qrand() % (64 * 16);
	y = qrand() % (64 * 16);

	maxHealth = 2000;
	health = maxHealth;
}

void AirWizard::tick()
{
	Mob::tick();

	if(m_attackDelay > 0) {
		dir = (m_attackDelay - 45) / 4 % 4;
		dir = (dir * 2 % 4) + (dir / 2);

		if(m_attackDelay < 45) {
			dir = 0;
		}

		--m_attackDelay;

		if(m_attackDelay == 0) {
			m_attackType = 0;

			if(health < 1000) {
				m_attackType = 1;
			}

			if(health < 200) {
				m_attackType = 2;
			}

			m_attackTime = 60 * 2;
		}

		return;
	}

	if(m_attackTime > 0) {
		--m_attackTime;

		double dir = m_attackTime * 0.25 * (m_attackTime % 2 * 2 - 1);
		double speed = 0.7 + m_attackType * 0.2;

		level->add(new Spark(this, qCos(dir) * speed, qSin(dir) * speed));
		return;
	}

	if(level->player && (m_randomWalkTime == 0)) {
		int xd = level->player->x - x;
		int yd = level->player->y - y;

		if(xd * xd + yd * yd < 32 * 32) {
			m_xa = 0;
			m_ya = 0;

			if(xd < 0) {
				m_xa = +1;
			}

			if(xd > 0) {
				m_xa = -1;
			}
			if(yd < 0) {
				m_ya = +1;
			}

			if(yd > 0) {
				m_ya = -1;
			}
		} else if (xd * xd + yd * yd > 80 * 80) {
			m_xa = 0;
			m_ya = 0;

			if(xd < 0) {
				m_xa = -1;
			}

			if(xd > 0) {
				m_xa = +1;
			}

			if(yd < 0) {
				m_ya = -1;
			}

			if(yd > 0) {
				m_ya = +1;
			}
		}
	}

	int speed = (tickTime % 4) == 0 ? 0 : 1;
	if(!move(m_xa * speed, m_ya * speed) || (qrand() % 100 == 0)) {
		m_randomWalkTime = 30;

		m_xa = qrand() % 3 - 1;
		m_ya = qrand() % 3 - 1;
	}

	if(m_randomWalkTime > 0) {
		--m_randomWalkTime;

		if(level->player && (m_randomWalkTime == 0)) {
			int xd = level->player->x - x;
			int yd = level->player->y - y;

			if((qrand() % 4 == 0) && (xd * xd + yd * yd < 50 * 50)) {
				if((m_attackDelay == 0) && (m_attackTime == 0)) {
					m_attackDelay = 60 * 2;
				}
			}
		}
	}
}

void AirWizard::render(Screen *screen)
{
	int xt = 8;
	int yt = 14;

	int flip1 = (walkDist >> 3) & 1;
	int flip2 = (walkDist >> 3) & 1;

	if(dir == 1) {
		xt += 2;
	}

	if(dir > 1) {
		flip1 = 0;
		flip2 = ((walkDist >> 4) & 1);

		if(dir == 2) {
			flip1 = 1;
		}

		xt += 4 + ((walkDist >> 3) & 1) * 2;
	}

	int xo = x - 8;
	int yo = y - 11;

	int col1 = Color::get(-1, 100, 500, 555);
	int col2 = Color::get(-1, 100, 500, 532);
	if(health < 200) {
		if(tickTime / 3 % 2 == 0) {
			col1 = Color::get(-1, 500, 100, 555);
			col2 = Color::get(-1, 500, 100, 532);
		}
	} else if(health < 1000) {
		if(tickTime / 5 % 4 == 0) {
			col1 = Color::get(-1, 500, 100, 555);
			col2 = Color::get(-1, 500, 100, 532);
		}
	}

	if(hurtTime > 0) {
		col1 = Color::get(-1, 555, 555, 555);
		col2 = Color::get(-1, 555, 555, 555);
	}

	screen->render(xo + 8 * flip1, yo + 0, xt + yt * 32, col1, flip1);
	screen->render(xo + 8 - 8 * flip1, yo + 0, xt + 1 + yt * 32, col1, flip1);
	screen->render(xo + 8 * flip2, yo + 8, xt + (yt + 1) * 32, col2, flip2);
	screen->render(xo + 8 - 8 * flip2, yo + 8, xt + 1 + (yt + 1) * 32, col2, flip2);
}

void AirWizard::touchedBy(Entity *entity)
{
	Player *player = dynamic_cast<Player*>(entity);
	if(player) {
		entity->hurt(this, 3, dir);
	}
}

void AirWizard::doHurt(int dmg, int attackDir)
{
	Mob::doHurt(dmg, attackDir);

	if((m_attackDelay == 0) && (m_attackTime == 0)) {
		m_attackDelay = 60 * 2;
	}
}

void AirWizard::die()
{
	Mob::die();

	if(level->player) {
		level->player->score += 1000;
		level->player->gameWon();
	}

	Sound::bossdeath->play();
}
