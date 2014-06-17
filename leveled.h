#ifndef LEVELED_H
#define LEVELED_H

#include <QWidget>

class LevelEd : public QWidget
{
	Q_OBJECT

	public:
		LevelEd(QWidget *parent = 0);

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		QImage m_image;

};

#endif
