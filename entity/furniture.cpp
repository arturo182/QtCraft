#include "furniture.h"

#include <item/powergloveitem.h>
#include <item/furnitureitem.h>
#include <entity/inventory.h>
#include <entity/player.h>
#include <gfx/screen.h>

Furniture::Furniture(QString name) :
	col(0),
	sprite(0),
	m_pushTime(0),
	m_pushDir(-1),
	m_shouldTake(0)
{
	this->name = name;
	xr = 3;
	yr = 3;
}

void Furniture::tick()
{
	if(m_shouldTake) {
		if(PowerGloveItem *pow = dynamic_cast<PowerGloveItem*>(m_shouldTake->activeItem)) {
			remove();

			m_shouldTake->inventory->add(0, pow);
			m_shouldTake->activeItem = new FurnitureItem(this);
		}

		m_shouldTake = 0;
	}

	if(m_pushDir == 0) {
		move(0, 1);
	}

	if(m_pushDir == 1) {
		move(0, -1);
	}

	if(m_pushDir == 2) {
		move(-1, 0);
	}

	if(m_pushDir == 3) {
		move(1, 0);
	}

	m_pushDir = -1;
	if(m_pushTime > 0) {
		--m_pushTime;
	}
}

void Furniture::render(Screen *screen)
{
	screen->render(x - 8, y - 8 - 4, sprite * 2 + 256, col, 0);
	screen->render(x - 0, y - 8 - 4, sprite * 2 + 256 + 1, col, 0);
	screen->render(x - 8, y - 0 - 4, sprite * 2 + 256 + 32, col, 0);
	screen->render(x - 0, y - 0 - 4, sprite * 2 + 256 + 33, col, 0);
}

bool Furniture::blocks(Entity *e)
{
	return true;
}

void Furniture::take(Player *player)
{
	m_shouldTake = player;
}

void Furniture::touchedBy(Entity *entity)
{
	if(Player *player = dynamic_cast<Player*>(entity)) {
		if(m_pushTime == 0) {
			m_pushDir = player->dir;
			m_pushTime = 10;
		}
	}
}

