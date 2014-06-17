#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <screen/menu.h>

#include <QStringList>

class TitleMenu : public Menu
{
	public:
		TitleMenu();

		void tick();
		void render(Screen *screen);

	private:
		int m_selected;
		QStringList m_options;
};

#endif
