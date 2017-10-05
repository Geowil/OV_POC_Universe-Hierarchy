#ifndef INVENTORY__H
#define INVENTORY__H

#include <string>
#include <vector>
#include "item.h"

using std::string;
using std::vector;

class Inventory {
public:
	Inventory();

	void changeInventory(string operation, int index, int amount);
	void addNewItem(int id, int amt, string type);
	void removeItem(int index);
	vector<Item> getItems();

private:
	vector<Item> invItems;
};
#endif