#include "resource.h"

#include <item/plantableresource.h>
#include <item/foodresource.h>
#include <level/tile/tile.h>
#include <entity/player.h>
#include <level/level.h>
#include <gfx/color.h>

#include <QDebug>

bool Resource::resourcesInitialized = false;
Resource *Resource::wood;
Resource *Resource::stone;
Resource *Resource::flower;
Resource *Resource::acorn;
Resource *Resource::dirt;
Resource *Resource::sand;
Resource *Resource::cactusFlower;
Resource *Resource::seeds;
Resource *Resource::wheat;
Resource *Resource::bread;
Resource *Resource::apple;

Resource *Resource::coal;
Resource *Resource::ironOre;
Resource *Resource::goldOre;
Resource *Resource::ironIngot;
Resource *Resource::goldIngot;

Resource *Resource::slime;
Resource *Resource::glass;
Resource *Resource::cloth;
Resource *Resource::cloud;
Resource *Resource::gem;

void Resource::init()
{
	if(!resourcesInitialized) {
		Resource::wood =		new Resource("Wood",  129, Color::get(-1, 200, 531, 430));
		Resource::stone =		new Resource("Stone", 130, Color::get(-1, 111, 333, 555));
		Resource::wheat =		new Resource("Wheat", 134, Color::get(-1, 110, 330, 550));
		Resource::bread =		new FoodResource("Bread", 136, Color::get(-1, 110, 330, 550), 2, 5);
		Resource::apple =		new FoodResource("Apple", 137, Color::get(-1, 100, 300, 500), 1, 5);

		Resource::coal =		new Resource("COAL",  138, Color::get(-1, 0, 111, 111));
		Resource::ironOre =		new Resource("I.ORE", 138, Color::get(-1, 100, 322, 544));
		Resource::goldOre =		new Resource("G.ORE", 138, Color::get(-1, 110, 440, 553));
		Resource::ironIngot =	new Resource("IRON",  139, Color::get(-1, 100, 322, 544));
		Resource::goldIngot =	new Resource("GOLD",  139, Color::get(-1, 110, 330, 553));

		Resource::slime =		new Resource("SLIME", 138, Color::get(-1, 10, 30, 50));
		Resource::glass =		new Resource("glass", 140, Color::get(-1, 555, 555, 555));
		Resource::cloth =		new Resource("cloth", 129, Color::get(-1, 25, 252, 141));
		Resource::gem =			new Resource("gem", 141, Color::get(-1, 101, 404, 545));

		resourcesInitialized = true;
	}
}

void Resource::init2()
{
	Resource::flower =			new PlantableResource("Flower", 128, Color::get(-1, 10, 444, 330),  Tile::flower,        QList<Tile*>() << Tile::grass);
	Resource::acorn =			new PlantableResource("Acorn",  131, Color::get(-1, 100, 531, 320), Tile::treeSapling,   QList<Tile*>() << Tile::grass);
	Resource::dirt =			new PlantableResource("Dirt",   130, Color::get(-1, 100, 322, 432), Tile::dirt,          QList<Tile*>() << Tile::hole  << Tile::water << Tile::lava);
	Resource::sand =			new PlantableResource("Sand",   130, Color::get(-1, 110, 440, 550), Tile::sand,          QList<Tile*>() << Tile::grass << Tile::dirt);
	Resource::cactusFlower =	new PlantableResource("Cactus", 132, Color::get(-1, 10, 40, 50),    Tile::cactusSapling, QList<Tile*>() << Tile::sand);
	Resource::seeds =			new PlantableResource("Seeds",  133, Color::get(-1, 10, 40, 50),    Tile::wheat,         QList<Tile*>() << Tile::farmland);
	Resource::cloud =			new PlantableResource("cloud",  130, Color::get(-1, 222, 555, 444), Tile::cloud,         QList<Tile*>() << Tile::infiniteFall);

}

Resource::Resource(QString name, int sprite, int color)
{
	if(name.count() > 6) {
		qDebug() << "Name cannot be longer than six chars!";
	}

	this->name = name;
	this->sprite = sprite;
	this->color = color;
}

bool Resource::interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir)
{
	return false;
}
