#ifndef RESOURCERECIPE_H
#define RESOURCERECIPE_H

#include <crafting/recipe.h>

class ResourceRecipe : public Recipe
{
	public:
		ResourceRecipe(Resource *resource);

		void craft(Player *player);

	private:
		Resource *m_resource;
};

#endif
