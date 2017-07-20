#include "plSystem.h"
#include "util.h"
#include "consts.h"


planetarySystem::planetarySystem() {}

planetarySystem::planetarySystem(string sysName, float sec) {
	plsName = sysName;
	plsSec = sec;
}

void planetarySystem::setSysName(string name) {
	plsName = name;
}

float planetarySystem::getSecRating() {
	return plsSec;
}

string planetarySystem::getSysName() {
	return plsName;
}

void planetarySystem::createPlanets() {
	int numOfPlanets = Util::getIRand(1, 4);

	for (int i1 = 0; i1 < numOfPlanets; i1++) {
		Planet newPL;

		newPL.setName(getSysName() + " " + rNumerals[i1]);
		addPlanet(newPL);
	}

	generatePlanets();

	for each (Planet plt in plsPlanets) {
		plt.setupPlanetObjects();
	}	
}

void planetarySystem::addPlanet(Planet pl) {
	plsPlanets.push_back(pl);
}

void planetarySystem::modifyPlanet(Planet pl) {
	for (int i1 = 0; i1 < plsPlanets.size(); i1++) {
		if (i1 == plsPlanets.size() - 1 && plsPlanets[i1].getName() != pl.getName()) {
			Util::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Planet " + pl.getName() + " not found in expected system.", "./OV_Log.txt");
		}
		else if (plsPlanets[i1].getName() == pl.getName()) {
			plsPlanets[i1] = pl;
			break; //Found and updated, no longer need to loop
		}
	}
}

vector<Planet> planetarySystem::getPlanets() {
	return plsPlanets;
}

Planet planetarySystem::getPlanet(int index) {
	return plsPlanets.at(index);
}

void planetarySystem::updateSecRating(float sec, string operation) {
	if (operation == "add") {
		plsSec += sec;
	}
	else if (operation == "sub") {
		plsSec -= sec;
	}
	else if (operation == "set") {
		plsSec = sec;
	}
}

string planetarySystem::getName() {
	return plsName;
}

void planetarySystem::generatePlanets() {
	for each (Planet plt in plsPlanets) { //Iterate through each planet in plsSystem plsPlanets vector and set up values for each planet		
									//Start Planet Info Setup
									//EKS and Size Range Randomization
		pERand2 = Util::getFRand(1.0f, 5500.0f); //External value tag: float range
		pSRRand2 = Util::getIRand(1, 1000); //External value tag: int range
		pERand2 = pERand2 * 0.001; //Convert random EKS value to a proper format
		bPPGen2 = false; //So while loops will run

	    //Randomize population rands
		int popRand1 = Util::getIRand(1, 60);
		int popRand2 = Util::getIRand(1, 100);
		int popRand3 = Util::getIRand(1, 260);

						 //Type 0
		if ((pERand2 >= 0.0f) && (pERand2 <= 0.9f)) { //External value tag: int range
			while (!bPPGen2) { //While planet pop has not been generated
				pSRand2 = Util::getFRand(1.0f, 2.5f); //Randomize the planet size and then get to checking

				if ((pSRRand2 >= 450) && (pSRRand2 <= 625)) { //If planet size range is within the range of 450 and 625 continue
					if (pSRand2 < 1.2f || pSRand2 > 1.8f) { //If planet size is outside of the range of 1.2 to 1.8 continue otherwise reroll the size rand on next loop
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3); //Calculate the population and return to pPStore2
						pPMax2 = (long long int)pPStore2; //Convert pPStore2 to a lli and save to pPMax2
						bPPGen2 = true; //Pop has been generated so set to true
					}
				}
				else if (pSRRand2 < 450 || pSRRand2 > 625) { //If planet size range is outside of the range of 450 to 625 continue
					if ((pSRand2 >= 1.2f) && (pSRand2 <= 1.8f)) { //If planet size is within the range of 1.2 and 1.8 continue otherwise reroll the size rand on next loop
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
			}
		}

		//Type 1
		else if ((pERand2 >= 1.0f) && (pERand2 <= 1.9f)) { //External value tag: int range
			while (!bPPGen2) {
				pSRand2 = Util::getFRand(1.9f, 3.0f);

				if ((pSRRand2 >= 450) && (pSRRand2 <= 625)) {
					if (pSRand2 < 2.0f || pSRand2 > 2.3f) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
				else if (pSRRand2 < 450 || pSRRand2 > 625) {
					if ((pSRand2 >= 2.0f) && (pSRand2 <= 2.3f)) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
			}
		}

		//Type 2
		else if ((pERand2 >= 2.0f) && (pERand2 <= 2.9f)) { //External value tag: int range
			while (!bPPGen2) {
				pSRand2 = Util::getFRand(2.4f, 5.3f);

				if ((pSRRand2 >= 450) && (pSRRand2 <= 625)) {
					if (pSRand2 < 2.8f || pSRand2 > 4.1f) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
				else if (pSRRand2 < 450 || pSRRand2 > 625) {
					if ((pSRand2 >= 2.8f) && (pSRand2 <= 4.1f)) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
			}
		}

		//Type 3
		else if ((pERand2 >= 3.0f) && (pERand2 <= 3.9f)) { //External value tag: int range
			while (!bPPGen2) {
				pSRand2 = Util::getFRand(4.2f, 7.7f);

				if ((pSRRand2 >= 450) && (pSRRand2 <= 625)) {
					if (pSRand2 < 4.8f || pSRand2 > 6.9f) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
				else if (pSRRand2 < 450 || pSRRand2 > 625) {
					if ((pSRand2 >= 4.8f) && (pSRand2 <= 6.9f)) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
			}
		}

		//Type 4
		else if ((pERand2 >= 4.0f) && (pERand2 <= 4.9f)) { //External value tag: int range
			while (!bPPGen2) {
				pSRand2 = Util::getFRand(7.0f, 8.4f);

				if ((pSRRand2 >= 450) && (pSRRand2 <= 625)) {
					if (pSRand2 < 7.5f || pSRand2 > 7.9f) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
				else if (pSRRand2 < 450 || pSRRand2 > 625) {
					if ((pSRand2 >= 7.5f) && (pSRand2 <= 7.9f)) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
			}
		}

		//Type 5
		else if (pERand2 > 4.9f) { //External value tag: int range
			while (!bPPGen2) {
				pSRand2 = Util::getFRand(8.0f, 10.0f);

				if ((pSRRand2 >= 450) && (pSRRand2 <= 625)) {
					if (pSRand2 < 8.8f || pSRand2 > 9.7f) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
				else if (pSRRand2 < 450 || pSRRand2 > 625) {
					if ((pSRand2 >= 8.8f) && (pSRand2 <= 9.7f)) {
						pPStore2 = Util::calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3);
						pPMax2 = (long long int)pPStore2;
						bPPGen2 = true;
					}
				}
			}
		}

		plt.setEKS(pERand2); //Set planet EKS value
		plt.setSize(pSRand2); //Set planet size
		plt.updatePop(pPMax2, "set"); //Set planet population
		plt.updateMPop(pPMax2, "set"); //Set planet max population

		numODef = Util::getDefenses(Util::getIRand(1, 100), pERand2);
		numOShd = Util::getShields(Util::getIRand(1, 100), pERand2);

		if (numODef > 0) {
			plt = addDefenses(plt);
		}

		if (numOShd > 0) {
			plt = addShields(plt);
		}
	}
}

Planet planetarySystem::addDefenses(Planet plt) {
	float eks = plt.getEKS();
	int i2;

	for (i2 = 0; i2 < numODef; i2++) {
		plt.addPDefenses(true, Util::getIRand(0, 7), false, 0, false);
	}

	return plt;
}

Planet planetarySystem::addShields(Planet plt) {
	float eks = plt.getEKS();
	int i2;

	for (i2 = 0; i2 < numODef; i2++) {
		plt.addPDefenses(false, 0, true, Util::getIRand(0, 7), false);
	}

	return plt;
}