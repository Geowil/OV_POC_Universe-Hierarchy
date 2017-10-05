#ifndef ABELT_H
#define ABELT_H

#include <string>
#include <vector>
#include "range.h"
#include "asteroid.h"
#include "random.cpp"
#include "object.h"
#include 
using std::string;
using std::vector;

class aBelt : public Object{
public:

	aBelt();
	aBelt(string name, float size, bool full);
	aBelt(string name, float size, int ramount, bool full);

	void createAsteroids(); //Create asteroids in a belt
	void addAsteroid(int aid, string aName, string aOName, int aID, string aDesc, float aSize, float aOAmount, float x, float y, float z); //Add an asteroid to the belt
	void removeAsteroid(int i);

	string getName();
	float getSize();
	int getOre(int id);

	bool isFull();

	vector<Asteroid> roids;

private:

	bool bIsABFull; //bool: is asteroid belt full?
	float aBSize; //Asteroid belt size; see below
	string aBName; //Astroid belt name
	string astName;

	Range oreIDs;

	float rand1, rand2, rand5, tempSize1, tempSize2, tempSize3;
	int rand3, rand4, numOfAsteroids, aID, randx, randy, randz, aBVal;

	int i1, i2, i3, asteroid_id;
};
#endif