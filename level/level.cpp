#include "level.h"

#include <level/tile/tile.h>
#include <level/levelgen.h>
#include <entity/entity.h>
#include <entity/player.h>
#include <entity/zombie.h>
#include <entity/mob.h>
#include <gfx/screen.h>

#include <QDebug>
#include <entity/slime.h>
#include <entity/airwizard.h>

Level::Level(int w, int h, int level, Level *parentLevel) :
	grassColor(141),
	dirtColor(322),
	sandColor(550),
	monsterDensity(8),
	player(0)
{
	if(level < 0) {
		dirtColor = 222;
	}

	m_depth = level;
	this->w = w;
	this->h = h;

	if(level == 1) {
		dirtColor = 444;
	}

	QVector<QVector<qint8> > maps;
	if(level == 0) {
		maps = LevelGen::createAndValidateTopMap(w, h);
	} else if(level < 0) {
		maps = LevelGen::createAndValidateUndergroundMap(w, h, -level);
		monsterDensity = 4;
	} else {
		maps = LevelGen::createAndValidateSkyMap(w, h);
		monsterDensity = 4;
	}

	tiles = maps[0];
	data = maps[1];

	if(parentLevel) {
		for(int y = 0; y < h; ++y) {
			for(int x = 0; x < w; ++x) {
				if(parentLevel->getTile(x, y) == Tile::stairsDown) {
					setTile(x, y, Tile::stairsUp, 0);
					if(level == 0) {
						setTile(x - 1, y, Tile::hardRock, 0);
						setTile(x + 1, y, Tile::hardRock, 0);
						setTile(x, y - 1, Tile::hardRock, 0);
						setTile(x, y + 1, Tile::hardRock, 0);
						setTile(x - 1, y - 1, Tile::hardRock, 0);
						setTile(x - 1, y + 1, Tile::hardRock, 0);
						setTile(x + 1, y - 1, Tile::hardRock, 0);
						setTile(x + 1, y + 1, Tile::hardRock, 0);
					} else {
						setTile(x - 1, y, Tile::dirt, 0);
						setTile(x + 1, y, Tile::dirt, 0);
						setTile(x, y - 1, Tile::dirt, 0);
						setTile(x, y + 1, Tile::dirt, 0);
						setTile(x - 1, y - 1, Tile::dirt, 0);
						setTile(x - 1, y + 1, Tile::dirt, 0);
						setTile(x + 1, y - 1, Tile::dirt, 0);
						setTile(x + 1, y + 1, Tile::dirt, 0);
					}
				}
			}
		}

	}

	entitiesInTiles = QVector<QVector<Entity*> >(w * h);
	for(int i = 0; i < w * h; ++i) {
		entitiesInTiles[i] = QVector<Entity*>();
	}

	if(level == 1) {
		AirWizard *aw = new AirWizard();
		aw->x = (w * 8);
		aw->y = (h * 8);
		add(aw);
	}
}

void Level::add(Entity *entity)
{
	if(Player *p = dynamic_cast<Player*>(entity)) {
		player = p;
	}

	entity->removed = false;
	entities.append(entity);
	entity->init(this);

	insertEntity(entity->x >> 4, entity->y >> 4, entity);
}

void Level::remove(Entity *entity)
{
	entities.removeAll(entity);

	int xto = entity->x >> 4;
	int yto = entity->y >> 4;

	removeEntity(xto, yto, entity);
}

void Level::trySpawn(int count)
{
	for(int i = 0; i < count; ++i) {
		int minLevel = 1;
		int maxLevel = 1;

		if(m_depth < 0) {
			maxLevel = -m_depth + 1;
		}

		if(m_depth > 0) {
			minLevel = 4;
			maxLevel = 4;
		}

		int lvl = qrand() % (maxLevel - minLevel + 1) + minLevel;

		Mob *mob = 0;
		if(qrand() % 2 == 0) {
			mob = new Slime(lvl);
		} else {
			mob = new Zombie(lvl);
		}

		if(mob->findStartPos(this)) {
			add(mob);
		} else {
			delete mob;
		}
	}
}

void Level::tick()
{
	trySpawn(1);

	for(int i = 0; i < w * h / 50; ++i) {
		int xt = qrand() % w;
		int yt = qrand() % w;

		getTile(xt, yt)->tick(this, xt, yt);
	}

	foreach(Entity *e, entities) {
		int xto = e->x >> 4;
		int yto = e->y >> 4;

		e->tick();

		if(e->removed) {
			entities.removeAll(e);

			removeEntity(xto, yto, e);

			//delete e;
		} else {
			int xt = e->x >> 4;
			int yt = e->y >> 4;

			if((xto != xt) || (yto != yt)) {
				removeEntity(xto, yto, e);
				insertEntity(xt, yt, e);
			}
		}
	}
}

void Level::renderBackground(Screen *screen, int xScroll, int yScroll)
{
	int xo = xScroll >> 4;
	int yo = yScroll >> 4;
	int w = (screen->w + 15) >> 4;
	int h = (screen->h + 15) >> 4;

	screen->setOffset(xScroll, yScroll);

	for(int y = yo; y <= h + yo; ++y) {
		for(int x = xo; x <= w + xo; ++x) {
			getTile(x, y)->render(screen, this, x, y);
		}
	}

	screen->setOffset(0, 0);
}

void Level::renderSprites(Screen *screen, int xScroll, int yScroll)
{
	int xo = xScroll >> 4;
	int yo = yScroll >> 4;
	int w = (screen->w + 15) >> 4;
	int h = (screen->h + 15) >> 4;

	screen->setOffset(xScroll, yScroll);

	for(int y = yo; y <= h + yo; ++y) {
		for(int x = xo; x <= w + xo; ++x) {
			if((x >= 0) && (y >= 0) && (x < this->w) && (y < this->h)) {
				m_rowSprites.append(entitiesInTiles[(x + y * this->w)].toList());
			}
		}

		if(m_rowSprites.size() > 0) {
			sortAndRender(screen, m_rowSprites);
		}

		m_rowSprites.clear();
	}

	screen->setOffset(0, 0);
}

void Level::renderLight(Screen *screen, int xScroll, int yScroll)
{
	int xo = xScroll >> 4;
	int yo = yScroll >> 4;
	int w = (screen->w + 15) >> 4;
	int h = (screen->h + 15) >> 4;

	screen->setOffset(xScroll, yScroll);

	int r = 4;
	for(int y = yo - r; y <= h + yo + r; ++y) {
		for(int x = xo - r; x <= w + xo + r; ++x) {
			if((x < 0) || (y < 0) || (x >= this->w) || (y >= this->h)) {
				continue;
			}

			QVector<Entity*> entities = entitiesInTiles[(x + y * this->w)];
			for(int i = 0; i < entities.size(); ++i) {
				Entity *e = entities[i];

				int lr = e->getLightRadius();
				if(lr > 0) {
					screen->renderLight(e->x - 1, e->y - 4, lr * 8);
				}
			}

			int lr = getTile(x, y)->getLightRadius(this, x, y);
			if(lr > 0) {
				screen->renderLight(x * 16 + 8, y * 16 + 8, lr * 8);
			}
		}
	}

	screen->setOffset(0, 0);
}

void Level::setTile(int x, int y, Tile *t, qint8 dataVal)
{
	if((x < 0) || (y < 0) || (x >= w) || (y >= h)) {
		return;
	}

	tiles[(x + y * w)] = t->id;
	data[(x + y * w)] = dataVal;
}

Tile *Level::getTile(int x, int y)
{
	if((x < 0) || (y < 0) || (x >= w) || (y >= h)) {
		return Tile::rock;
	}

	int tile = tiles[x + y * w];
	return Tile::tiles[tile];
}

void Level::setData(int x, int y, int val)
{
	if((x < 0) || (y < 0) || (x >= w) || (y >= h)) {
		return;
	}

	data[(x + y * w)] = val;
}

int Level::getData(int x, int y) const
{
	if((x < 0) || (y < 0) || (x >= w) || (y >= h)) {
		return 0;
	}

	return data[(x + y * w)] & 0xFF;
}

QList<Entity*> Level::getEntities(int x0, int y0, int x1, int y1)
{
	QList<Entity*> result;

	int xt0 = (x0 >> 4) - 1;
	int yt0 = (y0 >> 4) - 1;
	int xt1 = (x1 >> 4) + 1;
	int yt1 = (y1 >> 4) + 1;

	for(int y = yt0; y <= yt1; ++y) {
		for(int x = xt0; x <= xt1; ++x) {
			if((x >= 0) && (y >= 0) && (x < w) && (y < h)) {
				QVector<Entity*> entities = entitiesInTiles[(x + y * w)];

				for(int i = 0; i < entities.count(); ++i) {
					Entity *e = entities[i];

					if(e->intersects(x0, y0, x1, y1)) {
						result.append(e);
					}
				}
			}
		}
	}

	return result;
}

bool spriteSorter(Entity *e1, Entity *e2)
{
	return e1->y < e2->y;
}

void Level::sortAndRender(Screen *screen, QList<Entity*> list)
{
	qSort(list.begin(), list.end(), spriteSorter);

	for(int i = 0; i < list.size(); ++i) {
		list[i]->render(screen);
	}
}

void Level::insertEntity(int x, int y, Entity *entity)
{
	if((x < 0) || (y < 0) || (x >= w) || (y >= h)) {
		return;
	}

	entitiesInTiles[(x + y * w)].append(entity);
}

void Level::removeEntity(int x, int y, Entity *entity)
{
	if((x < 0) || (y < 0) || (x >= w) || (y >= h)) {
		return;
	}

	int idx = entitiesInTiles[(x + y * w)].indexOf(entity);
	if(idx > -1) {
		entitiesInTiles[(x + y * w)].remove(idx);
	}

	//delete entity;
}
