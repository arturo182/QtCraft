#ifndef ITEMENTITY_H
#define ITEMENTITY_H

#include <entity/entity.h>

class Item;

class ItemEntity : public Entity
{
	public:
		ItemEntity(Item *item, int x, int y);

		void tick();
		void render(Screen *screen);
		void take(Player *player);
		bool isBlockableBy(Mob *mob);

	public:
		Item *item;
		int hurtTime;
		double xa;
		double ya;
		double za;
		double xx;
		double yy;
		double zz;

	protected:
		void touchedBy(Entity *entity);

	protected:
		int walkDist;
		int dir;
		int xKnockback;
		int yKnockback;

	private:
		int m_lifeTime;
		int m_time;
};

#endif
