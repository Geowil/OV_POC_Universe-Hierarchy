#ifndef STORE__H
#define STORE__H

#include <string>
#include <vector>
#include <utility>
#include "object.h"
#include "inventory.h"

using std::string;
using std::vector;

class Store : public Object{
public:
	Store();
	Store(string name, string type);
	Store(int id, string name, string type, vector<Item> items); //Loading

	void addInventory(vector<Item> newInv); //Add new items to inventory
	void updateInventory(int pos, Item it, string op1, string op2);
	vector<Item> getItems();

private:
	Inventory sInv;

};

#endif