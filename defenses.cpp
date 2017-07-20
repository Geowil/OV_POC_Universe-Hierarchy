#include "defenses.h"

Defense::Defense() {}

Defense::Defense(string name) {
	dName = name;
}

Defense* Defense::rDefense() {
	return this;
}

string Defense::getName() {
	return dName;
}

//Shield Functions
Shield::Shield() {}

Shield::Shield(string name) {
	mName = name;
}

Shield* Shield::rShield() {
	return this;
}

string Shield::getName() {
	return mName;
}

