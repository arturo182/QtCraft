#include <QApplication>

#include <leveled.h>
#include <game.h>
//#define LEVEL_ED

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

#ifdef LEVEL_ED
	LevelEd ed;
	ed.show();

	return app.exec();
#else
	Game game;

	game.show();
	game.start();

	return 0;
#endif
}
