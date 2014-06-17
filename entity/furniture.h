#ifndef FURNITURE_H
#define FURNITURE_H

#include <entity/entity.h>

#include <QString>

class Furniture : public Entity
{
	public:
		Furniture(QString name);

		void tick();
		void render(Screen *screen);
		bool blocks(Entity *e);
		void take(Player *player);

	public:
		int col;
		int sprite;
		QString name;

	protected:
		void touchedBy(Entity *entity);

	private:
		int m_pushTime;
		int m_pushDir;
		Player *m_shouldTake;
};

#endif
