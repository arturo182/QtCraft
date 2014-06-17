#ifndef GAUSSIANRAND_H
#define GAUSSIANRAND_H

#include <qmath.h>

class GaussianRand
{
	public:
		static double next()
		{
			if(haveNextNextGaussian) {
				haveNextNextGaussian = false;
				return nextNextGaussian;
			} else {
				double v1, v2, s;
				do {
					v1 = 2 * (qrand() / (float)RAND_MAX) - 1;
					v2 = 2 * (qrand() / (float)RAND_MAX) - 1;
					s = v1 * v1 + v2 * v2;
				} while (s >= 1 || s == 0);

				double multiplier = qSqrt(-2 * qLn(s) / s);
				nextNextGaussian = v2 * multiplier;
				haveNextNextGaussian = true;

				return v1 * multiplier;
			}
		}

	private:
		static bool haveNextNextGaussian;
		static double nextNextGaussian;
};


#endif
