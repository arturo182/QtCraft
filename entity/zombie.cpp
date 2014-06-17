#include "zombie.h"

#include <item/resourceitem.h>
#include <entity/itementity.h>
#include <item/resource.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

Zombie::Zombie(int lvl) :
	m_xa(0),
	m_ya(0),
	m_randomWalkTime(0)
{
	m_lvl = lvl;

	x = qrand() % 1024;
	y = qrand() % 1024;

	maxHealth = lvl * lvl * 10;
	health = maxHealth;
}

void Zombie::tick()
{
	Mob::tick();

	if(level->player && (m_randomWalkTime == 0)) {
		int xd = level->player->x - x;
		int yd = level->player->y - y;

		if(xd * xd + yd * yd < 2500) {
			m_xa = 0;
			m_ya = 0;

			if(xd < 0) m_xa = -1;
			if(xd > 0) m_xa = 1;
			if(yd < 0) m_ya = -1;
			if(yd > 0) m_ya = 1;
		}
	}

	int speed = tickTime & 0x1;

	if((!move(m_xa * speed, m_ya * speed)) || (qrand() % 200 == 0)) {
		m_randomWalkTime = 60;
		m_xa = ((qrand() % 3 - 1) * qrand() % 2);
		m_ya = ((qrand() % 3 - 1) * qrand() % 2);
	}

	if(m_randomWalkTime > 0) {
		m_randomWalkTime -= 1;
	}
}

void Zombie::render(Screen *screen)
{
	int xt = 0;
	int yt = 14;

	int flip1 = walkDist >> 3 & 0x1;
	int flip2 = walkDist >> 3 & 0x1;

	if(dir == 1) {
		xt += 2;
	}

	if(dir > 1) {
		flip1 = 0;
		flip2 = walkDist >> 4 & 0x1;

		if(dir == 2) {
			flip1 = 1;
		}

		xt += 4 + (walkDist >> 3 & 0x1) * 2;
	}

	int xo = x - 8;
	int yo = y - 11;

	int col = Color::get(-1, 10, 252, 40);
	if(m_lvl == 2) {
		col = Color::get(-1, 100, 522, 40);
	}

	if(m_lvl == 3) {
		col = Color::get(-1, 111, 444, 40);
	}

	if(m_lvl == 4) {
		col = Color::get(-1, 0, 111, 16);
	}

	if(hurtTime > 0) {
		col = Color::get(-1, 555, 555, 555);
	}

	screen->render(xo + 8 * flip1, yo + 0, xt + yt * 32, col, flip1);
	screen->render(xo + 8 - 8 * flip1, yo + 0, xt + 1 + yt * 32, col, flip1);
	screen->render(xo + 8 * flip2, yo + 8, xt + (yt + 1) * 32, col, flip2);
	screen->render(xo + 8 - 8 * flip2, yo + 8, xt + 1 + (yt + 1) * 32, col, flip2);
}

void Zombie::touchedBy(Entity *entity)
{
	Player *player = dynamic_cast<Player*>(entity);
	if(player) {
		entity->hurt(this, m_lvl + 1, dir);
	}
}

void Zombie::die()
{
	Mob::die();

	int count = qrand() % 2 + 1;
	for(int i = 0; i < count; ++i) {
		level->add(new ItemEntity(new ResourceItem(Resource::cloth), x + qrand() % 11 - 5, y + qrand() % 11 - 5));
	}

	if(level->player) {
		level->player->score += 50 * m_lvl;
	}
}
