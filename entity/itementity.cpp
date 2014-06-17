#include "itementity.h"

#include <entity/player.h>
#include <gaussianrand.h>
#include <gfx/screen.h>
#include <item/item.h>
#include <gfx/color.h>
#include <sound.h>

#include <QDebug>

ItemEntity::ItemEntity(Item *item, int x, int y) :
	hurtTime(0),
	walkDist(0),
	dir(0),
	xKnockback(0),
	yKnockback(0),
	m_time(0)
{
	this->item = item;
	this->x = x;
	this->y = y;

	xx = x;
	yy = y;
	xr = 3;
	yr = 3;

	zz = 2.0;
	xa = (GaussianRand::next() * 0.3);
	ya = (GaussianRand::next() * 0.2);
	za = (GaussianRand::next() * 0.7 + 1.0);

	m_lifeTime = (600 + qrand() % 60);
}

void ItemEntity::tick()
{
	++m_time;

	 if(m_time >= m_lifeTime) {
	   remove();
	   return;
	 }

	 xx += xa;
	 yy += ya;
	 zz += za;

	 if(zz < 0.0) {
	   zz = 0.0;
	   za *= -0.5;
	   xa *= 0.6;
	   ya *= 0.6;
	 }

	 za -= 0.15;

	 int ox = x;
	 int oy = y;
	 int nx = xx;
	 int ny = yy;
	 int expectedx = nx - x;
	 int expectedy = ny - y;

	 move(nx - x, ny - y);

	 int gotx = x - ox;
	 int goty = y - oy;

	 xx += gotx - expectedx;
	 yy += goty - expectedy;

	 if(hurtTime > 0) {
		 --hurtTime;
	 }
}

void ItemEntity::render(Screen *screen)
{
	if((m_time >= m_lifeTime - 120) && (m_time / 6 % 2 == 0)) {
		return;
	}

	//screen->render(x - 4, y - 4, item->getSprite(), Color::get(-1, 0, 0, 0), 0);
	screen->render(x - 4, y - 4 - zz, item->getSprite(), item->getColor(), 0);
}

void ItemEntity::take(Player *player)
{
	Sound::pickup->play();

	++player->score;
	item->onTake(this);
	remove();
}

bool ItemEntity::isBlockableBy(Mob *mob)
{
	return false;
}

void ItemEntity::touchedBy(Entity *entity)
{
	if(m_time > 30) {
		entity->touchItem(this);
	}
}
