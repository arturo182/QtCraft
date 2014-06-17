#include "item.h"

#include <typeinfo>

Item::Item()
{
}

int Item::getColor() const
{
	return 0;
}

int Item::getSprite() const
{
	return 0;
}

bool Item::interact(Player *player, Entity *entity, int attackDir)
{
	return false;
}

bool Item::interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir)
{
	return false;
}

bool Item::isDepleted() const
{
	return false;
}

bool Item::canAttack()
{
	return false;
}

int Item::getAttackDamageBonus(Entity *e)
{
	return 0;
}

QString Item::getName() const
{
	return "";
}

bool Item::matches(Item *item)
{
	return (typeid(item) == typeid(this));
}
