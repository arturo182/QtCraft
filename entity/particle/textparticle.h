#ifndef TEXTPARTICLE_H
#define TEXTPARTICLE_H

#include <entity/entity.h>

#include <qmath.h>
#include <QString>

class TextParticle : public Entity
{
	public:
		TextParticle(QString msg, int x, int y, int col);
		TextParticle(int msg, int x, int y, int col);

		void tick();
		void render(Screen *screen);

	public:
		double xa;
		double ya;
		double za;
		double xx;
		double yy;
		double zz;

	private:
		void init(QString msg, int x, int y, int col);

	private:
		QString m_msg;
		int m_time;
		int m_col;
};

#endif
