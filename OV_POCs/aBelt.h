#ifndef ABELT_H
#define ABELT_H

#include <string>
#include <vector>
#include "range.h"
#include "asteroid.h"
#include "random.cpp"
#include "object.h"
#include "resource.h"
#include "dataStructs.h"
#include "settings.h"

using std::string;
using std::vector;

namespace setting = Settings;

class aBelt : public Object{
public:

	aBelt();
	aBelt(string name, float size, bool full);
	aBelt(string name, float size, int ramount, bool full);

	void createAsteroids(float secLvl); //Create asteroids in a belt
	void addAsteroid(string aName, float aSize, float x, float y, float z); //Add an asteroid to the belt
	void removeAsteroid(int i);

	string getName();
	float getSize();
	void procAstrSize1(setting::oreTierSettings tier);
	void procAstrSize2(setting::oreTierSettings tier, setting::roidStageSettings oreStg);
	void getOre(string tier, string stage);

	bool isFull();

	vector<Asteroid> roids;

private:

	bool bIsABFull; //bool: is asteroid belt full?
	float aBSize; //Asteroid belt size; see below
	string aBName; //Astroid belt name
	string astName;

	vector<Resource> tempResVec; //Temp vector storage for processing
	vector<strcResc> strRescs; //Vector to store the struct representation data

	float oreTier,roidSizeCat;
	int oreStage,oreEle;

	float rand1, rand2, rand5, tempSize1, tempSize2, tempSize3;
	int rand3, rand4, numOfAsteroids, aID, randx, randy, randz, aBVal;

	int i1, i2, i3;
};
#endif