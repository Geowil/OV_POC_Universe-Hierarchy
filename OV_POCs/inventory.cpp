#include "inventory.h"
#include "util.h"

namespace u = Util;

Inventory::Inventory() {}

void Inventory::updateItem(Item it, int pos, string op1, string op2) {
	if (op1 == "update") { invItems.at(pos).changeAmount(op2, it.getIAmt()); }
	else if (op1 == "add") { invItems.push_back(Item(it.getID(), it.getName(), it.getDesc(), it.getType(), it.getIAmt(), it.getSG2())); }
	else if (op1 == "remove") { invItems.erase(invItems.begin() + pos); }
}

void Inventory::updateMaxSlots(string op, int val) { invMaxSlots = u::updateVal(op, val, invMaxSlots); }
void Inventory::updateMaxSG2(string op, float val) { invMaxSG2 = u::updateVal(op, val, invMaxSG2); }
int Inventory::getMaxSlots() { return invMaxSlots; }
float Inventory::getMaxSG2() { return invMaxSG2; }
vector<Item> Inventory::getItems() { return invItems; }