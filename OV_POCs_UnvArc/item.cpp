#include "item.h"

Item::Item() {}

Item::Item(int id, int amount, string type) {
	iID = id;
	iAmt = amount;
	iType = type;
}

void Item::changeAmount(string operation, int amount) {
	if (operation == "add") {
		iAmt += amount;
	} else if (operation == "sub") {
		iAmt -= amount;
	} else if (operation == "set") {
		iAmt = amount;
	}
}