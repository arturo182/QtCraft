#include "inventory.h"

#include <item/resourceitem.h>
#include <item/item.h>

void Inventory::add(Item *item)
{
	items.append(item);
}

void Inventory::add(int slot, Item *item)
{
	if(ResourceItem *toTake = dynamic_cast<ResourceItem*>(item)) {
		ResourceItem *has = findResource(toTake->resource);

		if(has) {
			has->count += toTake->count;
		} else {
			items.insert(slot, toTake);
		}
	} else {
		items.insert(slot, item);
	}
}

int Inventory::count(Item *item)
{
	if(ResourceItem *res = dynamic_cast<ResourceItem*>(item)) {
		ResourceItem *ri = findResource(res->resource);
		if(ri) {
			return ri->count;
		}
	} else {
		int count = 0;

		for(int i = 0; i < items.size(); ++i) {
			if(items[i]->matches(item)) {
				++count;
			}
		}

		return count;
	}

	return 0;
}

bool Inventory::hasResources(Resource *r, int count)
{
	ResourceItem *ri = findResource(r);
	if(!ri) {
		return false;
	}

	return (ri->count >= count);
}

bool Inventory::removeResource(Resource *r, int count)
{
	ResourceItem *ri = findResource(r);
	if(!ri) {
		return false;
	}

	if(ri->count < count) {
		return false;
	}

	ri->count -= count;

	if(ri->count <= 0) {
		items.removeAll(ri);
	}

	return true;
}

ResourceItem *Inventory::findResource(Resource *resource)
{
	for(int i = 0; i < items.size(); ++i) {
		if(ResourceItem *has = dynamic_cast<ResourceItem*>(items[i])) {
			if(has->resource == resource) {
				return has;
			}
		}
	}

	return 0;
}
