#ifndef ITEM__H
#define ITEM__H

#include <string>
#include "object.h"

using std::string;

class Item : public Object{
public:
	Item();
	Item(int id, string name, string desc, string type, int amount, float sg2);

	void changeAmount(string operation, int amount);
	int getIAmt();

private:
	int iAmt;
};
#endif