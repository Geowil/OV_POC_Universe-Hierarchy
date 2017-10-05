#include "inventory.h"

Inventory::Inventory() {}

void Inventory::changeInventory(string operation, int index, int amount) {
		invItems.at(index).changeAmount(operation, amount);
}

void Inventory::removeItem(int index) {
	invItems.erase(invItems.begin()+index);
}

void Inventory::addNewItem(int id, int amt, string type) {
	invItems.push_back(Item(id, amt, type));
}

vector<Item> Inventory::getItems() {
	return invItems;
}