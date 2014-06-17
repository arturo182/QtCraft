#ifndef FONT_H
#define FONT_H

#include <QString>

class Screen;

class Font
{
	public:
		static QString chars;

		static void draw(QString msg, Screen *screen, int x, int y, int col);
		static void draw(int msg, Screen *screen, int x, int y, int col);
		static void renderFrame(Screen *screen, QString title, int x0, int y0, int x1, int y1);
};

#endif
