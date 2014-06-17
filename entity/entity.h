#ifndef ENTITY_H
#define ENTITY_H

class ItemEntity;
class Player;
class Screen;
class Level;
class Item;
class Tile;
class Mob;

class Entity
{
	public:
		Entity();

		virtual void render(Screen *screen) = 0;
		virtual void tick() = 0;
		virtual void remove();
		virtual void hurt(Mob *mob, int dmg, int attackDir) { }
		virtual void hurt(Tile *tile, int x, int y, int dmg) { }

		void init(Level *level);
		virtual bool intersects(int x0, int y0, int x1, int y1);
		virtual bool blocks(Entity *e);
		virtual bool isBlockableBy(Mob *mob);
		virtual void touchItem(ItemEntity *itemEntity) { }

		virtual bool canSwim();
		virtual bool interact(Player *player, Item *item, int attackDir);
		virtual bool use(Player *player, int attackDir);
		virtual int getLightRadius();

		virtual bool move(int xa, int ya);
		virtual void touchedBy(Entity *entity) { }

	public:
		int x;
		int y;
		int xr;
		int yr;
		bool removed;
		Level *level;

	protected:
		virtual bool move2(int xa, int ya);

};

#endif
