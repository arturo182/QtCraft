#ifndef CRAFTING_H
#define CRAFTING_H

template<class T>
class QList;

class Recipe;

class Crafting
{
	public:
		static QList<Recipe*> anvilRecipes;
		static QList<Recipe*> ovenRecipes;
		static QList<Recipe*> furnaceRecipes;
		static QList<Recipe*> workbenchRecipes;

		static void init();

	private:
		static bool listsInitialized;
};


#endif
