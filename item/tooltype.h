#ifndef TOOLTYPE_H
#define TOOLTYPE_H

#include <QString>

class ToolType
{
	public:
		static ToolType *shovel;
		static ToolType *hoe;
		static ToolType *sword;
		static ToolType *pickaxe;
		static ToolType *axe;

	public:
		QString name;
		int sprite;

	private:
		ToolType(QString name, int sprite);
};

#endif
