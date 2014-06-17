#include "game.h"

#include <screen/leveltransitionmenu.h>
#include <crafting/crafting.h>
#include <screen/titlemenu.h>
#include <gfx/spritesheet.h>
#include <level/tile/tile.h>
#include <screen/deadmenu.h>
#include <screen/wonmenu.h>
#include <entity/player.h>
#include <item/resource.h>
#include <inputhandler.h>
#include <level/level.h>
#include <screen/menu.h>
#include <gfx/screen.h>
#include <item/item.h>
#include <gfx/color.h>
#include <gfx/font.h>

#include <QApplication>
#include <QDateTime>
#include <QKeyEvent>
#include <QPainter>
#include <QtOpenGL>
#include <QDebug>

QString Game::NAME = "QtCraft";
int Game::WIDTH = 160;
int Game::HEIGHT = 120;

Game::Game(QWidget *parent) :
	QGLWidget(parent),
	player(0),
	menu(0),
	gameTime(0),
	m_pixels(QVector<int>(Game::WIDTH * Game::HEIGHT)),
	m_running(false),
	m_image(QImage(Game::WIDTH, Game::HEIGHT, QImage::Format_RGB32)),
	m_screen(0),
	m_lightScreen(0),
	m_input(new InputHandler(this)),
	m_tickCount(0),
	m_level(0),
	m_currentLevel(3),
	m_playerDeadTime(0),
	m_pendingLevelChange(0),
	m_wonTimer(0),
	m_hasWon(false)
{
	qsrand(QDateTime::currentDateTime().toTime_t());

	setAttribute(Qt::WA_QuitOnClose);
	setFocusPolicy(Qt::StrongFocus);

	resize(Game::WIDTH * 4, Game::HEIGHT * 4);
}

void Game::start()
{
	m_timer.start();
	m_running = true;
	run();
}

void Game::stop()
{
	m_running = false;
}

void Game::won()
{
	m_wonTimer = 60 * 3;
	m_hasWon = true;
}

void Game::setMenu(Menu *menu)
{
	delete this->menu;

	this->menu = menu;

	if(menu) {
		menu->init(this, m_input);
	}
}

void Game::resetGame()
{
	m_playerDeadTime = 0;
	m_wonTimer = 0;
	gameTime = 0;
	m_hasWon = false;

	m_currentLevel = 3;

	//qDeleteAll(levels);

	Level *level4 = new Level(128, 128, 1, 0);
	Level *level3 = new Level(128, 128, 0, level4);
	Level *level2 = new Level(128, 128, -1, level3);
	Level *level1 = new Level(128, 128, -2, level2);
	Level *level0 = new Level(128, 128, -3, level1);

	m_levels.append(level0);
	m_levels.append(level1);
	m_levels.append(level2);
	m_levels.append(level3);
	m_levels.append(level4);

	m_level = m_levels[m_currentLevel];

	//delete player;

	player = new Player(this, m_input);
	player->findStartPos(m_level);

	m_level->add(player);

	for(int i = 0; i < 5; ++i) {
		m_levels[i]->trySpawn(5000);
	}
}

void Game::tick()
{
	++m_tickCount;

	if(!hasFocus()) {
		m_input->releaseAll();
	} else {
		if((!player->removed) && (!m_hasWon)) {
			++gameTime;
		}

		m_input->tick();

		if(menu) {
			menu->tick();
		} else {
			if(player->removed) {
				++m_playerDeadTime;

				if(m_playerDeadTime > 60) {
					setMenu(new DeadMenu());
				}
			} else if(m_pendingLevelChange != 0) {
				setMenu(new LevelTransitionMenu(m_pendingLevelChange));
				m_pendingLevelChange = 0;
			}

			if(m_wonTimer > 0) {
				if(--m_wonTimer == 0) {
					setMenu(new WonMenu());
				}
			}

			m_level->tick();
			++Tile::tickCount;
		}
	}
}

void Game::scheduleLevelChange(const int &dir)
{
	m_pendingLevelChange = dir;
}

void Game::changeLevel(const int &dir)
{
	m_level->remove(player);
	m_currentLevel += dir;
	m_level = m_levels[m_currentLevel];
	player->x = (player->x >> 4) * 16 + 8;
	player->y = (player->y >> 4) * 16 + 8;
	m_level->add(player);
}

void Game::closeEvent(QCloseEvent *event)
{
	m_running = false;
}

void Game::paintEvent(QPaintEvent *event)
{
	int xScroll = player->x - m_screen->w / 2;
	int yScroll = player->y - (m_screen->h - 8) / 2;

	if(xScroll < 16) {
		xScroll = 16;
	}

	if(yScroll < 16) {
		yScroll = 16;
	}

	if(xScroll > m_level->w * 16 - m_screen->w - 16) {
		xScroll = m_level->w * 16 - m_screen->w - 16;
	}

	if(yScroll > m_level->h * 16 - m_screen->h - 16) {
		yScroll = m_level->h * 16 - m_screen->h - 16;
	}

	if(m_currentLevel > 3) {
		int col = Color::get(20, 20, 121, 121);

		for(int y = 0; y < 14; ++y) {
			for(int x = 0; x < 24; ++x) {
				m_screen->render(x * 8 - (xScroll / 4 & 0x7), y * 8 - (yScroll / 4 & 0x7), 0, col, 0);
			}
		}
	}

	m_level->renderBackground(m_screen, xScroll, yScroll);
	m_level->renderSprites(m_screen, xScroll, yScroll);

	if(m_currentLevel < 3) {
		m_lightScreen->clear(0);
		m_level->renderLight(m_lightScreen, xScroll, yScroll);
	//	screen->overlay(lightScreen, xScroll, yScroll);
	}

	renderGui();

	if(!hasFocus()) {
		renderFocusNagger();
	}

	for(int y = 0; y < m_screen->h; ++y) {
		QRgb *line = reinterpret_cast<QRgb*>(m_image.scanLine(y));

		for(int x = 0; x < m_screen->w; ++x) {
			int cc = m_screen->pixels[x + y * m_screen->w];
			if(cc < 255) {
				line[x] = m_colors[cc];
			}
		}
	}

	QPainter p(this);
	p.drawImage(rect(), m_image);
	p.end();
}

void Game::run()
{
	qint64 lastTime = m_timer.nsecsElapsed();
	double unprocessed = 0;
	double nsPerTick = 1000000000.0 / 60;
	int frames = 0;
	int ticks = 0;
	qint64 lastTimer1 = QDateTime::currentDateTime().toMSecsSinceEpoch();

	init();

	while(m_running) {
		qint64 now = m_timer.nsecsElapsed();
		unprocessed += (now - lastTime) / nsPerTick;
		lastTime = now;

		bool shouldRender = true;
		while(unprocessed >= 1.0) {
			++ticks;

			tick();

			unprocessed -= 1.0;
			shouldRender = true;
		}

		if(shouldRender) {
			++frames;
			repaint();
		}

		if(QDateTime::currentDateTime().toMSecsSinceEpoch() - lastTimer1 > 1000) {
			lastTimer1 += 1000;

			qDebug() << ticks << "ticks," << frames << "fps";

			frames = 0;
			ticks = 0;
		}

		qApp->processEvents();
	}
}

void Game::init()
{
	int pp = 0;
	for(int r = 0; r < 6; ++r) {
		for(int g = 0; g < 6; ++g) {
			for(int b = 0; b < 6; ++b) {
				int rr = r * 255 / 5;
				int gg = g * 255 / 5;
				int bb = b * 255 / 5;
				int mid = (rr * 30 + gg * 59 + bb * 11) / 100;

				int r1 = (rr + mid) / 2 * 230 / 255 + 10;
				int g1 = (gg + mid) / 2 * 230 / 255 + 10;
				int b1 = (bb + mid) / 2 * 230 / 255 + 10;
				m_colors[pp++] = (r1 << 16 | g1 << 8 | b1);
			}
		}
	}

	QImage iconsImage(":/icons.png");
	m_screen = new Screen(Game::WIDTH, Game::HEIGHT, new SpriteSheet(iconsImage));
	m_lightScreen = new Screen(Game::WIDTH, Game::HEIGHT, new SpriteSheet(iconsImage));

	Tile::init();
	Resource::init();

	Tile::init2();
	Resource::init2();

	Crafting::init();

	resetGame();
	setMenu(new TitleMenu());
}

void Game::renderGui()
{
	for(int y = 0; y < 2; ++y) {
		for(int x = 0; x < 20; ++x) {
			m_screen->render(x * 8, m_screen->h - 16 + y * 8, 384, Color::get(0, 0, 0, 0), 0);
		}
	}

	for(int i = 0; i < 10; ++i) {
		if(i < player->health) {
			m_screen->render(i * 8, m_screen->h - 16, 384, Color::get(0, 200, 500, 533), 0);
		} else {
			m_screen->render(i * 8, m_screen->h - 16, 384, Color::get(0, 100, 0, 0), 0);
		}

		if(player->staminaRechargeDelay > 0) {
			if(player->staminaRechargeDelay / 4 % 2 == 0) {
				m_screen->render(i * 8, m_screen->h - 8, 385, Color::get(0, 555, 0, 0), 0);
			} else {
				m_screen->render(i * 8, m_screen->h - 8, 385, Color::get(0, 110, 0, 0), 0);
			}
		} else if(i < player->stamina) {
			m_screen->render(i * 8, m_screen->h - 8, 385, Color::get(0, 220, 550, 553), 0);
		} else {
			m_screen->render(i * 8, m_screen->h - 8, 385, Color::get(0, 110, 0, 0), 0);
		}
	}

	if(player->activeItem) {
		player->activeItem->renderInventory(m_screen, 80, m_screen->h - 16);
	}

	if(menu) {
		menu->render(m_screen);
	}
}

void Game::renderFocusNagger()
{
	QString msg = "Click to focus!";
	int xx = (Game::WIDTH - msg.count() * 8) / 2;
	int yy = 56;
	int w = msg.count();
	int h = 1;

	m_screen->render(xx - 8, yy - 8, 416, Color::get(-1, 1, 5, 445), 0);
	m_screen->render(xx + w * 8, yy - 8, 416, Color::get(-1, 1, 5, 445), 1);
	m_screen->render(xx - 8, yy + 8, 416, Color::get(-1, 1, 5, 445), 2);
	m_screen->render(xx + w * 8, yy + 8, 416, Color::get(-1, 1, 5, 445), 3);

	for(int x = 0; x < w; ++x) {
		m_screen->render(xx + x * 8, yy - 8, 417, Color::get(-1, 1, 5, 445), 0);
		m_screen->render(xx + x * 8, yy + 8, 417, Color::get(-1, 1, 5, 445), 2);
	}

	for(int y = 0; y < h; ++y) {
		m_screen->render(xx - 8, yy + y * 8, 418, Color::get(-1, 1, 5, 445), 0);
		m_screen->render(xx + w * 8, yy + y * 8, 418, Color::get(-1, 1, 5, 445), 1);
	}

	if(m_tickCount / 20 % 2 == 0) {
		Font::draw(msg, m_screen, xx, yy, Color::get(5, 333, 333, 333));
	} else {
		Font::draw(msg, m_screen, xx, yy, Color::get(5, 555, 555, 555));
	}
}
