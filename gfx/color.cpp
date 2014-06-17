#include "color.h"

#include <QColor>
#include <QDebug>

int Color::get(const int &a, const int &b, const int &c, const int &d)
{
	int col = (get(d) << 24) + (get(c) << 16) + (get(b) << 8) + get(a);
	return col;
}

int Color::get(const int &d)
{
	if(d < 0) {
		return 255;
	}

	int r = d / 100 % 10;
	int g = d / 10 % 10;
	int b = d % 10;

	return r * 36 + g * 6 + b;
}
