#include "levelgen.h"

#include <level/tile/tile.h>

#include <QDebug>

QVector<QVector<qint8> > LevelGen::createAndValidateTopMap(int w, int h)
{
	QVector<QVector<qint8> > result;
	QVector<int> count;

	do {
		result = createTopMap(w, h);

		count = QVector<int>(256);

		for(int i = 0; i < w * h; ++i) {
			++count[(result[0][i] & 0xFF)];
		}

	} while((count[(Tile::rock->id & 0xFF)] < 100) ||
			(count[(Tile::sand->id & 0xFF)] < 100) ||
			(count[(Tile::grass->id & 0xFF)] < 100)  ||
			(count[(Tile::tree->id & 0xFF)] < 100) ||
			(count[(Tile::stairsDown->id & 0xFF)] < 2));

	return result;
}

QVector<QVector<qint8> > LevelGen::createAndValidateUndergroundMap(int w, int h, int depth)
{
	QVector<QVector<qint8> > result;
	QVector<int> count;
	do {
		result = createUndergroundMap(w, h, depth);

		count = QVector<int>(256);

		for(int i = 0; i < w * h; ++i) {
			++count[(result[0][i] & 0xFF)];
		}
	} while((count[(Tile::rock->id & 0xFF)] < 100) ||
			(count[(Tile::dirt->id & 0xFF)] < 100) ||
			(count[((Tile::ironOre->id & 0xFF) + depth - 1)] < 20) ||
			((depth < 3) && (count[(Tile::stairsDown->id & 0xFF)] < 2)));

	return result;
}

QVector<QVector<qint8> > LevelGen::createAndValidateSkyMap(int w, int h)
{
	QVector<QVector<qint8> > result;
	QVector<int> count;

	do {
		result = createSkyMap(w, h);

		count = QVector<int>(256);

		for(int i = 0; i < w * h; ++i) {
			++count[(result[0][i] & 0xFF)];
		}
	} while((count[(Tile::cloud->id & 0xFF)] < 2000) ||
			(count[(Tile::stairsDown->id & 0xFF)] < 2));

	return result;
}

LevelGen::LevelGen(int w, int h, int featureSize)
{
	m_w = w;
	m_h = h;

	values = QVector<double>(w * h);

	for(int y = 0; y < w; y += featureSize) {
		for(int x = 0; x < w; x += featureSize) {
			setSample(x, y, (qrand() / (double)RAND_MAX) * 2.0 - 1.0);
		}
	}

	int stepSize = featureSize;
	double scale = 1.0 / w;
	double scaleMod = 1.0;

	do {
		int halfStep = stepSize / 2;

		for(int y = 0; y < w; y += stepSize) {
			for(int x = 0; x < w; x += stepSize) {
				double a = sample(x, y);
				double b = sample(x + stepSize, y);
				double c = sample(x, y + stepSize);
				double d = sample(x + stepSize, y + stepSize);

				double e = (a + b + c + d) / 4.0D + ((qrand() / (double)RAND_MAX) * 2.0 - 1.0) * stepSize * scale;
				setSample(x + halfStep, y + halfStep, e);
			}
		}

		for(int y = 0; y < w; y += stepSize) {
			for(int x = 0; x < w; x += stepSize) {
				double a = sample(x, y);
				double b = sample(x + stepSize, y);
				double c = sample(x, y + stepSize);
				double d = sample(x + halfStep, y + halfStep);
				double e = sample(x + halfStep, y - halfStep);
				double f = sample(x - halfStep, y + halfStep);

				double H = (a + b + d + e) / 4.0 + ((qrand() / (double)RAND_MAX) * 2.0 - 1.0) * stepSize * scale * 0.5;
				double g = (a + c + d + f) / 4.0 + ((qrand() / (double)RAND_MAX) * 2.0 - 1.0) * stepSize * scale * 0.5;
				setSample(x + halfStep, y, H);
				setSample(x, y + halfStep, g);
			}
		}

		stepSize /= 2;
		scale *= (scaleMod + 0.8);
		scaleMod *= 0.3;
	} while(stepSize > 1);
}

QVector<QVector<qint8> > LevelGen::createTopMap(int w, int h)
{
	LevelGen mnoise1(w, h, 16);
	LevelGen mnoise2(w, h, 16);
	LevelGen mnoise3(w, h, 16);

	LevelGen noise1(w, h, 32);
	LevelGen noise2(w, h, 32);

	QVector<qint8> map(w * h, 0);
	QVector<qint8> data(w * h, 0);
	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < w; ++x) {
			int i = x + y * w;

			double val = qAbs(noise1.values[i] - noise2.values[i]) * 3.0 - 2.0;
			double mval = qAbs(mnoise1.values[i] - mnoise2.values[i]);
			mval = qAbs(mval - mnoise3.values[i]) * 3.0 - 2.0;

			double xd = x / (w - 1.0) * 2.0 - 1.0;
			double yd = y / (h - 1.0) * 2.0 - 1.0;

			if(xd < 0.0) {
				xd = -xd;
			}

			if(yd < 0.0) {
				yd = -yd;
			}

			double dist = (xd < yd) ? yd : xd;
			dist = dist * dist * dist * dist;
			dist = dist * dist * dist * dist;
			val = val + 1.0 - dist * 20.0;

			if(val < -0.5) {
				map[i] = Tile::water->id;
			} else if((val > 0.5) && (mval < -1.5)) {
				map[i] = Tile::rock->id;
			} else {
				map[i] = Tile::grass->id;
			}
		}
	}

	for(int i = 0; i < w * h / 2800; ++i) {
		int xs = qrand() % w;
		int ys = qrand() % h;

		for(int k = 0; k < 10; ++k) {
			int x = xs + qrand() % 21 - 10;
			int y = ys + qrand() % 21 - 10;

			for(int j = 0; j < 100; ++j) {
				int xo = x + qrand() % 5 - qrand() % 5;
				int yo = y + qrand() % 5 - qrand() % 5;

				for(int yy = yo - 1; yy <= yo + 1; ++yy) {
					for(int xx = xo - 1; xx <= xo + 1; ++xx) {
						if((xx >= 0) && (yy >= 0) && (xx < w) && (yy < h)) {
							if(map[(xx + yy * w)] == Tile::grass->id) {
								map[(xx + yy * w)] = Tile::sand->id;
							}
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < w * h / 400; ++i) {
		int x = qrand() % w;
		int y = qrand() % h;

		for(int j = 0; j < 200; ++j) {
			int xx = x + qrand() % 15 - qrand() % 15;
			int yy = y + qrand() % 15 - qrand() % 15;

			if((xx >= 0) && (yy >= 0) && (xx < w) && (yy < h)) {
				if(map[(xx + yy * w)] == Tile::grass->id) {
					map[(xx + yy * w)] = Tile::tree->id;
				}
			}
		}

	}

	for(int i = 0; i < w * h / 400; ++i) {
		int x = qrand() % w;
		int y = qrand() % h;
		int col = qrand() % 4;

		for(int j = 0; j < 30; ++j) {
			int xx = x + qrand() % 5 - qrand() % 5;
			int yy = y + qrand() % 5 - qrand() % 5;

			if((xx >= 0) && (yy >= 0) && (xx < w) && (yy < h)) {
				if(map[(xx + yy * w)] == Tile::grass->id) {
					map[(xx + yy * w)] = Tile::flower->id;
					data[(xx + yy * w)] = (col + (qrand() % 4) * 16);
				}
			}
		}
	}


	for(int i = 0; i < w * h / 100; ++i) {
		int xx = qrand() % w;
		int yy = qrand() % h;

		if((xx >= 0) && (yy >= 0) && (xx < w) && (yy < h)) {
			if(map[(xx + yy * w)] == Tile::sand->id) {
				map[(xx + yy * w)] = Tile::cactus->id;
			}
		}
	}

	int count = 0;
	for(int i = 0; i < w * h / 100; ++i) {
stairsLoop:

		int x = qrand() % (w - 2) + 1;
		int y = qrand() % (h - 2) + 1;

		for(int yy = y - 1; yy <= y + 1; ++yy) {
			for(int xx = x - 1; xx <= x + 1; ++xx) {
				if(map[xx + yy * w] != Tile::rock->id) {
					goto stairsLoop;
				}
			}
		}

		map[x + y * w] = Tile::stairsDown->id;
		if(++count == 4) {
			break;
		}
	}

	QVector<QVector<qint8> > result;
	result.push_back(map);
	result.push_back(data);

	return result;
}

QVector<QVector<qint8> > LevelGen::createUndergroundMap(int w, int h, int depth)
{
	LevelGen mnoise1(w, h, 16);
	LevelGen mnoise2(w, h, 16);
	LevelGen mnoise3(w, h, 16);

	LevelGen nnoise1(w, h, 16);
	LevelGen nnoise2(w, h, 16);
	LevelGen nnoise3(w, h, 16);

	LevelGen wnoise1(w, h, 16);
	LevelGen wnoise2(w, h, 16);
	LevelGen wnoise3(w, h, 16);

	LevelGen noise1(w, h, 32);
	LevelGen noise2(w, h, 32);

	QVector<qint8> map(w * h);
	QVector<qint8> data(w * h);

	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < w; ++x) {
			int i = x + y * w;

			double val = qAbs(noise1.values[i] - noise2.values[i]) * 3.0 - 2.0;

			double mval = qAbs(mnoise1.values[i] - mnoise2.values[i]);
			mval = qAbs(mval - mnoise3.values[i]) * 3.0 - 2.0;

			double nval = qAbs(nnoise1.values[i] - nnoise2.values[i]);
			nval = qAbs(nval - nnoise3.values[i]) * 3.0 - 2.0;

			double wval = qAbs(wnoise1.values[i] - wnoise2.values[i]);
			wval = qAbs(nval - wnoise3.values[i]) * 3.0 - 2.0;

			double xd = x / (w - 1.0) * 2.0 - 1.0;
			double yd = y / (h - 1.0) * 2.0 - 1.0;

			if(xd < 0.0) {
				xd = -xd;
			}

			if(yd < 0.0) {
				yd = -yd;
			}

			double dist = xd >= yd ? xd : yd;
			dist = dist * dist * dist * dist;
			dist = dist * dist * dist * dist;
			val = val + 1.0 - dist * 20.0;

			if((val > -2.0) && (wval < -2.0 + depth / 2 * 3)) {
				if(depth > 2) {
					map[i] = Tile::lava->id;
				} else {
					map[i] = Tile::water->id;
				}
			} else if((val > -2.0) && ((mval < -1.7) || (nval < -1.4))) {
				map[i] = Tile::dirt->id;
			} else {
				map[i] = Tile::rock->id;
			}
		}
	}

	int r = 2;
	for(int i = 0; i < w * h / 400; ++i) {
		int x = qrand() % w;
		int y = qrand() % h;

		for(int j = 0; j < 30; ++j) {
			int xx = x + qrand() % 5 - qrand() % 5;
			int yy = y + qrand() % 5 - qrand() % 5;

			if((xx >= r) && (yy >= r) && (xx < w - r) && (yy < h -r)) {
				if(map[(xx + yy * w)] == Tile::rock->id) {
					map[(xx + yy * w)] = (Tile::ironOre->id & 0xFF) + depth - 1;
				}
			}
		}
	}

	if(depth < 3) {
		int count = 0;
		for (int i = 0; i < w * h / 100; ++i) {
stairsLoop:

			int x = qrand() % (w - 20) + 10;
			int y = qrand() % (h - 20) + 10;

			for(int yy = y - 1; yy <= y + 1; ++yy)
				for(int xx = x - 1; xx <= x + 1; ++xx) {
					if(map[xx + yy * w] != Tile::rock->id) {
						goto stairsLoop;
					}
				}

			map[x + y * w] = Tile::stairsDown->id;
			++count;

			if(count == 4) {
				break;
			}
		}
	}

	QVector<QVector<qint8> > result;
	result.push_back(map);
	result.push_back(data);

	return result;
}

QVector<QVector<qint8> > LevelGen::createSkyMap(int w, int h)
{
	LevelGen noise1(w, h, 8);
	LevelGen noise2(w, h, 8);

	QVector<qint8> map(w * h);
	QVector<qint8> data(w * h);

	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < w; ++x) {
			int i = x + y * w;

			double val = qAbs(noise1.values[i] - noise2.values[i]) * 3.0 - 2.0;

			double xd = x / (w - 1.0) * 2.0 - 1.0;
			double yd = y / (h - 1.0) * 2.0 - 1.0;

			if(xd < 0.0) {
				xd = -xd;
			}

			if(yd < 0.0) {
				yd = -yd;
			}

			double dist = (xd >= yd) ? xd : yd;
			dist = dist * dist * dist * dist;
			dist = dist * dist * dist * dist;
			val = -val * 1.0 - 2.2;
			val = val + 1.0 - dist * 20.0;

			if(val < -0.25) {
				map[i] = Tile::infiniteFall->id;
			} else {
				map[i] = Tile::cloud->id;
			}
		}
	}

	for(int i = 0; i < w * h / 50; ++i) {
cactusLoop:

		int x = qrand() % (w - 2) + 1;
		int y = qrand() % (h - 2) + 1;

		for(int yy = y - 1; yy <= y + 1; yy++)
			for(int xx = x - 1; xx <= x + 1; xx++) {
				if (map[xx + yy * w] != Tile::cloud->id) {
					goto cactusLoop;
				}
			}

		map[x + y * w] = Tile::cloudCactus->id;
	}

	int count = 0;
	for(int i = 0; i < w * h; i++) {
stairsLoop:

		int x = qrand() % (w - 2) + 1;
		int y = qrand() % (h - 2) + 1;

		for(int yy = y - 1; yy <= y + 1; ++yy)
			for(int xx = x - 1; xx <= x + 1; ++xx) {
				if(map[xx + yy * w] != Tile::cloud->id) {
					goto stairsLoop;
				}
			}

		map[x + y * w] = Tile::stairsDown->id;
		++count;

		if(count == 2) {
			break;
		}
	}

	QVector<QVector<qint8> > result;
	result.push_back(map);
	result.push_back(data);

	return result;
}

double LevelGen::sample(int x, int y) const
{
	return values[((x & (m_w - 1)) + (y & (m_h - 1)) * m_w)];
}

void LevelGen::setSample(int x, int y, double value)
{
	values[((x & (m_w - 1)) + (y & (m_h - 1)) * m_w)] = value;
}
