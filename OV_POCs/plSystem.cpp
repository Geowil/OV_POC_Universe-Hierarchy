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
	oSecLvl = sec;
}

planetarySystem::planetarySystem(int id, string sysName, float sec) {
	oID = id;
	oName = sysName;
	oSecLvl = sec;
}

void planetarySystem::createPlanets() {
	int numOfPlanets = u::getIRand(1, setting::maxPlanets);

	for (int i1 = 0; i1 < numOfPlanets; i1++) {
		string plName;

		plName = oName + " " + rNumerals[i1];
		plsPlanets.push_back(Planet(plName, oSecLvl));
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
			if (pERand2 >= plTSet.getPltEksRng().fLow && pERand2 <= plTSet.getPltEksRng().fHigh) {
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
		if (eks >= plTSet.getPltEksRng().fLow && eks <= plTSet.getPltEksRng().fHigh) {
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
}

int planetarySystem::getShields(float rand, float eks) {
	for (setting::pltTypeSettings plTSet : setting::gPltTypSettings) {
		if (eks >= plTSet.getPltEksRng().fLow && eks <= plTSet.getPltEksRng().fHigh) {
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
}

float planetarySystem::calcPop(float pERand, float pSRand, float popRand1, float popRand2, float popRand3) {
	float rPop = ((((((8000.0f * popRand1) * popRand2) * pERand) * pSRand) * popRand3) / 6.0f);

	//if rPop is negative, flip the sign
	if (rPop < 0) { rPop = rPop * -1; }

	return rPop;
}