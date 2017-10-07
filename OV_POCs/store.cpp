#include "store.h"

Store::Store(){}

Store::Store(string name) {
	oName = name;
}

void Store::addInventory(vector<invSetup> newInv) {
	for (invSetup inv : newInv) {
		sInv.addNewItem(inv.iID, inv.iAmt, inv.iTyp);
	}
}

vector<Item> Store::getItems() {
	return sInv.getItems();
}

