#include "textparticle.h"

#include <gaussianrand.h>
#include <gfx/color.h>
#include <gfx/font.h>

TextParticle::TextParticle(QString msg, int x, int y, int col) :
	m_time(0)
{
	init(msg, x, y, col);
}

TextParticle::TextParticle(int msg, int x, int y, int col) :
	m_time(0)
{
	init(QString::number(msg), x, y, col);
}

void TextParticle::tick()
{
	++m_time;
	if(m_time > 60) {
	  remove();
	}

	xx += xa;
	yy += ya;
	zz += za;

	if(zz < 0.0) {
	  zz = 0.0;
	  za *= -0.5;
	  xa *= 0.6;
	  ya *= 0.6;
	}

	za -= 0.15;
	x = xx;
	y = yy;
}

void TextParticle::render(Screen *screen)
{
	Font::draw(m_msg, screen, x - m_msg.count() * 4 + 1, y - zz + 1, Color::get(-1, 0, 0, 0));
	Font::draw(m_msg, screen, x - m_msg.count() * 4, y - zz, m_col);
}

void TextParticle::init(QString msg, int x, int y, int col)
{
	this->x = x;
	this->y = y;
	m_msg = msg;
	m_col = col;

	xx = x;
	yy = y;
	zz = 2.0;

	xa = (GaussianRand::next() * 0.3);
	ya = (GaussianRand::next() * 0.2);
	za = ((qrand() / (float)RAND_MAX) * 0.7 + 2.0);
}
