#include "titlemenu.h"

#include <screen/instructionsmenu.h>
#include <screen/aboutmenu.h>
#include <inputhandler.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <gfx/font.h>
#include <game.h>
#include <sound.h>

#include <QDebug>

TitleMenu::TitleMenu() :
	m_selected(0),
	m_options(QStringList() << "Start game" << "How to play" << "About" << "Quit")
{

}

void TitleMenu::tick()
{
	if(input->up->clicked) m_selected -= 1;
	if(input->down->clicked) m_selected += 1;

	int len = m_options.count();
	if(m_selected < 0) {
		m_selected += len;
	}

	if(m_selected >= len) {
		m_selected -= len;
	}

	if((input->attack->clicked) || (input->menu->clicked)) {
	  if(m_selected == 0) {
		Sound::test->play();
		game->resetGame();
		game->setMenu(0);
	  }

	  if(m_selected == 1) {
		  game->setMenu(new InstructionsMenu());
	  }

	  if(m_selected == 2) {
		  game->setMenu(new AboutMenu());
	  }

	  if(m_selected == 3) {
		  game->stop();
	  }
	}
}

void TitleMenu::render(Screen *screen)
{
	screen->clear(0);

	int h = 2;
	int w = 13;
	int titleColor = Color::get(0, 8, 131, 551);
	int xo = (screen->w - w * 8) / 2;
	int yo = 24;

	for(int y = 0; y < h; ++y) {
	  for(int x = 0; x < w; ++x) {
		screen->render(xo + x * 8, yo + y * 8, x + (y + 6) * 32, titleColor, 0);
	  }
	}

	for(int i = 0; i < 4; ++i) {
	  QString msg = m_options[i];
	  int col = Color::get(0, 222, 222, 222);

	  if(i == m_selected) {
		msg = "> " + msg + " <";
		col = Color::get(0, 555, 555, 555);
	  }

	  Font::draw(msg, screen, (screen->w - msg.count() * 8) / 2, (6 + i) * 10, col);
	}

	Font::draw("(Arrow keys,X and C)", screen, 0, screen->h - 8, Color::get(0, 111, 111, 111));
}
