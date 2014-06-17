#include "tooltype.h"

ToolType *ToolType::shovel = new ToolType("Shvl", 0);
ToolType *ToolType::hoe = new ToolType("Hoe", 1);
ToolType *ToolType::sword = new ToolType("Swrd", 2);
ToolType *ToolType::pickaxe = new ToolType("Pick", 3);
ToolType *ToolType::axe = new ToolType("Axe", 4);

ToolType::ToolType(QString name, int sprite)
{
	this->name = name;
	this->sprite = sprite;
}
