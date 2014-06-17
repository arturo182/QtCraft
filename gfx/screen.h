#ifndef SCREEN_H
#define SCREEN_H

#include <QVector>
#include <QColor>

class SpriteSheet;

class Screen
{
	public:
		static int BIT_MIRROR_X;
		static int BIT_MIRROR_Y;

	public:
		Screen(int w, int h, SpriteSheet *sheet);

		void clear(int color);
		void render(int xp, int yp, int tile, int colors, int bits);
		void setOffset(int xOffset, int yOffset);
		void overlay(Screen *screen2, int xa, int ya);
		void renderLight(int x, int y, int r);

	public:
		int xOffset;
		int yOffset;
		int w;
		int h;
		QVector<QRgb> pixels;

	private:
		SpriteSheet *m_sheet;
		QVector<quint32> m_dither;

};

#endif
