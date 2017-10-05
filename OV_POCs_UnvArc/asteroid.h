#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>
#include <vector>
#include "object.h"
#include "resource.h"

using std::string;
using std::vector;

class dataSystem;

class Asteroid : public Object {
public:
	Asteroid();
	Asteroid(int aid, float size, float oamount, float x, float y, float z); //Constructor to add astroid to vector

	void updateOAmount(float amount, string operation);

	string getName(int pos);
	string getDesc(int pos);
	string getOName(int pos);
	int getAID();

	float getSize();
	float getOAmount();

	int getOID(int pos);
	void addOre(Resource ore);

private:
	int aID; //Asteroid ID
	string aDesc; //Asteroid description

	float aSize; //Asteroid size
	float aOAmount; //Asteroid ore amount

	vector<Resource>aOre; //Ore(s) contained in this asteroid

};
#endif

/*
Asteroid Belt Size

Each belt will have a limited amount of space.  Each asteroid added to a specific belt will take up some of that space until the space is completely used up.  A random will determine the number of asteroids
and this number will be multipiled by a random range times 13 divided by 6.

*/