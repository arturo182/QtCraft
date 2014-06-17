#include "screen.h"

#include <gfx/spritesheet.h>

#include <QDebug>

int Screen::BIT_MIRROR_X = 1;
int Screen::BIT_MIRROR_Y = 2;

Screen::Screen(int w, int h, SpriteSheet *sheet) :
	xOffset(0),
	yOffset(0),
	m_dither(QVector<quint32>() << 0 << 8 << 2 << 10 << 12 << 4 << 14 << 6 << 3 << 11 << 1 << 9 << 15 << 7 << 13 << 5 )
{
	m_sheet = sheet;
	this->w = w;
	this->h = h;

	pixels = QVector<quint32>(w * h);
}

void Screen::clear(int color)
{
	for(int i = 0; i < pixels.size(); ++i) {
		pixels[i] = color;
	}
}

void Screen::render(int xp, int yp, int tile, int colors, int bits)
{
	xp -= xOffset;
	yp -= yOffset;

	bool mirrorX = (bits & 0x1) > 0;
	bool mirrorY = (bits & 0x2) > 0;

	int xTile = tile % 32;
	int yTile = tile / 32;
	int toffs = xTile * 8 + yTile * 8 * m_sheet->width;

	for(int y = 0; y < 8; ++y) {
		int ys = y;

		if(mirrorY) {
			ys = 7 - y;
		}

		if((y + yp >= 0) && (y + yp < h)) {
			for(int x = 0; x < 8; ++x) {
				if((x + xp >= 0) && (x + xp < w)) {
					int xs = x;

					if(mirrorX) {
						xs = 7 - x;
					}

					int col = colors >> m_sheet->pixels[xs + ys * m_sheet->width + toffs] * 8 & 0xFF;
					if(col < 255) {
						pixels[x + xp + (y + yp) * w] = col;
					}
				}
			}
		}
	}
}

void Screen::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Screen::overlay(Screen *screen2, int xa, int ya)
{
	QVector<quint32> oPixels = screen2->pixels;
	int i = 0;

	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < w; ++x) {
			if(oPixels[i] / 10 <= m_dither[(((x + xa) & 0x3) + ((y + ya) & 0x3) * 4)]) {
				pixels[i] = 0;
			}

			++i;
		}
	}
}

void Screen::renderLight(int x, int y, int r)
{
	x -= xOffset;
	y -= yOffset;

	int x0 = x - r;
	int x1 = x + r;
	int y0 = y - r;
	int y1 = y + r;

	if(x0 < 0) x0 = 0;
	if(y0 < 0) y0 = 0;
	if(x1 > w) x1 = w;
	if(y1 > h) y1 = h;

	for(int yy = y0; yy < y1; ++yy) {
		int yd = yy - y;
		yd *= yd;

		for(int xx = x0; xx < x1; ++xx) {
			int xd = xx - x;
			int dist = xd * xd + yd;

			if(dist <= r * r) {
				quint32 br = 255 - dist * 255 / (r * r);

				if(pixels[(xx + yy * w)] < br) {
					pixels[(xx + yy * w)] = br;
				}
			}
		}
	}
}
