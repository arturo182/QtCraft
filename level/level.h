#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>

class Entity;
class Player;
class Screen;
class Tile;

class Level
{
	public:
		Level(int w, int h, int level, Level *parentLevel);

		void add(Entity *entity);
		void remove(Entity *entity);
		void trySpawn(int count);
		void tick();

		void renderBackground(Screen *screen, int xScroll, int yScroll);
		void renderSprites(Screen *screen, int xScroll, int yScroll);
		void renderLight(Screen *screen, int xScroll, int yScroll);

		void setTile(int x, int y, Tile *t, qint8 dataVal);
		Tile *getTile(int x, int y);

		void setData(int x, int y, int val);
		int getData(int x, int y) const;

		QList<Entity*> getEntities(int x0, int y0, int x1, int y1);

	public:
		int w;
		int h;
		QVector<qint8> tiles;
		QVector<qint8> data;
		QVector<QVector<Entity*> > entitiesInTiles;
		int grassColor;
		int dirtColor;
		int sandColor;
		int monsterDensity;
		QList<Entity*> entities;
		Player *player;

	private:
		void sortAndRender(Screen *screen, QList<Entity*> list);

		void insertEntity(int x, int y, Entity *entity);
		void removeEntity(int x, int y, Entity *entity);

	private:
		int m_depth;
		QList<Entity*> m_rowSprites;

};

#endif
