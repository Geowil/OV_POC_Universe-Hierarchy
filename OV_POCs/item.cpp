#include "item.h"
#include "util.h"

namespace u = Util;

Item::Item() {}
Item::Item(int id, string name, string desc, string type, int amount, float sg2) {
	oID = id;
	oName = name;
	oDesc = desc;
	oType = type;
	iAmt = amount;
	oSG2 = sg2;
}

void Item::changeAmount(string operation, int amount) { iAmt = u::updateVal(operation, amount, iAmt); }
int Item::getIAmt() { return iAmt; }