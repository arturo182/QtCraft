#ifndef TILE_H
#define TILE_H

#include <QVector>

class Entity;
class Player;
class Screen;
class Level;
class Item;
class Mob;

class Tile
{
	public:
		static int tickCount;
		static QVector<Tile*> tiles;
		static Tile *grass;
		static Tile *rock;
		static Tile *water;
		static Tile *flower;
		static Tile *tree;
		static Tile *dirt;
		static Tile *sand;
		static Tile *cactus;
		static Tile *hole;
		static Tile *treeSapling;
		static Tile *cactusSapling;
		static Tile *farmland;
		static Tile *wheat;
		static Tile *lava;
		static Tile *stairsDown;
		static Tile *stairsUp;
		static Tile *infiniteFall;
		static Tile *cloud;
		static Tile *hardRock;
		static Tile *ironOre;
		static Tile *goldOre;
		static Tile *gemOre;
		static Tile *cloudCactus;

		static void init();
		static void init2();

	public:
		Tile(qint8 id);

		virtual void render(Screen *screen, Level *level, int x, int y) = 0;
		virtual bool mayPass(Level *level, int x, int y, Entity *e);
		virtual int getLightRadius(Level *level, int x, int y);
		virtual void hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir) { }
		virtual void bumpedInto(Level *level, int xt, int yt, Entity *entity) { }
		virtual void tick(Level *level, int xt, int yt) { }
		virtual void steppedOn(Level *level, int xt, int yt, Entity *entity) { }
		virtual bool interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir);
		virtual bool use(Level *level, int xt, int yt, Player *player, int attackDir);
		bool connectsToLiquid() const;

	public:
		qint8 id;
		bool connectsToGrass;
		bool connectsToSand;
		bool connectsToLava;
		bool connectsToWater;

	private:
		static bool tilesInitialized;

};

#endif
