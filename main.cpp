#include "universe.h"
#include "save.h"
#include "load.h"
#include <iostream>

using namespace std;

Universe uni;

int main() {

	uni.createUniverse();
	uni.createPlSystems();

	cout << "There are " << uni.getSystems().size() << " planetary systems in the game universe..." << endl;

	return 0;
}