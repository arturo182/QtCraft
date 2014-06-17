#ifndef ILISTITEM_H
#define ILISTITEM_H

class Screen;

class IListItem
{
	public:
		virtual void renderInventory(Screen *screen, const int &x, const int &y) const = 0;
};

#endif
