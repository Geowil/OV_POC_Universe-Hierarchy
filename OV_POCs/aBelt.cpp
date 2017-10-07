#include "aBelt.h"
#include "util.h"
#include "consts.h"
#include "dataSystem.h"
#include <iostream>
#include <utility>

namespace u = Util;
namespace setting = Settings;

dataSystem ds_ab;

using std::cout;
using std::endl;
using Settings::gRoidStgSettings;

aBelt::aBelt() {}

aBelt::aBelt(string name, float size, bool full) {
	aBName = name;
	aBSize = size;
	bIsABFull = full;
}

aBelt::aBelt(string name, float size, int ramount, bool full) {
	aBName = name;
	aBSize = size;
	numOfAsteroids = ramount;
	bIsABFull = full;
}

void aBelt::createAsteroids(float secLvl) {
	bIsABFull = false;
	tempSize1 = 0.0f;
	tempSize2 = 0.0f;
	tempSize3 = 0.0f;

	while (!bIsABFull) {
		oreTier = u::getFRand(1.0, 100.0);
		roidSizeCat = u::getFRand(setting::roidSizeRandRng.fLow, setting::roidSizeRandRng.fHigh);
		oreStage = u::getIRand(1, 100);

		//First figure out the sec rating of system
		if (secLvl > setting::secRtHighRng.fLow) {
			//Figure out the tier of the ore to use
			for (setting::oreTierSettings tier : setting::gOreTierSettings) {
				if (oreTier >= tier.getHighRng().fLow && oreTier < tier.getHighRng().fHigh) {
					procAstrSize1(tier);
					break;
				}
			}
		} else if (secLvl > setting::secRtMidRng.fLow && secLvl <= setting::secRtMidRng.fHigh) {
			for (setting::oreTierSettings tier : setting::gOreTierSettings) {
				if (oreTier >= tier.getMidRng().fLow && oreTier < tier.getMidRng().fHigh) {
					procAstrSize1(tier);
					break;
				}
			}

		} else if (secLvl > setting::secRtLowRng.fLow && secLvl <= setting::secRtLowRng.fHigh) {
			for (setting::oreTierSettings tier : setting::gOreTierSettings) {
				if (oreTier >= tier.getLowRng().fLow && oreTier < tier.getLowRng().fHigh) {
					procAstrSize1(tier);
					break;
				}
			}

		} else if (secLvl <= setting::secRtNullRng.fLow) {
			for (setting::oreTierSettings tier : setting::gOreTierSettings) {
				if (oreTier >= tier.getNullRng().fLow && oreTier < tier.getNullRng().fHigh) {
					procAstrSize1(tier);
					break;
				}
			}
		}
		
		/*rand5 = u::getFRand(setting::, 50.0f);

		
		if ((rand5 >= 1.0f) && (rand5 <= 37.5f)) 
		{
			aID = Util::getIRand(0, 2); //Ore ID
			tempSize1 = oreBVal[aID];
			i3 = getOStage(aID);

			//asteroid size calcualtion
			tempSize1 = tempSize1 * Util::getFRand(std::get<0>(roidOSSMulti[i3]), std::get<1>(roidOSSMulti[i3]));
			tempSize2 = (((tempSize1 * 10) / 4) * astSMulti[i3]);
			tempSize3 += tempSize2;

			astName = oreNames[aID];

		} else if ((rand5 > 37.5f) && (rand5 <= 45.0f)){
			aID = Util::getIRand(3, 5);
			tempSize1 = oreBVal[aID];
			i3 = getOStage(aID);

			//asteroid size calcualtion
			tempSize1 = tempSize1 * Util::getFRand(std::get<0>(roidOSSMulti[i3]), std::get<1>(roidOSSMulti[i3]));
			tempSize2 = (((tempSize1 * 10) / 4) * astSMulti[i3]);
			tempSize3 += tempSize2;

			astName = oreNames[aID];		
		} else if ((rand5 > 45.0f) && (rand5 <= 50.0f)) {
			aID = Util::getIRand(6, 8);
			tempSize1 = oreBVal[aID];
			i3 = getOStage(aID);

			//asteroid size calcualtion
			tempSize1 = tempSize1 * Util::getFRand(std::get<0>(roidOSSMulti[i3]), std::get<1>(roidOSSMulti[i3]));
			tempSize2 = (((tempSize1 * 10) / 4) * astSMulti[i3]);
			tempSize3 += tempSize2;

			astName = oreNames[aID];
		}*/

		//TODO: In version 1.0 this function will need to change for positioning to include consideration for asteroid object bounds so asteroids are not stuck inside, fully or partially, other asteroids.
		addAsteroid(tempResVec.at(oreEle).getName(), tempSize2, Util::getFRand(-10.0f, 30.0f), Util::getFRand(-8.0f, 21.0f), Util::getFRand(-13.0f, 32.0f));

		//Check to see if tempSize2 is greater thean aBSize
		if (tempSize3 > aBSize) {
			//If it is then remove last asteroid
			tempSize3 -= tempSize2; //Remove the asteroid's size from the size total
			roids.erase(roids.begin() + roids.size() - 1);
		}
		else if (tempSize3 <= aBSize) {
			if (numOfAsteroids == roids.size()) {
				bIsABFull = true;
			}
			else if (tempSize3 == aBSize) {
				bIsABFull = true;
			}
		}

		//Check to make sure no other asteroid has the same coords
		if (roids.size() > 1) {
			for (i2 = 0; i2 < roids.size(); i2++) {
				for (i3 = 0; i3 < roids.size() - 1; i3++) {
					if ((roids.at(i3).getXPos() == roids.at(i3 + 1).getXPos()) && (roids.at(i3).getYPos() == roids.at(i3 + 1).getYPos()) && (roids.at(i3).getZPos() == roids.at(i3 + 1).getZPos())) { //If asteroid is at same coords then
						tempSize3 -= roids.at(i3 + 1).getSize(); //Remove from total size
						roids.erase(roids.begin() + i3 + 1); //And then from the vector

						bIsABFull = false; //reset to false as it is no longer full
					}
				}
			}
		}
	}
}

void aBelt::addAsteroid(string aName, float aSize, float x, float y, float z) {
	roids.push_back(Asteroid(aName, aSize, x, y, z));

	//Dirty way but easy
	for (i1 = 0; i1 < tempResVec.size(); i1++) {
		roids.at(roids.size() - 1).addOre(tempResVec.at(i1));
		roids.at(roids.size() - 1).updateOAmt(i1, (aSize / tempResVec.at(i1).getSG2()), "set"); //In future, for multi-ore roids need to divide aSize by number of ores before this point
	}	
}

string aBelt::getName() {
	return aBName;
}

float aBelt::getSize() {
	return aBSize;
}

void aBelt::removeAsteroid(int i) {
	roids.erase(roids.begin() + i);
}

bool aBelt::isFull() {
	return bIsABFull;
}

void aBelt::getOre(string tier, string stage) {
	if (!ds_ab.openDB()) {
		cout << "Problem opening database.  Please check error log." << endl;
	} else {
		vector<string> conds = { "Type = 'Ore'", "Teir = '" + tier + "'", "Stage = '" + stage + "'"};
		ds_ab.prepQuery("Resources","select from where",0,conds);

		strRescs = ds_ab.getRescs();

		for (strcResc rsc : strRescs) {
			tempResVec.push_back(Resource(rsc.id, rsc.name, rsc.desc, rsc.typ, rsc.stg, rsc.tier, rsc.bsize, rsc.sg2, 0.0f));
		}
	}
}

void aBelt::procAstrSize1(setting::oreTierSettings tier) {
	//Determine the size category of the asteroid
	if (roidSizeCat >= setting::roidSmallRng.fLow && roidSizeCat <= setting::roidSmallRng.fHigh) {
		//Determine the ore stage to use
		for (setting::roidStageSettings oreStg : setting::gRoidStgSettings) {
			if (oreStage >= oreStg.getRoidSmRng().iLow && oreStage <= oreStg.getRoidSmRng().iHigh) {
				procAstrSize2(tier, oreStg);

				break;
			}
		}
	} else if (roidSizeCat > setting::roidMedRng.fLow && roidSizeCat <= setting::roidMedRng.fHigh) {
		//Determine the ore stage to use
		for (setting::roidStageSettings oreStg : setting::gRoidStgSettings) {
			if (oreStage >= oreStg.getRoidMdRng().iLow && oreStage <= oreStg.getRoidMdRng().iHigh) {
				procAstrSize2(tier, oreStg);
			}

			break;
		}
	} else if (roidSizeCat > setting::roidLargeRng.fLow && roidSizeCat <= setting::roidLargeRng.fHigh) {
		//Determine the ore stage to use
		for (setting::roidStageSettings oreStg : setting::gRoidStgSettings) {
			if (oreStage >= oreStg.getRoidLgRng().iLow && oreStage <= oreStg.getRoidLgRng().iHigh) {
				procAstrSize2(tier, oreStg);
			}

			break;
		}
	}
}

void aBelt::procAstrSize2(setting::oreTierSettings tier, setting::roidStageSettings oreStg) {
	getOre(to_string(tier.getTierVal()), to_string(oreStg.getStageI())); //Populate temp resource vector for further processing

	//Get a random val based on 0 to size of temp ore vect - 1
	oreEle = u::getIRand(0, tempResVec.size() - 1);

	//Now use that ore in this asteroid
	tempSize1 = tempResVec.at(oreEle).getBaseSz();

	//asteroid size calcualtion
	tempSize1 = tempSize1 * Util::getFRand(oreStg.getRoidOStgMulRnd().fLow, oreStg.getRoidOStgMulRnd().fHigh);
	tempSize2 = (((tempSize1 * 10) / 4) * oreStg.getRoidStgMulti());
	tempSize3 += tempSize2;
}