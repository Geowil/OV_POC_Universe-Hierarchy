#include "moon.h"

Moon::Moon() {}

Moon::Moon(string name) {
	mName = name;
}

string Moon::getName() {
	return mName;
}

void Moon::setName(string name) {
	mName = name;
}