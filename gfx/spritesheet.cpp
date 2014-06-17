#include "spritesheet.h"

SpriteSheet::SpriteSheet(const QImage &image)
{
	width = image.width();
	height = image.height();

	pixels = QVector<QRgb>(width * height);
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			pixels[x + y * width] = image.pixel(x, y) / 64;
		}
	}
}
