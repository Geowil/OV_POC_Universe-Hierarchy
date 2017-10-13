#include "plSystem.h"
#include "util.h"
#include "consts.h"
#include "settings.h"

namespace u = Util;
namespace setting = Settings;

planetarySystem::planetarySystem() {}
planetarySystem::planetarySystem(string sysName) { oName = sysName; }
planetarySystem::planetarySystem(string sysName, float sec) {
	oName = sysName;
	plsSec = sec;
}

planetarySystem::planetarySystem(int id, string sysName, float sec) {
	oID = id;
	oName = sysName;
	plsSec = sec;
}

float planetarySystem::getSecRating() { return plsSec; }
void planetarySystem::createPlanets() {
	int numOfPlanets = u::getIRand(1, setting::maxPlanets);

	for (int i1 = 0; i1 < numOfPlanets; i1++) {
		string plName;

		plName = oName + " " + rNumerals[i1];
		plsPlanets.push_back(Planet(plName,plsSec));
	}

	generatePlanets();

	for (Planet& plt : plsPlanets) {
		plt.setupPlanetObjects();
	}	
}

void planetarySystem::addPlanet(Planet plt){ plsPlanets.push_back(plt); }
void planetarySystem::modifyPlanet(Planet pl) {
	for (int i1 = 0; i1 < plsPlanets.size(); i1++) {
		if (i1 == plsPlanets.size() - 1 && plsPlanets[i1].getName() != pl.getName()) {
			u::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err010", "Planet " + pl.getName() + " not found in expected system.", "./OV_Log.txt");
		}
		else if (plsPlanets[i1].getName() == pl.getName()) {
			plsPlanets[i1] = pl;
			break; //Found and updated, no longer need to loop
		}
	}
}

vector<Planet> planetarySystem::getPlanets() { return plsPlanets; }
Planet planetarySystem::getPlanet(int index) { return plsPlanets.at(index); }
void planetarySystem::updateSecRating(float sec, string operation) { plsSec = u::updateVal(operation, sec, plsSec); }
void planetarySystem::generatePlanets() {
	//Iterate through each planet in plsSystem plsPlanets vector and set up values for each planet		
	for (Planet& plt : plsPlanets) {
		//Start Planet Info Setup
		//EKS and Size Range Randomization
		pERand2 = u::getFRand(setting::pltEksRand.fLow, setting::pltEksRand.fHigh); //Gets an EKS value from the passed range
		pERand2 = pERand2 * 0.001; //Convert random EKS value to a proper format
		bPPGen2 = false; //Set this to false so that planet will regen until it passes all checks

	    //Randomize population rands
		int popRand1 = u::getFRand(setting::pltPopRand1.fLow, setting::pltPopRand1.fHigh);
		int popRand2 = u::getFRand(setting::pltPopRand2.fLow, setting::pltPopRand2.fHigh);
		int popRand3 = u::getFRand(setting::pltPopRand3.fLow, setting::pltPopRand3.fHigh);

		pSRRand2 = u::getIRand(setting::pltSizeRand.iLow, setting::pltSizeRand.iHigh); //Gets a size value to determine proper size per eks rating from passed range

		//Now, cycle through each planet type setting in settings vector and apply the conditions based on the values in the appropriate instance
		for (setting::pltTypeSettings plTSet : setting::gPltTypSettings) {
			//Check if EKS value falls within the correct range
			if (pERand2 >= plTSet.getPltEksRng().fLow && (pERand2 <= plTSet.getPltEksRng().fHigh || plTSet.getPltEksRng().fHigh == 0)) {
				//As the current eks random falls within the current type setting, set up the planet using this type setting's values
				//Continue while this planet has not been confirmed generated
				while (!bPPGen2) {
					//Get size random for validity checking
					pSRand2 = u::getFRand(plTSet.getPltSzRndRng().fLow, plTSet.getPltSzRndRng().fHigh);

					//Check if the size range random is within the type size range out an outlier
					if (pSRRand2 >= plTSet.getPltSzRng().iLow && pSRRand2 <= plTSet.getPltSzRng().iHigh) {
						//Now check if the planet size falls within the acceptable range for non-outlier planets; if not, reprocess
						if (pSRand2 < plTSet.getPltOutlrRng().fLow || pSRand2 > plTSet.getPltOutlrRng().fHigh) {
							pPStore2 = calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3); //Calculate the population
							pPMax2 = (long long int)pPStore2; //Convert to lli
							bPPGen2 = true; //Planet gen'ed successfully
						}
					} else if (pSRRand2 < plTSet.getPltSzRng().iLow || pSRRand2 > plTSet.getPltSzRng().iHigh) {
						//Now check if the planet size falls within the acceptable range for outlier planets; if not, reprocess
						if (pSRand2 >= plTSet.getPltOutlrRng().fLow && pSRand2 <= plTSet.getPltOutlrRng().fHigh) {
							pPStore2 = calcPop(pERand2, pSRand2, popRand1, popRand2, popRand3); //Calculate the population
							pPMax2 = (long long int)pPStore2; //Convert to lli
							bPPGen2 = true; //Planet gen'ed successfully
						}
					}
				}
			}

			if (bPPGen2) { break; }
		}

		plt.setEKS(pERand2); //Set planet EKS value
		plt.setSize(pSRand2); //Set planet size
		plt.updatePop(pPMax2, "set"); //Set planet population
		plt.updateMPop(pPMax2, "set"); //Set planet max population
		plt.setSLevel(plsSec); //Pass the system sec rating to planet for use later

		numODef = getDefenses(u::getFRand(0.1f, setting::pltDefRand.fHigh), pERand2);
		numOShd = getShields(u::getFRand(0.1f, setting::pltShdRand.fHigh), pERand2);

		//if (numODef > 0) { plt = addDefenses(plt); }
		//if (numOShd > 0) { plt = addShields(plt); }
	}
}

Planet planetarySystem::addDefenses(Planet plt) {
	float eks = plt.getEKS();
	int i2;

	for (i2 = 0; i2 < numODef; i2++) {
		plt.addPDefenses(true, u::getIRand(0, 7), false, 0, false);
	}

	return plt;
}

Planet planetarySystem::addShields(Planet plt) {
	float eks = plt.getEKS();
	int i2;

	for (i2 = 0; i2 < numODef; i2++) {
		plt.addPDefenses(false, 0, true, u::getIRand(0, 7), false);
	}

	return plt;
}

int planetarySystem::getDefenses(float rand, float eks) {
	for (setting::pltTypeSettings plTSet : setting::gPltTypSettings) {
		if (eks >= plTSet.getPltEksRng().fLow && (eks <= plTSet.getPltEksRng().fHigh || plTSet.getPltEksRng().fHigh == 0)) {
			for (i1 = 0; i1 < plTSet.getPltDefRngSz() - 1; i1++) {
				if (i1 == 0 && (rand >= 0.1f && rand <= plTSet.getPltDefRng(i1))) {
					return i1; //Use iterator for num of defs
				}
				else if (i1 != 0 && (rand > plTSet.getPltDefRng(i1 - 1) && rand <= plTSet.getPltDefRng(i1))) {
					return i1;
				}
			}
		}
	}
	/*
	if ((eks > 0.0f) && (eks < 1.0f)) { //Type 0 Planet
		if ((rand >= 1) && (rand <= 35)) { nOfDef = 0; } //36% chance for 0 defenses		
		else if ((rand >= 36) && (rand <= 60)) { nOfDef = 1; } //25% chance for 1 defense
		else if ((rand >= 61) && (rand <= 78)) { nOfDef = 2; } //18% chance for 2 defenses
		else if ((rand >= 79) && (rand <= 87)) { nOfDef = 3; } //7% chance for 3 defenses
		else if ((rand >= 88) && (rand <= 94)) { nOfDef = 4; } //7% chance for 4 defenses
		else if ((rand >= 95) && (rand <= 98)) { nOfDef = 5; } //4% chance for 5 defenses
		else if (rand >= 99) { nOfDef = 6; } //2% Chance for 6 defenses
	}
	else if ((eks >= 1.0f) && (eks < 2.0f)) { //Type 1 Planet
		if ((rand >= 1) && (rand <= 28)) { nOfDef = 0; } //29% chance for 0 defenses		
		else if ((rand >= 29) && (rand <= 55)) { nOfDef = 1; } //28% chance for 1 defense
		else if ((rand >= 56) && (rand <= 71)) { nOfDef = 2; } //16% chance for 2 defenses
		else if ((rand >= 72) && (rand <= 82)) { nOfDef = 3; } //11% chance for 3 defenses
		else if ((rand >= 83) && (rand <= 90)) { nOfDef = 4; } //8% chance for 4 defenses
		else if ((rand >= 91) && (rand <= 96)) { nOfDef = 5; } //7% chance for 5 defenses
		else if (rand >= 97) { nOfDef = 6; } //4% Chance for 6 defenses
	}
	else if ((eks >= 2.0f) && (eks < 3.0f)) { //Type 2 Planet
		if ((rand >= 1) && (rand <= 28)) { nOfDef = 0; } //29% chance for 0 defenses		
		else if ((rand >= 29) && (rand <= 56)) { nOfDef = 1; } //28% chance for 1 defense
		else if ((rand >= 57) && (rand <= 70)) { nOfDef = 2; } //14% chance for 2 defenses
		else if ((rand >= 71) && (rand <= 82)) { nOfDef = 3; } //12% chance for 3 defenses
		else if ((rand >= 83) && (rand <= 91)) { nOfDef = 4; } //9% chance for 4 defenses
		else if ((rand >= 92) && (rand <= 96)) { nOfDef = 5; } //5% chance for 5 defenses
		else if (rand >= 97) { nOfDef = 6; } //4% Chance for 6 defenses
	}
	else if ((eks >= 3.0f) && (eks < 4.0f)) { //Type 3 Planet
		if ((rand >= 1) && (rand <= 20)) { nOfDef = 0; } //21% chance for 0 defenses		
		else if ((rand >= 21) && (rand <= 46)) { nOfDef = 1; } //26% chance for 1 defense
		else if ((rand >= 47) && (rand <= 68)) { nOfDef = 2; } //19% chance for 2 defenses
		else if ((rand >= 69) && (rand <= 80)) { nOfDef = 3; } //13% chance for 3 defenses
		else if ((rand >= 81) && (rand <= 89)) { nOfDef = 4; } //9% chance for 4 defenses
		else if ((rand >= 90) && (rand <= 95)) { nOfDef = 5; } //6% chance for 5 defenses
		else if (rand >= 96) { nOfDef = 6; } //3% Chance for 6 defenses
	}
	else if ((eks >= 4.0f) && (eks < 5.0f)) { //Type 4 Planet
		if (rand >= 1 && rand <= 18) { nOfDef = 0; } //19% chance for 0 defenses		
		else if (rand >= 19 && rand <= 35) { nOfDef = 1; } //15% chance for 1 defense
		else if (rand >= 36 && rand <= 55) { nOfDef = 2; } //20% chance for 2 defenses
		else if (rand >= 56 && rand <= 68) { nOfDef = 3; } //13% chance for 3 defenses
		else if (rand >= 69 && rand <= 80) { nOfDef = 4; } //12% chance for 4 defenses
		else if (rand >= 81 && rand <= 89) { nOfDef = 5; } //9% chance for 5 defenses
		else if (rand >= 90 && rand <= 95) { nOfDef = 6; } //6% Chance for 6 defenses
		else if (rand >= 96) { nOfDef = 7; } //5% chance for 7 defenses
	}
	else if (eks >= 5.0f) { //Type 5 Planet
		if (rand >= 1 && rand <= 12) { nOfDef = 0; } //13% chance for 0 defenses		
		else if (rand >= 13 && rand <= 28) { nOfDef = 1; } //16% chance for 1 defense
		else if (rand >= 29 && rand <= 48) { nOfDef = 2; } //20% chance for 2 defenses
		else if (rand >= 49 && rand <= 62) { nOfDef = 3; } //14% chance for 3 defenses
		else if (rand >= 63 && rand <= 74) { nOfDef = 4; } //12% chance for 4 defenses
		else if (rand >= 75 && rand <= 85) { nOfDef = 5; } //11% chance for 5 defenses
		else if (rand >= 86 && rand <= 92) { nOfDef = 6; } //9% Chance for 6 defenses
		else if (rand >= 93 && rand <= 97) { nOfDef = 7; } //5% Chance for 7 defenses
		else if (rand >= 98) { nOfDef = 8; } //3% chance for 8 defenses
	}

	return nOfDef;*/
}

int planetarySystem::getShields(float rand, float eks) {
	for (setting::pltTypeSettings plTSet : setting::gPltTypSettings) {
		if (eks >= plTSet.getPltEksRng().fLow && (eks <= plTSet.getPltEksRng().fHigh || plTSet.getPltEksRng().fHigh == 0)) {
			for (i1 = 0; i1 < plTSet.getPltShdRngSz() - 1; i1++) {
				if (i1 == 0 && (rand >= 0.1f && rand <= plTSet.getPltShdRng(i1))) {
					return i1; //Use iterator for num of defs
				}
				else if (i1 != 0 && (rand > plTSet.getPltShdRng(i1 - 1) && rand <= plTSet.getPltShdRng(i1))) {
					return i1;
				}
			}
		}
	}

	/*if ((eks > 0.0f) && (eks < 1.0f)) { //Type 0 Planet
		if ((rand >= 1) && (rand <= 60)) { nOfShd = 0; } //61% chance for 0 shields
		else if ((rand >= 61) && (rand <= 86)) { nOfShd = 1; } //26% chance for 1 shields
		else if (rand >= 86) { nOfShd = 2; } //17% chance for 2 shields
	}
	else if ((eks >= 1.0f) && (eks < 2.0f)) { //Type 1 Planet
		if ((rand >= 1) && (rand <= 52)) { nOfShd = 0; } //53% chance for 0 shields
		else if ((rand >= 53) && (rand <= 84)) { nOfShd = 1; } //22% chance for 1 shields
		else if (rand >= 85) { nOfShd = 2; } //15% chance for 2 shields
	}
	else if ((eks >= 2.0f) && (eks < 3.0f)) { //Type 2 Planet
		if ((rand >= 1) && (rand <= 35)) { nOfShd = 0; } //36% chance for 0 shields
		else if ((rand >= 36) && (rand <= 68)) { nOfShd = 1; } //33% chance for 1 shields
		else if ((rand >= 68) && (rand <= 87)) { nOfShd = 2; } //18% chance for 2 shields
		else if (rand >= 88) { nOfShd = 3; } //13% chance for 3 shields
	}
	else if ((eks >= 3.0f) && (eks < 4.0f)) { //Type 3 Planet
		if ((rand >= 1) && (rand <= 27)) { nOfShd = 0; } //28% chance for 0 shields
		else if ((rand >= 28) && (rand <= 64)) { nOfShd = 1; } //27% chance for 1 shields
		else if ((rand >= 65) && (rand <= 84)) { nOfShd = 2; } //21% chance for 2 shields
		else if (rand >= 85) { nOfShd = 3; } //16% chance for 3 shields
	}
	else if ((eks >= 4.0f) && (eks < 5.0f)) { //Type 4 Planet
		if ((rand >= 1) && (rand <= 20)) { nOfShd = 0; } //21% chance for 0 shields
		else if ((rand >= 21) && (rand <= 48)) { nOfShd = 1; } //28% chance for 1 shields
		else if ((rand >= 49) && (rand <= 74)) { nOfShd = 2; } //26% chance for 2 shields
		else if ((rand >= 75) && (rand <= 88)) { nOfShd = 3; } //14% chance for 3 shields
		else if (rand >= 89) { nOfShd = 4; } //12% chance for 4 shields
	}
	else if (eks >= 5.0f) { //Type 5 Planet
		if ((rand >= 1) && (rand <= 18)) { nOfShd = 0; } //19% chance for 0 shields
		else if ((rand >= 19) && (rand <= 36)) { nOfShd = 1; } //18% chance for 1 shields
		else if ((rand >= 37) && (rand <= 65)) { nOfShd = 2; } //29% chance for 2 shields
		else if ((rand >= 66) && (rand <= 84)) { nOfShd = 3; } //19% chance for 3 shields
		else if (rand >= 85) { nOfShd = 4; } //16% chance for 4 shields
	}

	return nOfShd;*/
}

float planetarySystem::calcPop(float pERand, float pSRand, float popRand1, float popRand2, float popRand3) {
	float rPop = ((((((8000.0f * popRand1) * popRand2) * pERand) * pSRand) * popRand3) / 6.0f);

	//if rPop is negative, flip the sign
	if (rPop < 0) { rPop = rPop * -1; }

	return rPop;
}