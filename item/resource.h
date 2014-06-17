#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>

class Player;
class Level;
class Tile;

class Resource
{
	public:
		static Resource *wood;
		static Resource *stone;
		static Resource *flower;
		static Resource *acorn;
		static Resource *dirt;
		static Resource *sand;
		static Resource *cactusFlower;
		static Resource *seeds;
		static Resource *wheat;
		static Resource *bread;
		static Resource *apple;

		static Resource *coal;
		static Resource *ironOre;
		static Resource *goldOre;
		static Resource *ironIngot;
		static Resource *goldIngot;

		static Resource *slime;
		static Resource *glass;
		static Resource *cloth;
		static Resource *cloud;
		static Resource *gem;

		static void init();
		static void init2();

	public:
		Resource(QString name, int sprite, int color);

		virtual bool interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir);

	public:
		QString name;
		int sprite;
		int color;

	private:
		static bool resourcesInitialized;
};

#endif
