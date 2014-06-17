#include "toolrecipe.h"

#include <entity/inventory.h>
#include <entity/player.h>
#include <item/toolitem.h>
#include <item/tooltype.h>

ToolRecipe::ToolRecipe(ToolType *type, int level) :
	Recipe(new ToolItem(type, level))
{
	m_type = type;
	m_level = level;
}

void ToolRecipe::craft(Player *player)
{
	player->inventory->add(0, new ToolItem(m_type, m_level));
}
