#include "wonmenu.h"

#include <screen/titlemenu.h>
#include <entity/player.h>
#include <inputhandler.h>
#include <game.h>

WonMenu::WonMenu() :
	m_inputDelay(60)
{
}

void WonMenu::tick()
{
	if(m_inputDelay > 0) {
		--m_inputDelay;
	} else if(input->attack->clicked || input->menu->clicked) {
		game->setMenu(new TitleMenu());
		//delete this;
	}
}

void WonMenu::render(Screen *screen)
{
	Font::renderFrame(screen, "", 1, 3, 18, 9);
	Font::draw("You won! Yay!", screen, 2 * 8, 4 * 8, Color::get(-1, 555, 555, 555));

	int seconds = game->gameTime / 60;
	int minutes = seconds / 60;
	int hours = minutes / 60;
	minutes %= 60;
	seconds %= 60;

	QString timeString;
	if (hours > 0) {
		timeString = QString("%1h%2%3m").arg(hours).arg(minutes < 10 ? "0" : "").arg(minutes);
	} else {
		timeString = QString("%1m%2%3s").arg(minutes).arg(seconds < 10 ? "0" : "").arg(seconds);
	}

	Font::draw("Time:", screen, 2 * 8, 5 * 8, Color::get(-1, 555, 555, 555));
	Font::draw(timeString, screen, (2 + 5) * 8, 5 * 8, Color::get(-1, 550, 550, 550));
	Font::draw("Score:", screen, 2 * 8, 6 * 8, Color::get(-1, 555, 555, 555));
	Font::draw(game->player->score, screen, (2 + 6) * 8, 6 * 8, Color::get(-1, 550, 550, 550));
	Font::draw("Press C to win", screen, 2 * 8, 8 * 8, Color::get(-1, 333, 333, 333));

}
