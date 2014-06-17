#include "aboutmenu.h"

#include <screen/titlemenu.h>
#include <inputhandler.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>
#include <game.h>

AboutMenu::AboutMenu()
{

}

void AboutMenu::tick()
{
	if((input->attack->clicked) || (input->menu->clicked)) {
		game->setMenu(new TitleMenu());
		//delete this;
	}
}

void AboutMenu::render(Screen *screen)
{
	screen->clear(0);

	Font::draw("About QtCraft", screen, 20, 8, Color::get(0, 555, 555, 555));
	Font::draw("Minicraft was made", screen, 4, 24, Color::get(0, 333, 333, 333));
	Font::draw("by Markus Persson", screen, 4, 32, Color::get(0, 333, 333, 333));
	Font::draw("And ported to Qt", screen, 4, 40, Color::get(0, 333, 333, 333));
	Font::draw("by arturo182.", screen, 4, 48, Color::get(0, 333, 333, 333));
	Font::draw("Just for fun.", screen, 4, 56, Color::get(0, 333, 333, 333));
	Font::draw("It is dedicated to", screen, 4, 72, Color::get(0, 333, 333, 333));
	Font::draw("Markus' father. <3", screen, 4, 80, Color::get(0, 333, 333, 333));
}
