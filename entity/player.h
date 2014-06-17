#ifndef PLAYER_H
#define PLAYER_H

#include <entity/mob.h>

class InputHandler;
class Inventory;
class Item;
class Level;
class Game;

class Player : public Mob
{
	public:
		Player(Game *game, InputHandler *input);

		void tick();
		void render(Screen *screen);

		void touchItem(ItemEntity *itemEntity);

		bool findStartPos(Level *level);
		int getLightRadius();
		void changeLevel(int dir);
		void gameWon();

		bool canSwim();
		bool payStamina(int cost);


	public:
		Game *game;
		Inventory *inventory;
		Item *attackItem;
		Item *activeItem;
		int stamina;
		int staminaRecharge;
		int staminaRechargeDelay;
		int score;
		int maxStamina;
		int invulnerableTime;

	protected:
		void die();
		void doHurt(int dmg, int m_attackDir);
		void touchedBy(Entity *entity);

	private:
		void attack();
		bool use();
		bool use(int x0, int y0, int x1, int y1);
		void hurt(int x0, int y0, int x1, int y1);
		bool interact(int x0, int y0, int x1, int y1);
		int getAttackDamage(Entity *entity);

	private:
		InputHandler *m_input;
		int m_attackTime;
		int m_attackDir;
		int m_onStairDelay;
};

#endif
