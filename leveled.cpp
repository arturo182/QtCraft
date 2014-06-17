#include "leveled.h"

#include <level/tile/tile.h>
#include <level/levelgen.h>

#include <QDateTime>
#include <QPainter>
#include <item/resource.h>

LevelEd::LevelEd(QWidget *parent) :
	QWidget(parent)
{
	resize(512, 512);
	setAttribute(Qt::WA_QuitOnClose);

	qsrand(QDateTime::currentDateTime().toTime_t());

	uint col;

	int w = 128;
	int h = 128;

	Tile::init();
	Resource::init();

	Tile::init2();

	//int d = 2;
	//QVector<qint8> map = LevelGen::createAndValidateTopMap(w, h)[0];
	//QVector<qint8> map = LevelGen::createAndValidateUndergroundMap(w, h, (d++ % 3) + 1)[0];
	 QVector<qint8> map = LevelGen::createAndValidateSkyMap(w, h)[0];

	m_image = QImage(w, h, QImage::Format_RGB32);
	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < w; ++x) {
			int i = x + y * w;

			if(map[i] == Tile::water->id) {
				col = 0x000080;
			}

			if(map[i] == Tile::grass->id) {
				col = 0x208020;
			}

			if(map[i] == Tile::rock->id) {
				col = 0xa0a0a0;
			}

			if(map[i] == Tile::dirt->id) {
				col = 0x604040;
			}

			if(map[i] == Tile::sand->id) {
				col = 0xa0a040;
			}

			if(map[i] == Tile::tree->id) {
				col = 0x003000;
			}

			if(map[i] == Tile::lava->id) {
				col = 0xff2020;
			}

			if(map[i] == Tile::cloud->id) {
				col = 0xa0a0a0;
			}

			if(map[i] == Tile::stairsDown->id) {
				col = 0xffffff;
			}

			if(map[i] == Tile::stairsUp->id) {
				col = 0xffffff;
			}

			if(map[i] == Tile::cloudCactus->id) {
				col = 0xff00ff;
			}

			m_image.setPixel(x, y, col);
		}
	}
}

void LevelEd::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawImage(rect(), m_image);
}
