#include "aBelt.h"
#include "util.h"
#include "consts.h"
#include "settings.h"
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

	asteroid_id = 0; //Reset aid

	getOre(); //Populate temp resource vector for further processing
	processOre(); //Process ore stages into oreStages vector

	while (!bIsABFull) {
		/*
		non-testing ranges:
		small: 75% of random max 1-37.5
		medium: 15% of random max 37.6-45.0
		large: 5% of random max 45.1-50.0
		*/

		/* How ores are created:
			This is a very complicated process, at least on paper.  There are many variables to consider here.

			First, and foremost, is system sec rating.  While this makes no sense logically, yet (there is a way to describe this situation that is), it makes sense in terms of game progression.
			As you expand out into systems which have not been around quite as long, more valuable ores can still be found.\

			This should be the main determination on which teir ores are being placed into asteroids.

			The next variable is asteroid size.  Larger asteroids should be more likely to be lower stage ores.  For example, there should not be many large Methyx Major asteroids.  Higher stages should be more prevelent in small asteroids and somewhat less prevelent
			in medium sized asteroids.

			How this would look in terms of code might be like this (pseudocode):
			
			if sec rating is in a certain range
				load up a vector or list or something of up to a specific teir of ores
				if asteroid size is small
					given a random range
						select a specific teir of ores
						given a random range
							if the rand is within a certain range
								select a stage 3 ore
							if the rand is within a different range
								select a stage 2 ore

						and so on...


			This might be the starting structure of the code to do this.  It would be very complex at first but could probably be refactored over time		
		*/

		oreTier = u::getFRand(1.0, 100.0);

		//First figure out the sec rating of system
		if (secLvl > setting::secRtHighRng.fLow) {
			/*High Sec Tier Probabilities
				Tier 1: 80%
				Tier 2: 15%
				Tier 3: 2.5%
				Tier 4: 2.5%
			*/

			//Figure out the tier of the ore to use
			for (setting::oreTierSettings tier : setting::gOreTierSettings) {
				if (oreTier >= tier.getHighRng().fLow && oreTier < tier.getHighRng().fHigh) {
					//Figure out 
				}
			}
		}
	
		else if (secLvl > setting::secRtMidRng.fLow && secLvl <= setting::secRtMidRng.fHigh) {
			/*Mid Sec Tier Probabilities
				Tier 1: 75%
				Tier 2: 18%
				Tier 3: 4.2%
				Tier 4: 2.8%
			*/

				for (setting::oreTierSettings tier : setting::gOreTierSettings) {
					if (oreTier >= tier.getMidRng().fLow && oreTier < tier.getMidRng().fHigh) {

					}
				}

		}
		else if (secLvl > setting::secRtLowRng.fLow && secLvl <= setting::secRtLowRng.fHigh) {
			/*Low Sec Tier Probabilities
			Tier 1: 40%
			Tier 2: 32%
			Tier 3: 16%
			Tier 4: 12%
			*/

		}
		else if (secLvl <= setting::secRtNullRng.fLow) {
			/*High Sec Tier Probabilities
			Tier 1: 25%
			Tier 2: 30%
			Tier 3: 24%
			Tier 4: 21%
			*/

		}
		rand5 = u::getFRand(setting::, 50.0f);

		
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
		}


		//TODO: In version 1.0 this function will need to change for positioning to include consideration for asteroid object bounds so asteroids are not stuck inside, fully or partially, other asteroids.
		addAsteroid(asteroid_id, astName, astName, aID, astName, tempSize2, (tempSize2 / oreSG2[aID]), Util::getFRand(-10.0f, 30.0f), Util::getFRand(-8.0f, 21.0f), Util::getFRand(-13.0f, 32.0f));
		asteroid_id += 1;

		//Check to see if tempSize2 is greater thean aBSize
		if (tempSize3 > aBSize) {
			//If it is then remove last asteroid
			tempSize3 -= tempSize2; //Remove the asteroid's size from the size total
			roids.erase(roids.begin() + roids.size() - 1);
			asteroid_id -= 1; //iterate aid back 1
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
						asteroid_id -= 1;

						bIsABFull = false; //reset to false as it is no longer full
					}
				}
			}
		}
	}
}

void aBelt::addAsteroid(int aid, string aName, string aOName, int aOID, string aDesc, float aSize, float aOAmount, float x, float y, float z) {
	roids.push_back(Asteroid(aid, aName, aOName, aOID, aDesc, aSize, aOAmount, x, y, z));
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

void aBelt::getOre() {
	if (!ds_ab.openDB()) {
		cout << "Problem opening database.  Please check error log." << endl;
	} else {
		vector<string> conds = { "Type = 'Ore'" };
		ds_ab.prepQuery("Resources","select from where",0,conds);

		strRescs = ds_ab.getRescs();

		for (strcResc rsc : strRescs) {
			Resource newRes;

			newRes.setupRes(rsc.id, rsc.name, rsc.desc, rsc.typ, rsc.ore, rsc.stg, rsc.bsize, rsc.sg2);
			tempResVec.push_back(newRes);
		}
	}
}

void aBelt::processOre() {
	//Setup the vector of vectors based on the number of stages in settings
	if (oreStages.size() < 1) {
		for (i1 = 0; i1 < setting::oreStages.size(); i1++) {
			vector<Resource> newResVec;

			oreStages.push_back(newResVec);
		}
	}

	//Use gRoidStgSettings to find and then place all of the loaded ores
	for (i1 = 0; i1 < gRoidStgSettings.size(); i1++) {
		for (Resource rsc : tempResVec) {
			if (rsc.getStage() == gRoidStgSettings.at(i1).getStageI()) {
				Resource newRes;

				newRes.setupRes(rsc.getID(), rsc.getName(), rsc.getDesc(), rsc.getType(), rsc.getOre(), rsc.getStage(), rsc.getBaseSz(), rsc.getSG2());
				
				oreStages.at(i1).push_back(newRes);
			}
		}
	}
}