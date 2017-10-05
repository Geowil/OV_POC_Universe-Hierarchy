#ifndef STORE__H
#define STORE__H

#include <string>
#include <vector>
#include <utility>
#include "object.h"
#include "inventory.h"
#include "dataStructs.h"

using std::string;
using std::vector;
using std::pair;

class Store : public Object{
public:
	Store();
	Store(string name);

	void addInventory(vector<invSetup> newInv); //Add new items to inventory
	vector<Item> getItems();

private:
	Inventory sInv;

};

#endif