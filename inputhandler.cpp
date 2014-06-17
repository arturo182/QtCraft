#include "inputhandler.h"

#include "game.h"

#include <QKeyEvent>
#include <QDebug>

InputHandler::InputHandler(Game *game) :
	QObject(game),
	up(new Key),
	down(new Key),
	left(new Key),
	right(new Key),
	attack(new Key),
	menu(new Key)
{
	m_keys.append(up);
	m_keys.append(down);
	m_keys.append(left);
	m_keys.append(right);
	m_keys.append(attack);
	m_keys.append(menu);

	game->installEventFilter(this);
}

void InputHandler::releaseAll()
{
	for(int i = 0; i < m_keys.count(); ++i) {
		m_keys[i]->down = false;
	}
}

void InputHandler::tick()
{
	for(int i = 0; i < m_keys.count(); ++i) {
		m_keys[i]->tick();
	}
}

bool InputHandler::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::KeyPress) {
		toggle(dynamic_cast<QKeyEvent*>(event), true);
	} else if(event->type() == QEvent::KeyRelease) {
		toggle(dynamic_cast<QKeyEvent*>(event), false);
	}

	return QObject::eventFilter(obj, event);
}

void InputHandler::toggle(QKeyEvent *event, bool pressed)
{
	if(event->key() == Qt::Key_8) up->toggle(pressed);
	if(event->key() == Qt::Key_2) down->toggle(pressed);
	if(event->key() == Qt::Key_4) left->toggle(pressed);
	if(event->key() == Qt::Key_6) right->toggle(pressed);

	if(event->key() == Qt::Key_W) up->toggle(pressed);
	if(event->key() == Qt::Key_S) down->toggle(pressed);
	if(event->key() == Qt::Key_A) left->toggle(pressed);
	if(event->key() == Qt::Key_D) right->toggle(pressed);

	if(event->key() == Qt::Key_Up) up->toggle(pressed);
	if(event->key() == Qt::Key_Down) down->toggle(pressed);
	if(event->key() == Qt::Key_Left) left->toggle(pressed);
	if(event->key() == Qt::Key_Right) right->toggle(pressed);

	if(event->key() == Qt::Key_Tab) menu->toggle(pressed);
	if(event->key() == Qt::Key_Alt) menu->toggle(pressed);
	if(event->key() == Qt::Key_AltGr) menu->toggle(pressed);
	if(event->key() == Qt::Key_Return) menu->toggle(pressed);
	if(event->key() == Qt::Key_X) menu->toggle(pressed);

	if(event->key() == Qt::Key_Space) attack->toggle(pressed);
	if(event->key() == Qt::Key_Control) attack->toggle(pressed);
	if(event->key() == Qt::Key_0) attack->toggle(pressed);
	if(event->key() == Qt::Key_Insert) attack->toggle(pressed);
	if(event->key() == Qt::Key_C) attack->toggle(pressed);
}


Key::Key() :
	presses(0),
	absorbs(0),
	down(false),
	clicked(false)
{
}

void Key::toggle(bool pressed)
{
	if(pressed != down) {
		down = pressed;
	}

	if(pressed) {
		++presses;
	}
}

void Key::tick()
{
	if(absorbs < presses) {
		++absorbs;

		clicked = true;
	} else {
		clicked = false;
	}
}
