#include "cloudcactustile.h"

#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
#include <entity/player.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <entity/airwizard.h>

CloudCactusTile::CloudCactusTile(qint8 id) :
	Tile(id)
{
}

void CloudCactusTile::render(Screen *screen, Level *level, int x, int y)
{
	int color = Color::get(444, 111, 333, 555);
	screen->render(x * 16 + 0, y * 16 + 0, 17 + 1 * 32, color, 0);
	screen->render(x * 16 + 8, y * 16 + 0, 18 + 1 * 32, color, 0);
	screen->render(x * 16 + 0, y * 16 + 8, 17 + 2 * 32, color, 0);
	screen->render(x * 16 + 8, y * 16 + 8, 18 + 2 * 32, color, 0);
}

bool CloudCactusTile::mayPass(Level *level, int x, int y, Entity *e)
{
	AirWizard *wizard = dynamic_cast<AirWizard*>(e);
	if(wizard) {
		return true;
	}

	return false;
}

void CloudCactusTile::hurt(Level *level, int x, int y, Mob *source, int dmg, int attackDir)
{
	hurt(level, x, y, 0);
}

void CloudCactusTile::hurt(Level *level, int x, int y, int dmg)
{
	int damage = level->getData(x, y) + 1;
	level->add(new SmashParticle(x * 16 + 8, y * 16 + 8));
	level->add(new TextParticle(dmg, x * 16 + 8, y * 16 + 8, Color::get(-1, 500, 500, 500)));
	if(dmg > 0) {
		if(damage >= 10) {
			level->setTile(x, y, Tile::cloud, 0);
		} else {
			level->setData(x, y, damage);
		}
	}
}

bool CloudCactusTile::interact(Level *level, int xt, int yt, Player *player, Item *item, int attackDir)
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

void CloudCactusTile::bumpedInto(Level *level, int xt, int yt, Entity *entity)
{
	AirWizard *wizard = dynamic_cast<AirWizard*>(entity);
	if(wizard) {
		return;
	}

	entity->hurt(this, xt, yt, 3);
}
