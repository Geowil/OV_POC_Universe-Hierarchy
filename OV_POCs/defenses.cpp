#include "defenses.h"
#include "util.h"

Defense::Defense() {}
Defense::Defense(string name) {
	oName = name;
}

Defense* Defense::rDefense() { return this; }

//Shield Functions
Shield::Shield() {}
Shield::Shield(string name) {
	oName = name;
}

Shield* Shield::rShield() { return this; }


