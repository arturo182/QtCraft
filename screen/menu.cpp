#include "menu.h"

#include <item/item.h>
#include <gfx/color.h>
#include <gfx/font.h>

Menu::Menu() :
	game(0),
	input(0)
{
}

void Menu::init(Game *game, InputHandler *input)
{
	this->game = game;
	this->input = input;
}
