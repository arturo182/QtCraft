#include "foodresource.h"

#include <entity/player.h>

#include <QDebug>

FoodResource::FoodResource(QString name, int sprite, int color, int heal, int staminaCost) :
	Resource(name, sprite, color)
{
	m_heal = heal;
	m_staminaCost = staminaCost;
}

bool FoodResource::interactOn(Tile *tile, Level *level, int xt, int yt, Player *player, int attackDir)
{
	if((player->health < player->maxHealth) && (player->payStamina(m_staminaCost))) {
		player->heal(m_heal);

		return true;
	}

	return false;
}
