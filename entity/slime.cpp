#include "slime.h"

#include <entity/itementity.h>
#include <item/resourceitem.h>
#include <entity/player.h>
#include <item/resource.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

Slime::Slime(int lvl) :
	m_xa(0),
	m_ya(0),
	m_jumpTime(0)
{
	m_lvl = lvl;
	x = qrand() % (64 * 16);
	y = qrand() % (64 * 16);

	maxHealth = lvl * lvl * 5;
	health = maxHealth;
}

void Slime::tick()
{
	Mob::tick();

	int speed = 1;
	if(!move(m_xa * speed, m_ya * speed) || (qrand() % 40 == 0)) {
		if(m_jumpTime <= -10) {
			m_xa = qrand() % 3 - 1;
			m_ya = qrand() % 3 - 1;

			if(level->player) {
				int xd = level->player->x - x;
				int yd = level->player->y - y;

				if(xd * xd + yd * yd < 50 * 50) {
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

			if((m_xa != 0) || (m_ya != 0)) {
				m_jumpTime = 10;
			}
		}
	}

	--m_jumpTime;
	if(m_jumpTime == 0) {
		m_xa = m_ya = 0;
	}
}

void Slime::render(Screen *screen)
{
	int xt = 0;
	int yt = 18;

	int xo = x - 8;
	int yo = y - 11;

	if(m_jumpTime > 0) {
		xt += 2;
		yo -= 4;
	}

	int col = Color::get(-1, 10, 252, 555);
	if(m_lvl == 2) {
		col = Color::get(-1, 100, 522, 555);
	}

	if(m_lvl == 3) {
		col = Color::get(-1, 111, 444, 555);
	}

	if(m_lvl == 4) {
		col = Color::get(-1, 000, 111, 224);
	}

	if(hurtTime > 0) {
		col = Color::get(-1, 555, 555, 555);
	}

	screen->render(xo + 0, yo + 0, xt + yt * 32, col, 0);
	screen->render(xo + 8, yo + 0, xt + 1 + yt * 32, col, 0);
	screen->render(xo + 0, yo + 8, xt + (yt + 1) * 32, col, 0);
	screen->render(xo + 8, yo + 8, xt + 1 + (yt + 1) * 32, col, 0);
}

void Slime::die()
{
	Mob::die();

	int count = qrand() % 2 + 1;
	for(int i = 0; i < count; ++i) {
		level->add(new ItemEntity(new ResourceItem(Resource::slime), x + qrand() % 11 - 5, y + qrand() % 11 - 5));
	}

	if(level->player) {
		level->player->score += 25 * m_lvl;
	}
}

void Slime::touchedBy(Entity *entity)
{
	Player *player = dynamic_cast<Player*>(entity);
	if(player) {
		entity->hurt(this, m_lvl, dir);
	}
}
