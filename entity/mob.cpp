#include "mob.h"

#include <entity/particle/textparticle.h>
#include <level/tile/tile.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/color.h>
#include <sound.h>

Mob::Mob() :
	hurtTime(0),
	maxHealth(10),
	health(maxHealth),
	swimTimer(0),
	tickTime(0),
	dir(0),
	walkDist(0),
	xKnockback(0),
	yKnockback(0)
{
	x = 8;
	y = 8;
	xr = 4;
	yr = 3;
}

void Mob::tick()
{
	++tickTime;

	if(level->getTile(x >> 4, y >> 4) == Tile::lava) {
		hurt(this, 4, dir ^ 0x1);
	}

	if(health <= 0) {
		die();
	}

	if(hurtTime > 0) {
		--hurtTime;
	}
}

void Mob::hurt(Mob *mob, int dmg, int attackDir)
{
	doHurt(dmg, attackDir);
}

void Mob::hurt(Tile *tile, int x, int y, int dmg)
{
	int attackDir = dir ^ 0x1;
	doHurt(dmg, attackDir);
}

void Mob::heal(int heal)
{
	if(hurtTime > 0) {
		return;
	}

	level->add(new TextParticle(heal, x, y, Color::get(-1, 50, 50, 50)));
	health += heal;

	if(health > maxHealth) {
		health = maxHealth;
	}
}

bool Mob::move(int xa, int ya)
{
	if((isSwimming()) && (++swimTimer % 2 == 0)) {
		return true;
	}

	if(xKnockback < 0) {
		move2(-1, 0);
		xKnockback += 1;
	}

	if(xKnockback > 0) {
		move2(1, 0);
		xKnockback -= 1;
	}

	if(yKnockback < 0) {
		move2(0, -1);
		yKnockback += 1;
	}

	if(yKnockback > 0) {
		move2(0, 1);
		yKnockback -= 1;
	}

	if(hurtTime > 0) {
		return true;
	}

	if((xa != 0) || (ya != 0)) {
		++walkDist;

		if(xa < 0) dir = 2;
		if(xa > 0) dir = 3;
		if(ya < 0) dir = 1;
		if(ya > 0) dir = 0;
	}

	return Entity::move(xa, ya);
}

bool Mob::findStartPos(Level *level)
{
	int x = qrand() % level->w;
	int y = qrand() % level->h;
	int xx = x * 16 + 8;
	int yy = y * 16 + 8;

	if(level->player) {
		int xd = level->player->x - xx;
		int yd = level->player->y - yy;

		if(xd * xd + yd * yd < 6400) {
			return false;
		}
	}

	int r = level->monsterDensity * 16;
	if(level->getEntities(xx - r, yy - r, xx + r, yy + r).size() > 0) {
		return false;
	}

	if(level->getTile(x, y)->mayPass(level, x, y, this)) {
		this->x = xx;
		this->y = yy;

		return true;
	}

	return false;
}

bool Mob::blocks(Entity *e)
{
	return e->isBlockableBy(this);
}

void Mob::doHurt(int dmg, int attackDir)
{
	if(hurtTime > 0) {
		return;
	}

	if(level->player) {
		int xd = level->player->x - x;
		int yd = level->player->y - y;

		if(xd * xd + yd * yd < 6400) {
			Sound::monsterHurt->play();
		}
	}

	level->add(new TextParticle(dmg, x, y, Color::get(-1, 500, 500, 500)));
	health -= dmg;

	if(attackDir == 0) {
		yKnockback = 6;
	}

	if(attackDir == 1) {
		yKnockback = -6;
	}

	if(attackDir == 2) {
		xKnockback = -6;
	}

	if(attackDir == 3) {
		xKnockback = 6;
	}

	hurtTime = 10;
}

bool Mob::isSwimming()
{
	Tile *tile = level->getTile(x >> 4, y >> 4);

	return (tile == Tile::water) || (tile == Tile::lava);
}

void Mob::die()
{
	remove();
}
