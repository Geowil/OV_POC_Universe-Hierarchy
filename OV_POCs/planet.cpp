#include <iostream>
#include <stdlib.h>
#include "planet.h"
#include <Windows.h>
#include <cmath>
#include "util.h"
#include "consts.h"
#include "settings.h"

namespace u = Util;
namespace setting = Settings;

//global variable defines

//Pillage EKS Multipliers

/*
move to database settings
How these work:

Multipliers is actually a misnomer.  These values take away a certain precentage of a planets randomized resource rewards.  As the EKS value gets higher, the more resources that are lost.
It is done this way to simulate the effects of attacking and pillaging the planet.  As planet sizes and EKS values increase the more destruction there has to be to pillage the planet.
This is represented here as a loss of resources when gaining though means of hostile action.

This is a resource balancing feature but will be tweakable by players/modders in future version when I move all of these hard coded defines and some other hard coded values into an ini file.

#define PV_EKS0 0.98
#define PV_EKS1 0.92
#define PV_EKS2 0.85
#define PV_EKS3 0.80
#define PV_EKS4 0.74
#define PV_EKS5	0.68*/

//Planet Functions
Planet::Planet() {}

Planet::Planet(string name, float slvl) {
	oName = name;
	oSecLvl = slvl;
	bIsDest = false;
}

Planet::Planet(string name, float eks, long long int pop, float slvl) {	
	oName = name;
	pEKS = eks;
	pMPop = pop;
	pPop = pMPop;
	bIsDest = false;
	oSecLvl = slvl;
}

Planet* Planet::getPlanet() { return this; }
float Planet::getEKS() { return pEKS; }
long long int Planet::getPop() { return pPop; }
string Planet::getPopS() {
	sStorage = to_string(pPop);
	getTrailer(sStorage);
	sPPop = to_string(popStorage);

	return sPPop + " " + trailer;
}

long long int Planet::getMPop() {
	return pMPop;
}

string Planet::getMPopS() {
	sStorage = to_string(pMPop);
	getTrailer(sStorage);
	sPMPop = to_string(popStorage);

	return sPMPop + " " + trailer;
}

float Planet::getSize() { return pSize; }
bool Planet::bPIsDest() { return bIsDest; }
void Planet::setSize(float size) { pSize = size; }
void Planet::updatePop(long long int pop, string operation) { pPop = u::updateVal(operation, pop, pPop); }
void Planet::updateMPop(long long int pop, string operation) { pMPop = u::updateVal(operation, pop, pMPop); }
void Planet::setPDest(int i) {
	if (i == 0) {
		bIsDest = false;
	} else {
		bIsDest = true;
	}
}

void Planet::setEKS(float eks) { pEKS = eks; }
void Planet::setupPlanetObjects() {
	createBelts();
	createMoons();
	createStations();
}

void Planet::createBelts() {
	numOfBelts = u::getIRand(1, setting::maxAsteroidBelts);

	if (numOfBelts != 0) {
		for (i = 1; i <= numOfBelts; i++) {
			ramount = u::getIRand(setting::abltMaxAsteroids.iLow, setting::abltMaxAsteroids.iHigh);
			size = ((ramount * u::getFRand(setting::abltSizeRandRng.fLow, setting::abltSizeRandRng.fHigh) * 46) / 2);
			name = oName + " Asteroid Belt " + rNumerals[i - 1];

			addBelt(name, size, ramount, false);
		}
	}
}

void Planet::addBelt(string name, float size, int ramount, bool full) {
	if (!full) {
		belts.push_back(aBelt(name, size, ramount, false));

		belts.at(belts.size() - 1).createAsteroids(oSecLvl);

		//Sleep(300);
	} else {
		belts.push_back(aBelt(name, size, true));
	}
}

void Planet::modifyABelt(aBelt ab) {
	for (int i1 = 0; i1 < belts.size(); i1++) {
		if (i1 == belts.size() - 1 && belts[i1].getName() != ab.getName()) {
			u::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Asteroid belt " + ab.getName() + " not found in expected system.", "./OV_Log.txt");
		}
		else if (belts[i1].getName() == ab.getName()) {
			belts[i1] = ab;
			break; //Found and updated, no longer need to loop
		}
	}
}

vector<aBelt> Planet::getABelts() {
	return belts;
}

aBelt Planet::getABelt(int index) {
	return belts.at(index);
}

void Planet::createMoons() {
	moonRand = u::getIRand(setting::mnAmtRnd.iLow, setting::mnAmtRnd.iHigh);

	for (setting::pltTypeSettings plt : setting::gPltTypSettings){
		if (pEKS >= plt.getPltEksRng().fLow && pEKS <= plt.getPltEksRng().fHigh) {
			for (i1 = 0; i1 < plt.getPltMnAmtSz() - 1; i1++) {
				if (i1 == 0 && (moonRand >= 1 && moonRand <= plt.getPltMnAmt(i1))) {
					numOfMoons = i1;
				}
				else if (i1 != 0 && (moonRand >= plt.getPltMnAmt(i1 - 1) && moonRand <= plt.getPltMnAmt(i1))) {
					numOfMoons = i1;
				}
			}
		}
	}

	if (numOfMoons != 0) {
		for (i = 1; i <= numOfMoons; i++) {
			
			name = oName + " Moon " + rNumerals[i - 1];

			addMoon(name);
		}
	}


}

void Planet::addMoon(string name) {
	moons.push_back(Moon(name));
}

void Planet::setupMoonData() {
	for (Moon& mn : moons) {
		mn.setupMoon(pEKS,oSecLvl);
	}
}

void Planet::modifyMoon(Moon m) {
	for (int i1 = 0; i1 < moons.size(); i1++) {
		if (i1 == moons.size() - 1 && moons[i1].getName() != m.getName()) {
			Util::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Moon " + m.getName() + " not found in universe.", "./OV_Log.txt");
		}
		else if (moons[i1].getName() == m.getName()) {
			moons[i1] = m;
			break; //Found and updated, no longer need to loop
		}
	}
}

vector<Moon> Planet::getMoons() {
	return moons;
}

Moon Planet::getMoon(int index) {
	return moons.at(index);
}

void Planet::createStations() {
	beltRand = Util::getIRand(0, 2);

	if (beltRand != 0) {
		for (i = 1; i <= beltRand; i++) {

			name = oName + " Station " + rNumerals[i - 1];

			addStation(name);
		}
	}
}

void Planet::addStation(string name) {
	stations.push_back(Station(name));
}

void Planet::modifyStation(Station stat) {
	for (int i1 = 0; i1 < stations.size(); i1++) {
		if (i1 == stations.size() - 1 && stations[i1].getName() != stat.getName()) {
			Util::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Station " + stat.getName() + " not found in universe.", "./OV_Log.txt");
		}
		else if (stations[i1].getName() == stat.getName()) {
			stations[i1] = stat;
			break; //Found and updated, no longer need to loop
		}
	}
}

vector<Station> Planet::getStations() {
	return stations;
}

Station Planet::getStation(int index) {
	return stations.at(index);
}

void Planet::addPDefenses(bool defense, int odid, bool shield, int psid, bool defender) {
	if (defense) {
		pDef.push_back(Defense(plDefNames[odid]));
	} else if (shield) {
		pShd.push_back(Shield(plShdNames[psid]));
	} else if (defender) {}
}

void Planet::modifyDefense(Defense def) {
	for (int i1 = 0; i1 < pDef.size(); i1++) {
		if (i1 == pDef.size() - 1 && pDef[i1].getName() != def.getName()) {
			Util::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Planetary defense " + def.getName() + " not found in universe.", "./OV_Log.txt");
		}
		else if (pDef[i1].getName() == def.getName()) {
			pDef[i1] = def;
			break; //Found and updated, no longer need to loop
		}
	}
}

vector<Defense> Planet::getDefenses() {
	return pDef;
}

Defense Planet::getDefense(int index) {
	return pDef.at(index);
}

void Planet::modifyShield(Shield shd) {
	for (int i1 = 0; i1 < pShd.size(); i1++) {
		if (i1 == pShd.size() - 1 && pShd[i1].getName() != shd.getName()) {
			Util::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Planetary shield " + shd.getName() + " not found in universe.", "./OV_Log.txt");
		}
		else if (pShd[i1].getName() == shd.getName()) {
			pShd[i1] = shd;
			break; //Found and updated, no longer need to loop
		}
	}
}

vector<Shield> Planet::getShields() {
	return pShd;
}

Shield Planet::getShield(int index) {
	return pShd.at(index);
}

void Planet::getTrailer(string pop) {
	if ((sStorage.length() >= 4) && (sStorage.length() <= 6)) {
		trailer = "K";
		popStorage = pMPop * 0.0001f;
	}
	else if ((sStorage.length() >= 7) && (sStorage.length() <= 9)) {
		trailer = "M";
		popStorage = pMPop * 0.000001f;
	}
	else if ((sStorage.length() >= 10) && (sStorage.length() <= 12)) {
		trailer = "B";
		popStorage = pMPop * 0.000000001f;
	}
	else if ((sStorage.length() >= 13) && (sStorage.length() <= 16)) {
		trailer = "T";
		popStorage = pMPop * 0.000000000001f;
	}
	else {
		popStorage = 0.0;
		trailer = " ";
	}
}