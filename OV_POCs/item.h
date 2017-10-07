#ifndef ITEM__H
#define ITEM__H

#include <string>

using std::string;

class Item {
public:
	Item();
	Item(int id, int amount, string type);

	void changeAmount(string operation, int amount);

private:
	int iID;
	int iAmt;
	string iType;
};
#endif