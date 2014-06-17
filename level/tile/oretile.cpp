#include "oretile.h"

#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
#include <entity/itementity.h>
#include <item/resourceitem.h>
#include <entity/player.h>
#include <item/resource.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>

OreTile::OreTile(qint8 id, Resource *toDrop) :
	Tile(id)
{
	m_toDrop = toDrop;
	m_color = toDrop->color & 0xffff00;
}

void OreTile::render(Screen *screen, Level *level, int x, int y)
{
	m_color = (m_toDrop->color & 0xffffff00) + Color::get(level->dirtColor);

	screen->render(x * 16 + 0, y * 16 + 0, 17 + 1 * 32, m_color, 0);
	screen->render(x * 16 + 8, y * 16 + 0, 18 + 1 * 32, m_color, 0);
	screen->render(x * 16 + 0, y * 16 + 8, 17 + 2 * 32, m_color, 0);
	screen->render(x * 16 + 8, y * 16 + 8, 18 + 2 * 32, m_color, 0);
}

void OreTile::hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir)
{
	hurt(level, x, y, 0);
}

void OreTile::hurt(Level *level, int x, int y, int dmg)
{
	int damage = level->getData(x, y) + 1;
	level->add(new SmashParticle(x * 16 + 8, y * 16 + 8));
	level->add(new TextParticle(dmg, x * 16 + 8, y * 16 + 8, Color::get(-1, 500, 500, 500)));

	if(dmg > 0) {
		int count = qrand() % 2;
		if(damage >= qrand() % 10 + 3) {
			level->setTile(x, y, Tile::dirt, 0);
			count += 2;
		} else {
			level->setData(x, y, damage);
		}

		for(int i = 0; i < count; i++) {
			level->add(new ItemEntity(new ResourceItem(m_toDrop), x * 16 + qrand() % 10 + 3, y * 16 + qrand() % 10 + 3));
		}
	}
}

bool OreTile::mayPass(Level *level, int x, int y, Entity *e)
{
	return false;
}

bool OreTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
{
	if(ToolItem *tool = dynamic_cast<ToolItem*>(item)) {
		if(tool->type == ToolType::pickaxe) {
			if(player->payStamina(6 - tool->level)) {
				hurt(level, xt, yt, 1);

				return true;
			}
		}
	}

	return false;
}

void OreTile::bumpedInto(Level *level, int xt, int yt, Entity *entity)
{
	entity->hurt(this, xt, yt, 3);
}
