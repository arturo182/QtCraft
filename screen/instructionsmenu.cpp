#include "instructionsmenu.h"

#include <screen/titlemenu.h>
#include <inputhandler.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>
#include <game.h>

InstructionsMenu::InstructionsMenu()
{

}

void InstructionsMenu::tick()
{
	if((input->attack->clicked) || (input->menu->clicked)) {
		game->setMenu(new TitleMenu());

		//delete this;
	}
}

void InstructionsMenu::render(Screen *screen)
{
	screen->clear(0);

	Font::draw("HOW TO PLAY", screen, 36, 8, Color::get(0, 555, 555, 555));
	Font::draw("Move your character", screen, 4, 24, Color::get(0, 333, 333, 333));
	Font::draw("with the arrow keys", screen, 4, 32, Color::get(0, 333, 333, 333));
	Font::draw("press C to attack", screen, 4, 40, Color::get(0, 333, 333, 333));
	Font::draw("and X to open the", screen, 4, 48, Color::get(0, 333, 333, 333));
	Font::draw("inventory and to", screen, 4, 56, Color::get(0, 333, 333, 333));
	Font::draw("use items.", screen, 4, 64, Color::get(0, 333, 333, 333));
	Font::draw("Select an item in", screen, 4, 72, Color::get(0, 333, 333, 333));
	Font::draw("the inventory to", screen, 4, 80, Color::get(0, 333, 333, 333));
	Font::draw("equip it.", screen, 4, 88, Color::get(0, 333, 333, 333));
	Font::draw("Kill the air wizard", screen, 4, 96, Color::get(0, 333, 333, 333));
	Font::draw("to win the game!", screen, 4, 104, Color::get(0, 333, 333, 333));
}
