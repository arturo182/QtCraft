#include "player.h"

#include <screen/inventorymenu.h>
#include <item/powergloveitem.h>
#include <item/furnitureitem.h>
#include <entity/itementity.h>
#include <entity/furniture.h>
#include <entity/inventory.h>
#include <entity/workbench.h>
#include <level/tile/tile.h>
#include <item/toolitem.h>
#include <item/tooltype.h>
#include <inputhandler.h>
#include <level/level.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <item/item.h>
#include <game.h>
#include <sound.h>
#include <entity/particle/textparticle.h>

Player::Player(Game *game, InputHandler *input) :
	inventory(new Inventory),
	attackItem(0),
	activeItem(0),
	staminaRecharge(0),
	staminaRechargeDelay(0),
	score(0),
	maxStamina(10),
	invulnerableTime(0),
	m_attackTime(0),
	m_attackDir(0),
	m_onStairDelay(0)
{
	this->game = game;
	m_input = input;

	x = 24;
	y = 24;

	stamina = maxStamina;

	inventory->add(new FurnitureItem(new Workbench()));
	inventory->add(new PowerGloveItem());
	inventory->add(new ToolItem(ToolType::sword, 4));
	inventory->add(new ToolItem(ToolType::shovel, 4));
	inventory->add(new ToolItem(ToolType::hoe, 4));
	inventory->add(new ToolItem(ToolType::axe, 4));
	inventory->add(new ToolItem(ToolType::pickaxe, 4));

}

void Player::tick()
{
	Mob::tick();

	if(invulnerableTime > 0) {
		invulnerableTime -= 1;
	}

	Tile *onTile = level->getTile(x >> 4, y >> 4);
	if((onTile == Tile::stairsDown) || (onTile == Tile::stairsUp)) {
		if(m_onStairDelay == 0) {
			changeLevel(onTile == Tile::stairsUp ? 1 : -1);
			m_onStairDelay = 10;

			return;
		}

		m_onStairDelay = 10;
	} else if(m_onStairDelay > 0) {
		m_onStairDelay -= 1;
	}

	if((stamina <= 0) && (staminaRechargeDelay == 0) && (staminaRecharge == 0)) {
		staminaRechargeDelay = 40;
	}

	if(staminaRechargeDelay > 0) {
		staminaRechargeDelay -= 1;
	}

	if(staminaRechargeDelay == 0) {
		staminaRecharge += 1;

		if(isSwimming()) {
			staminaRecharge = 0;
		}

		while(staminaRecharge > 10) {
			staminaRecharge -= 10;

			if(stamina < maxStamina) {
				stamina += 1;
			}
		}
	}

	int xa = 0;
	int ya = 0;

	if(m_input->up->down) {
		--ya;
	}

	if(m_input->down->down) {
		++ya;
	}

	if(m_input->left->down) {
		--xa;
	}

	if(m_input->right->down) {
		++xa;
	}

	if((isSwimming()) && (tickTime % 60 == 0)) {
		if(stamina > 0) {
			stamina -= 1;
		} else {
			Mob::hurt(this, 1, dir ^ 0x1);
		}
	}

	if(staminaRechargeDelay % 2 == 0) {
		move(xa, ya);
	}

	if((m_input->attack->clicked) && (stamina != 0)) {
		stamina -= 1;
		staminaRecharge = 0;

		attack();
	}

	if((m_input->menu->clicked) && !use()) {
		game->setMenu(new InventoryMenu(this));
	}

	if(m_attackTime > 0) {
		m_attackTime -= 1;
	}
}

void Player::render(Screen *screen)
{
	int xt = 0;
	int yt = 14;

	int flip1 = walkDist >> 3 & 0x1;
	int flip2 = walkDist >> 3 & 0x1;

	if(dir == 1) {
		xt += 2;
	}

	if(dir > 1) {
		flip1 = 0;
		flip2 = walkDist >> 4 & 0x1;

		if(dir == 2) {
			flip1 = 1;
		}

		xt += 4 + (walkDist >> 3 & 0x1) * 2;
	}

	int xo = x - 8;
	int yo = y - 11;

	if(isSwimming()) {
		yo += 4;

		int waterColor = Color::get(-1, -1, 115, 335);
		if(tickTime / 8 % 2 == 0) {
			waterColor = Color::get(-1, 335, 5, 115);
		}

		screen->render(xo + 0, yo + 3, 421, waterColor, 0);
		screen->render(xo + 8, yo + 3, 421, waterColor, 1);
	}

	if((m_attackTime > 0) && (m_attackDir == 1)) {
		screen->render(xo + 0, yo - 4, 422, Color::get(-1, 555, 555, 555), 0);
		screen->render(xo + 8, yo - 4, 422, Color::get(-1, 555, 555, 555), 1);

		if(attackItem) {
			attackItem->renderIcon(screen, xo + 4, yo - 4);
		}
	}

	int col = Color::get(-1, 100, 220, 532);
	if(hurtTime > 0) {
		col = Color::get(-1, 555, 555, 555);
	}

	FurnitureItem *furniture = dynamic_cast<FurnitureItem*>(activeItem);
	if(furniture) {
		yt += 2;
	}

	screen->render(xo + 8 * flip1, yo + 0, xt + yt * 32, col, flip1);
	screen->render(xo + 8 - 8 * flip1, yo + 0, xt + 1 + yt * 32, col, flip1);

	if(!isSwimming()) {
		screen->render(xo + 8 * flip2, yo + 8, xt + (yt + 1) * 32, col, flip2);
		screen->render(xo + 8 - 8 * flip2, yo + 8, xt + 1 + (yt + 1) * 32, col, flip2);
	}

	if((m_attackTime > 0) && (m_attackDir == 2)) {
		screen->render(xo - 4, yo, 423, Color::get(-1, 555, 555, 555), 1);
		screen->render(xo - 4, yo + 8, 423, Color::get(-1, 555, 555, 555), 3);

		if(attackItem) {
			attackItem->renderIcon(screen, xo - 4, yo + 4);
		}
	}

	if((m_attackTime > 0) && (m_attackDir == 3)) {
		screen->render(xo + 8 + 4, yo, 423, Color::get(-1, 555, 555, 555), 0);
		screen->render(xo + 8 + 4, yo + 8, 423, Color::get(-1, 555, 555, 555), 2);

		if(attackItem) {
			attackItem->renderIcon(screen, xo + 8 + 4, yo + 4);
		}
	}

	if((m_attackTime > 0) && (m_attackDir == 0)) {
		screen->render(xo + 0, yo + 8 + 4, 422, Color::get(-1, 555, 555, 555), 2);
		screen->render(xo + 8, yo + 8 + 4, 422, Color::get(-1, 555, 555, 555), 3);

		if(attackItem) {
			attackItem->renderIcon(screen, xo + 4, yo + 8 + 4);
		}
	}

	if(furniture) {
		furniture->furniture->x = x;
		furniture->furniture->y = yo;
		furniture->furniture->render(screen);
	}
}

void Player::touchedBy(Entity *entity)
{
	Player *play = dynamic_cast<Player*>(entity);
	if(!play) {
		entity->touchedBy(this);
	}
}

void Player::touchItem(ItemEntity *itemEntity)
{
	itemEntity->take(this);
	inventory->add(0, itemEntity->item);
}

bool Player::findStartPos(Level *level)
{
	int x;
	int y;

	do
	{
		x = qrand() % level->w;
		y = qrand() % level->h;
	} while(level->getTile(x, y) != Tile::grass);

	this->x = (x * 16 + 8);
	this->y = (y * 16 + 8);

	return true;
}

int Player::getLightRadius()
{
	int r = 2;
	if(activeItem) {
		if(FurnitureItem *furniture = dynamic_cast<FurnitureItem*>(activeItem)) {
			int rr = furniture->furniture->getLightRadius();
			if(rr > r) {
				r = rr;
			}
		}
	}
	return r;
}

void Player::changeLevel(int dir)
{
	game->scheduleLevelChange(dir);
}

void Player::gameWon()
{
	level->player->invulnerableTime = 60 * 5;
	game->won();
}

void Player::attack()
{
	walkDist += 8;
	m_attackDir = dir;
	attackItem = activeItem;
	bool done = false;

	if(activeItem) {
		m_attackTime = 10;
		int yo = -2;
		int range = 12;

		if((dir == 0) && (interact(x - 8, y + 4 + yo, x + 8, y + range + yo))) {
			done = true;
		}

		if((dir == 1) && (interact(x - 8, y - range + yo, x + 8, y - 4 + yo))) {
			done = true;
		}

		if((dir == 3) && (interact(x + 4, y - 8 + yo, x + range, y + 8 + yo))) {
			done = true;
		}

		if((dir == 2) && (interact(x - range, y - 8 + yo, x - 4, y + 8 + yo))) {
			done = true;
		}

		if(done) {
			return;
		}

		int xt = x >> 4;
		int yt = (y + yo) >> 4;
		int r = 12;

		if(m_attackDir == 0) {
			yt = (y + r + yo) >> 4;
		}

		if(m_attackDir == 1) {
			yt = (y - r + yo) >> 4;
		}

		if(m_attackDir == 2) {
			xt = (x - r) >> 4;
		}

		if(m_attackDir == 3) {
			xt = (x + r) >> 4;
		}

		if((xt >= 0) && (yt >= 0) && (xt < level->w) && (yt < level->h)) {
			if(activeItem->interactOn(level->getTile(xt, yt), level, xt, yt, this, m_attackDir)) {
				done = true;
			} else if(level->getTile(xt, yt)->interact(level, xt, yt, this, activeItem, m_attackDir)) {
				done = true;
			}

			if(activeItem->isDepleted()) {
				//delete activeItem;
				activeItem = 0;
			}
		}
	}

	if(done) {
		return;
	}

	if((!activeItem) || (activeItem->canAttack())) {
		m_attackTime = 5;
		int yo = -2;
		int range = 20;

		if(dir == 0) {
			hurt(x - 8, y + 4 + yo, x + 8, y + range + yo);
		}

		if(dir == 1) {
			hurt(x - 8, y - range + yo, x + 8, y - 4 + yo);
		}

		if(dir == 3) {
			hurt(x + 4, y - 8 + yo, x + range, y + 8 + yo);
		}

		if(dir == 2) {
			hurt(x - range, y - 8 + yo, x - 4, y + 8 + yo);
		}

		int xt = x >> 4;
		int yt = (y + yo) >> 4;
		int r = 12;

		if(m_attackDir == 0) {
			yt = (y + r + yo) >> 4;
		}

		if(m_attackDir == 1) {
			yt = (y - r + yo) >> 4;
		}

		if(m_attackDir == 2) {
			xt = (x - r) >> 4;
		}

		if(m_attackDir == 3) {
			xt = (x + r) >> 4;
		}

		if((xt >= 0) && (yt >= 0) && (xt < level->w) && (yt < level->h)) {
			level->getTile(xt, yt)->hurt(level, xt, yt, this, qrand() % 3 + 1, m_attackDir);
		}
	}
}

bool Player::canSwim()
{
	return true;
}

bool Player::payStamina(int cost)
{
	if(cost > stamina) {
		return false;
	}

	stamina -= cost;

	return true;
}

void Player::die()
{
	Mob::die();
	//Sound::playerDeath->play();
}

void Player::doHurt(int dmg, int attackDir)
{
	if((hurtTime > 0) || (invulnerableTime > 0)) {
		return;
	}

	Sound::playerHurt->play();

	level->add(new TextParticle(dmg, x, y, Color::get(-1, 504, 504, 504)));
	//health -= dmg;

	if(attackDir == 0) {
		yKnockback = 6;
	}

	if(attackDir == 1) {
		yKnockback = -6;
	}

	if(attackDir == 2) {
		xKnockback = -6;
	}

	if(attackDir == 3) {
		xKnockback = 6;
	}

	hurtTime = 10;
	invulnerableTime = 30;
}

bool Player::use()
{
	int yo = -2;

	if((dir == 0) && (use(x - 8, y + 4 + yo, x + 8, y + 12 + yo))) {
		return true;
	}

	if((dir == 1) && (use(x - 8, y - 12 + yo, x + 8, y - 4 + yo))) {
		return true;
	}

	if((dir == 3) && (use(x + 4, y - 8 + yo, x + 12, y + 8 + yo))) {
		return true;
	}

	if((dir == 2) && (use(x - 12, y - 8 + yo, x - 4, y + 8 + yo))) {
		return true;
	}

	int xt = x >> 4;
	int yt = (y + yo) >> 4;
	int r = 12;

	if(m_attackDir == 0) {
		yt = (y + r + yo) >> 4;
	}

	if(m_attackDir == 1) {
		yt = (y - r + yo) >> 4;
	}

	if(m_attackDir == 2) {
		xt = (x - r) >> 4;
	}

	if(m_attackDir == 3) {
		xt = (x + r) >> 4;
	}

	return (xt >= 0) && (yt >= 0) && (xt < level->w) && (yt < level->h) && (level->getTile(xt, yt)->use(level, xt, yt, this, m_attackDir));
}

bool Player::use(int x0, int y0, int x1, int y1)
{
	QList<Entity*> entities = level->getEntities(x0, y0, x1, y1);

	for(int i = 0; i < entities.count(); ++i) {
		Entity *e = entities[i];

		if((e != this) && (e->use(this, m_attackDir))) {
			return true;
		}
	}

	return false;
}

void Player::hurt(int x0, int y0, int x1, int y1)
{
	QList<Entity*> entities = level->getEntities(x0, y0, x1, y1);

	for(int i = 0; i < entities.size(); ++i) {
		Entity *e = entities[i];
		if(e != this) {
			e->hurt(this, getAttackDamage(e), m_attackDir);
		}
	}
}

bool Player::interact(int x0, int y0, int x1, int y1)
{
	QList<Entity*> entities = level->getEntities(x0, y0, x1, y1);

	for(int i = 0; i < entities.count(); ++i) {
		Entity *e = entities[i];

		if((e != this) && (e->interact(this, activeItem, m_attackDir))) {
			return true;
		}
	}

	return false;
}

int Player::getAttackDamage(Entity *entity)
{
	int dmg = qrand() % 3 + 1;

	if(attackItem) {
		dmg += attackItem->getAttackDamageBonus(entity);
	}

	return dmg;
}
