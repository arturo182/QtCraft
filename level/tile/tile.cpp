#include "tile.h"

#include <level/tile/infinitefalltile.h>
#include <level/tile/cloudcactustile.h>
#include <level/tile/hardrocktile.h>
#include <level/tile/saplingtile.h>
#include <level/tile/cactustile.h>
#include <level/tile/flowertile.h>
#include <level/tile/stairstile.h>
#include <level/tile/cloudtile.h>
#include <level/tile/grasstile.h>
#include <level/tile/watertile.h>
#include <level/tile/wheattile.h>
#include <level/tile/dirttile.h>
#include <level/tile/farmtile.h>
#include <level/tile/holetile.h>
#include <level/tile/lavatile.h>
#include <level/tile/rocktile.h>
#include <level/tile/sandtile.h>
#include <level/tile/treetile.h>
#include <level/tile/oretile.h>
#include <item/resource.h>

#include <QDebug>

bool Tile::tilesInitialized = false;
int Tile::tickCount = 0;
QVector<Tile*>Tile::tiles = QVector<Tile*>(256, 0);
Tile *Tile::grass;
Tile *Tile::rock;
Tile *Tile::water;
Tile *Tile::flower;
Tile *Tile::tree;
Tile *Tile::dirt;
Tile *Tile::sand;
Tile *Tile::cactus;
Tile *Tile::hole;
Tile *Tile::treeSapling;
Tile *Tile::cactusSapling;
Tile *Tile::farmland;
Tile *Tile::wheat;
Tile *Tile::lava;
Tile *Tile::stairsDown;
Tile *Tile::stairsUp;
Tile *Tile::infiniteFall;
Tile *Tile::cloud;
Tile *Tile::hardRock;
Tile *Tile::ironOre;
Tile *Tile::goldOre;
Tile *Tile::gemOre;
Tile *Tile::cloudCactus;


void Tile::init()
{
	if(!tilesInitialized) {
		Tile::grass			= new GrassTile(0);
		Tile::rock			= new RockTile(1);
		Tile::water			= new WaterTile(2);
		Tile::flower		= new FlowerTile(3);
		Tile::tree			= new TreeTile(4);
		Tile::dirt			= new DirtTile(5);
		Tile::sand			= new SandTile(6);
		Tile::cactus		= new CactusTile(7);
		Tile::hole			= new HoleTile(8);
		Tile::treeSapling	= new SaplingTile(9, Tile::grass, Tile::tree);
		Tile::cactusSapling	= new SaplingTile(10, Tile::sand, Tile::cactus);
		Tile::farmland		= new FarmTile(11);
		Tile::wheat			= new WheatTile(12);
		Tile::lava			= new LavaTile(13);
		Tile::stairsDown	= new StairsTile(14, false);
		Tile::stairsUp		= new StairsTile(15, true);
		Tile::infiniteFall	= new InfiniteFallTile(16);
		Tile::cloud			= new CloudTile(17);
		Tile::hardRock		= new HardRockTile(18);
		Tile::cloudCactus	= new CloudCactusTile(22);

		tilesInitialized = true;
	}
}

void Tile::init2()
{
	Tile::ironOre		= new OreTile(19, Resource::ironOre);
	Tile::goldOre		= new OreTile(20, Resource::goldOre);
	Tile::gemOre		= new OreTile(21, Resource::gem);
}

Tile::Tile(qint8 id) :
	connectsToGrass(false),
	connectsToSand(false),
	connectsToLava(false),
	connectsToWater(false)
{
	this->id = id;

	if(tiles[id]) {
		qDebug() << "Duplicate tile id" << id;
	}

	tiles[id] = this;
}

bool Tile::mayPass(Level *level, int x, int y, Entity *e)
{
	return true;
}

int Tile::getLightRadius(Level *level, int x, int y)
{
	return 0;
}

bool Tile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	return false;
}

bool Tile::use(Level *level, int xt, int yt, Player *player, int attackDir)
{
	return false;
}

bool Tile::connectsToLiquid() const
{
	return connectsToWater || connectsToLava;
}
