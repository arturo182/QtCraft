#ifndef MENU_H
#define MENU_H

#include <gfx/color.h>
#include <gfx/font.h>

template<typename T>
class QList;

class InputHandler;
class IListItem;
class Screen;
class Game;

class Menu
{
	public:
		Menu();

		virtual void init(Game *game, InputHandler *input);
		virtual void tick() = 0;
		virtual void render(Screen *screen) = 0;

		template <class T>
		void renderItemList(Screen *screen, const int &xo, const int &yo, const int &x1, const int &y1, const QList<T*> &listItems, int selected)
		{
			bool renderCursor = true;
			if(selected < 0) {
				selected = -selected - 1;
				renderCursor = false;
			}

			int w = x1 - xo;
			int h = y1 - yo - 1;
			int i0 = 0;
			int i1 = listItems.size();

			if(i1 > h) {
				i1 = h;
			}

			int io = selected - h / 2;
			if(io > listItems.size() - h) {
				io = listItems.size() - h;
			}

			if(io < 0) {
				io = 0;
			}

			for(int i = i0; i < i1; ++i) {
				listItems[i + io]->renderInventory(screen, (1 + xo) * 8, (i + 1 + yo) * 8);
			}

			if(renderCursor) {
				int yy = selected + 1 - io + yo;
				Font::draw(">", screen, (xo + 0) * 8, yy * 8, Color::get(5, 555, 555, 555));
				Font::draw("<", screen, (xo + w) * 8, yy * 8, Color::get(5, 555, 555, 555));
			}
		}

	protected:
		Game *game;
		InputHandler *input;
};

#endif
