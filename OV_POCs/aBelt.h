#ifndef ABELT_H
#define ABELT_H

#include <string>
#include <vector>
#include "asteroid.h"
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
	aBelt(int id, string name, float size, int ramount, bool full);

	void createAsteroids(float secLvl); //Create asteroids in a belt
	void addAsteroid(string aName, float aSize, float x, float y, float z); //Add an asteroid to the belt
	//void updateAsteroid(Asteroid roid, int pos);
	void removeAsteroid(int i);

	float getSize();
	void procAstrSize1(setting::oreTierSettings tier);
	void procAstrSize2(setting::oreTierSettings tier, setting::roidStageSettings oreStg);
	void getOre(string tier, string stage);

	bool isFull();

	//Asteroid getRoid(int pos);
	//vector<Asteroid> getRoids();

private:
	float aBSize; //Asteroid belt size; see below
	vector<Asteroid> roids;

	bool bIsABFull; //bool: is asteroid belt full?
	vector<Resource> tempResVec; //Temp vector storage for processing
	vector<strcResc> strRescs; //Vector to store the struct representation data

	float oreTier, roidSizeCat, tempSize1, tempSize2, tempSize3;
	int oreStage, oreEle, numOfAsteroids, i1, i2, i3;
};
#endif