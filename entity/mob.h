#ifndef MOB_H
#define MOB_H

#include <entity/entity.h>

class Level;

class Mob : public Entity
{
	public:
		Mob();

		virtual void tick();
		virtual void hurt(Mob *mob, int dmg, int attackDir);
		virtual void hurt(Tile *tile, int x, int y, int dmg);
		virtual void heal(int heal);
		virtual bool move(int xa, int ya);
		virtual bool findStartPos(Level *level);
		virtual bool blocks(Entity *e);

	public:
		int hurtTime;
		int maxHealth;
		int health;
		int swimTimer;
		int tickTime;
		int dir;

	protected:
		virtual void doHurt(int dmg, int attackDir);
		virtual bool isSwimming();
		virtual void die();

	protected:
		int walkDist;
		int xKnockback;
		int yKnockback;
};

#endif
