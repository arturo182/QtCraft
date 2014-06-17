#include "entity.h"

#include <level/tile/tile.h>
#include <level/level.h>
#include <item/item.h>

#include <QDebug>

Entity::Entity() :
	x(0),
	y(0),
	xr(6),
	yr(6),
	removed(false),
	level(0)
{
}

void Entity::remove()
{
	removed = true;
}

void Entity::init(Level *level)
{
	this->level = level;
}

bool Entity::intersects(int x0, int y0, int x1, int y1)
{
	return (x + xr >= x0) && (y + yr >= y0) && (x - xr <= x1) && (y - yr <= y1);
}

bool Entity::blocks(Entity *e)
{
	return false;
}

bool Entity::isBlockableBy(Mob *mob)
{
	return true;
}

bool Entity::canSwim()
{
	return false;
}

bool Entity::interact(Player *player, Item *item, int attackDir)
{
	return item->interact(player, this, attackDir);
}

bool Entity::use(Player *player, int attackDir)
{
	return false;
}

int Entity::getLightRadius()
{
	return 0;
}

bool Entity::move(int xa, int ya)
{
	if((xa != 0) || (ya != 0)) {
		bool stopped = true;

		if((xa != 0) && (move2(xa, 0))) {
			stopped = false;
		}

		if((ya != 0) && (move2(0, ya))) {
			stopped = false;
		}

		if(!stopped) {
			int xt = x >> 4;
			int yt = y >> 4;

			level->getTile(xt, yt)->steppedOn(level, xt, yt, this);
		}

		return !stopped;
	}

	return true;
}

bool Entity::move2(int xa, int ya)
{
	if((xa != 0) && (ya != 0)) {
		qDebug() << "Move2 can only move along one axis at a time!";
	}

	int xto0 = (x - xr) >> 4;
	int yto0 = (y - yr) >> 4;
	int xto1 = (x + xr) >> 4;
	int yto1 = (y + yr) >> 4;

	int xt0 = (x + xa - xr) >> 4;
	int yt0 = (y + ya - yr) >> 4;
	int xt1 = (x + xa + xr) >> 4;
	int yt1 = (y + ya + yr) >> 4;

	bool blocked = false;
	for(int yt = yt0; yt <= yt1; ++yt) {
		for(int xt = xt0; xt <= xt1; ++xt) {
			if((xt < xto0) || (xt > xto1) || (yt < yto0) || (yt > yto1)) {
				level->getTile(xt, yt)->bumpedInto(level, xt, yt, this);

				if(!level->getTile(xt, yt)->mayPass(level, xt, yt, this)) {
					blocked = true;
					return false;
				}
			}
		}
	}

	if(blocked) {
		return false;
	}

	QList<Entity*> wasInside = level->getEntities(x - xr, y - yr, x + xr, y + yr);
	QList<Entity*> isInside = level->getEntities(x + xa - xr, y + ya - yr, x + xa + xr, y + ya + yr);

	for(int i = 0; i < isInside.size(); ++i) {
		Entity *e = isInside[i];

		if(e != this) {
			e->touchedBy(this);
		}
	}

	foreach(Entity *entity, wasInside) {
		isInside.removeAll(entity);
	}

	for(int i = 0; i < isInside.size(); ++i) {
		Entity *e = isInside[i];

		if(e != this) {
			if(e->blocks(this)) {
				return false;
			}
		}
	}

	x += xa;
	y += ya;

	return true;
}
