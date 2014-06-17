#ifndef TOOLRECIPE_H
#define TOOLRECIPE_H

#include <crafting/recipe.h>

class ToolType;

class ToolRecipe : public Recipe
{
	public:
		ToolRecipe(ToolType *type, int level);

		void craft(Player *player);

	private:
		ToolType *m_type;
		int m_level;
};

#endif
