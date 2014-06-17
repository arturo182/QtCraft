#ifndef LEVELGEN_H
#define LEVELGEN_H

#include <QVector>

class LevelGen
{
	public:
		static QVector<QVector<qint8> > createAndValidateTopMap(int w, int h);
		static QVector<QVector<qint8> > createAndValidateUndergroundMap(int w, int h, int depth);
		static QVector<QVector<qint8> > createAndValidateSkyMap(int w, int h);

	public:
		LevelGen(int w, int h, int featureSize);

	public:
		QVector<double> values;

	private:
		static QVector<QVector<qint8> > createTopMap(int w, int h);
		static QVector<QVector<qint8> > createUndergroundMap(int w, int h, int depth);
		static QVector<QVector<qint8> > createSkyMap(int w, int h);

	private:
		double sample(int x, int y) const;
		void setSample(int x, int y, double value);

	private:
		int m_w;
		int m_h;
};

#endif
