#include "store.h"

Store::Store() {}
Store::Store(string name, string type) {
	oName = name;
	oType = type;
}

Store::Store(int id, string name, string type, vector<Item> items) {
	oID = id;
	oName = name;
	oType = type;

	addInventory(items);
}

void Store::addInventory(vector<Item> newInv) {
	for (Item inv : newInv) {
		sInv.updateItem(inv,-1,"add","");
	}
}

void Store::updateInventory(int pos, Item it, string op1, string op2) { sInv.updateItem(it, pos, op1, op2); }
vector<Item> Store::getItems() { return sInv.getItems(); }

