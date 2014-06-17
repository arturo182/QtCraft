#ifndef GAME_H
#define GAME_H

#include <QElapsedTimer>
#include <QGLWidget>
#include <QVector>

class InputHandler;
class Player;
class Screen;
class Level;
class Menu;

class Game : public QGLWidget
{
	Q_OBJECT

	public:
		static QString NAME;
		static int HEIGHT;
		static int WIDTH;

	public:
		Game(QWidget *parent = 0);

		void start();
		void stop();
		void won();
		void setMenu(Menu *menu);
		void resetGame();
		void tick();
		void scheduleLevelChange(const int &dir);
		void changeLevel(const int &dir);

	public:
		Player *player;
		Menu *menu;
		int gameTime;

	protected:
		void closeEvent(QCloseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:
		void run();
		void init();
		void renderGui();
		void renderFocusNagger();

	private:
		QElapsedTimer m_timer;
		QVector<int> m_pixels;
		bool m_running;
		QImage m_image;
		Screen *m_screen;
		Screen *m_lightScreen;
		InputHandler *m_input;
		int m_colors[256];
		int m_tickCount;
		Level *m_level;
		QList<Level*> m_levels;
		int m_currentLevel;
		int m_playerDeadTime;
		int m_pendingLevelChange;
		int m_wonTimer;
		bool m_hasWon;
};

#endif
