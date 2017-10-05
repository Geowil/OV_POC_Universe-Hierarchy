#include "aBelt.h"
#include "util.h"
#include "consts.h"
#include "settings.h"
#include <utility>

namespace u = Util;
namespace setting = Settings;


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

void aBelt::createAsteroids() {
	bIsABFull = false;
	tempSize1 = 0.0f;
	tempSize2 = 0.0f;
	tempSize3 = 0.0f;

	asteroid_id = 0; //Reset aid

	while (!bIsABFull) {
		/*
		non-testing ranges:
		small: 75% of random max 1-37.5
		medium: 15% of random max 37.6-45.0
		large: 5% of random max 45.1-50.0
		*/
		
		rand5 = u::getFRand(1.0f, 50.0f);

		
		if ((rand5 >= 1.0f) && (rand5 <= 37.5f)) //Until a match is found here (TODO: handle exception if no match is found)
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

int aBelt::getOre(int id) {
	
}