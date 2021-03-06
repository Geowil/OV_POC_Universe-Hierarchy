#include "universe.h"
#include "util.h"
#include "settings.h"
#include "dataSystem.h"

namespace u = Util;
namespace setting = Settings;

dataSystem ds_unv;

Universe::Universe() {
	ds_unv.openDB();
}

void Universe::createUniverse() {
	uNOfExp = 1;
	uTTNextExp = calculateExpTime();
	uTSLastExp = 0;

	loadSystemNames();
	createPlSystems();
}

void Universe::loadSystemNames() {
	ds_unv.prepQuery("SysNames", "select from", 0, u::blankCond);
	tempSysNms = ds_unv.getSysNames();

	for (strcSysName sName : tempSysNms) {
		uSysNames.push_back(sName.name);  //Eventually will need to add handling for loading saves to remove used names
	}
}

void Universe::createPlSystems() {
	for (int i1 = 0; i1 < setting::unvStartSystems; i1++) {				
		sysNmEl = u::getIRand(0, uSysNames.size() - 1);
		
		sec = u::getFRand(0.45f, 1.0f);

		curSysName = uSysNames.at(sysNmEl);
		addSystem(curSysName);

		uSysNames.erase(uSysNames.begin() + sysNmEl); //Remove the system name from the pool once it has been used
	}

	setupSystems();
}

planetarySystem Universe::getSystem(int index) { return uSystems.at(index); }
vector<planetarySystem> Universe::getSystems() { return uSystems; }
void Universe::addSystem(string name) { uSystems.push_back(planetarySystem(name,sec)); }
void Universe::updateSystem(planetarySystem plSys) {
	for (int i1 = 0; i1 < uSystems.size(); i1++) {
		if (i1 == uSystems.size() - 1 && uSystems[i1].getName() != plSys.getName()) {
			u::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Planetary system " + plSys.getName() + " not found in universe.", "./OV_Log.txt");
		}
		else if (uSystems[i1].getName() == plSys.getName()) {
			uSystems[i1] = plSys;
			break; //Found and updated, no longer need to loop
		}
	}
}

void Universe::updateExpTime(int tick, string operation) {}
int Universe::calculateExpTime() { return 0; }
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
