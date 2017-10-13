#ifndef INVENTORY__H
#define INVENTORY__H

#include <string>
#include <vector>
#include "item.h"
#include "object.h"

using std::string;
using std::vector;

class Inventory : public Object {
public:
	Inventory();

	void updateItem(Item it, int pos, string op1, string op2);
	void updateMaxSlots(string op, int val);
	void updateMaxSG2(string op, float val);

	int getMaxSlots(); //For Station inv
	float getMaxSG2(); //For Station inv

	vector<Item> getItems();

private:
	vector<Item> invItems;

	int invMaxSlots; //Max number of slots (stations)
	float invMaxSG2; //Max SG2 alloted (stations)
};
#endif