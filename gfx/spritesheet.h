#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QVector>
#include <QImage>

class SpriteSheet
{
	public:
		SpriteSheet(const QImage &image);

	public:
		int width;
		int height;
		QVector<QRgb> pixels;
};

#endif
