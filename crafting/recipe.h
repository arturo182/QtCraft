#ifndef RECIPE_H
#define RECIPE_H

#include <item/item.h>

#include <QVector>

class Resource;
class Player;

class Recipe : public IListItem
{
	public:
		Recipe(Item *resultTemplate);

		virtual void craft(Player *player) = 0;

		Recipe *addCost(Resource *resource, int count);
		void checkCanCraft(Player *player);
		void deductCost(Player *player);
		void renderInventory(Screen *screen, const int &x, const int &y) const;

	public:
		QVector<Item*> costs;
		bool canCraft;
		Item *resultTemplate;
};

#endif
