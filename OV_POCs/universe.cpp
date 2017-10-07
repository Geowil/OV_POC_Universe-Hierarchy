#include "universe.h"
#include "util.h"
#include "consts.h"


Universe::Universe() {}

void Universe::createUniverse() {

	uNOfExp = 1;
	uTTNextExp = calculateExpTime();
	uTSLastExp = 0;
}

void Universe::createPlSystems() {
	int numOfSys = Util::getIRand(1, 5);

	for (int i1 = 0; i1 < numOfSys; i1++) {		
		
		string plSName = sysNames[i1];
		addSystem(plSName);
	}

	setupSystems();
}

planetarySystem Universe::getSystem(int index) {
	return uSystems.at(index);
}

vector<planetarySystem> Universe::getSystems() {
	return uSystems;
}

void Universe::addSystem(string name) {
	uSystems.push_back(planetarySystem(name));
}

void Universe::updateSystem(planetarySystem plSys) {
	for (int i1 = 0; i1 < uSystems.size(); i1++) {
		if (i1 == uSystems.size() - 1 && uSystems[i1].getName() != plSys.getName()) {
			Util::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Planetary system " + plSys.getName() + " not found in universe.", "./OV_Log.txt");
		}
		else if (uSystems[i1].getName() == plSys.getName()) {
			uSystems[i1] = plSys;
			break; //Found and updated, no longer need to loop
		}
	}
}

void Universe::updateExpTime(int tick, string operation) {
}

int Universe::calculateExpTime() {
	return 0;
}

void Universe::expansionPhase() {
	//Add code to expand universe
	//create system
	//create planets and a. belts
	//create stations, moons
	//create asteroids
}

void Universe::setupSystems() {
	for (planetarySystem& plSys : uSystems){
		plSys.createPlanets();
	}
}
