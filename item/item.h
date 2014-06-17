#ifndef ITEM_H
#define ITEM_H

#include <item/ilistitem.h>

#include <QString>

class ItemEntity;
class Entity;
class Player;
class Level;
class Tile;

class Item : public IListItem
{
	public:
		Item();

		virtual int getColor() const;
		virtual int getSprite() const;
		virtual void onTake(ItemEntity *itemEntity) { }
		virtual bool interact(Player *player, Entity *entity, int attackDir);
		virtual void renderIcon(Screen *screen, int x, int y) = 0;
		virtual bool interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir);
		virtual bool isDepleted() const;
		virtual bool canAttack();
		virtual int getAttackDamageBonus(Entity *e);
		virtual QString getName() const;
		virtual bool matches(Item *item);
};

#endif
