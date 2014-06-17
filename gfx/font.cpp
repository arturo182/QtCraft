#include "font.h"

#include <gfx/screen.h>
#include <gfx/color.h>

QString Font::chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ      0123456789.,!?'\"-+=/\\%()<>:;     ";

void Font::draw(QString msg, Screen *screen, int x, int y, int col)
{
	msg = msg.toUpper();

	for(int i = 0; i < msg.count(); ++i) {
		int ix = chars.indexOf(msg[i]);

		if(ix >= 0) {
			screen->render(x + i * 8, y, ix + 960, col, 0);
		}
	}
}

void Font::draw(int msg, Screen *screen, int x, int y, int col)
{
	draw(QString::number(msg), screen, x, y, col);
}

void Font::renderFrame(Screen *screen, QString title, int x0, int y0, int x1, int y1)
{
	for(int y = y0; y <= y1; ++y) {
		for(int x = x0; x <= x1; ++x) {
			if((x == x0) && (y == y0)) {
				screen->render(x * 8, y * 8, 416, Color::get(-1, 1, 5, 445), 0);
			} else if((x == x1) && (y == y0)) {
				screen->render(x * 8, y * 8, 416, Color::get(-1, 1, 5, 445), 1);
			} else if((x == x0) && (y == y1)) {
				screen->render(x * 8, y * 8, 416, Color::get(-1, 1, 5, 445), 2);
			} else if((x == x1) && (y == y1)) {
				screen->render(x * 8, y * 8, 416, Color::get(-1, 1, 5, 445), 3);
			} else if(y == y0) {
				screen->render(x * 8, y * 8, 417, Color::get(-1, 1, 5, 445), 0);
			} else if(y == y1) {
				screen->render(x * 8, y * 8, 417, Color::get(-1, 1, 5, 445), 2);
			} else if(x == x0) {
				screen->render(x * 8, y * 8, 418, Color::get(-1, 1, 5, 445), 0);
			} else if(x == x1) {
				screen->render(x * 8, y * 8, 418, Color::get(-1, 1, 5, 445), 1);
			} else {
				screen->render(x * 8, y * 8, 418, Color::get(5, 5, 5, 5), 1);
			}
		}
	}

	draw(title, screen, x0 * 8 + 8, y0 * 8, Color::get(5, 5, 5, 550));
}
