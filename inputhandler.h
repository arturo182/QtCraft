#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>

class QKeyEvent;
class Game;
class Key;

class InputHandler : public QObject
{
	Q_OBJECT

	public:
		InputHandler(Game *game = 0);

		void releaseAll();
		void tick();

	public:
		Key *up;
		Key *down;
		Key *left;
		Key *right;
		Key *attack;
		Key *menu;

	protected:
		bool eventFilter(QObject *obj, QEvent *event);

	private:
		void toggle(QKeyEvent *event, bool pressed);

	private:
		QList<Key*> m_keys;
};


class Key
{
	public:
		Key();

		void toggle(bool pressed);
		void tick();

	public:
		int presses;
		int absorbs;
		bool down;
		bool clicked;
};

#endif
