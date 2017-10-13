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
	Asteroid(string name, float size, float x, float y, float z); //Constructor to add astroid to vector
	Asteroid(int id, string name, float size, float x, float y, float z); //Constructor to add astroid to vector

	void updateRoid(Asteroid roid);
	
	string getODesc(int pos);
	void updateOAmt(int pos, float val, string operation);

	float getSize();
	float getOAmount(int pos);

	int getOID(int pos);
	void addOre(int id, string name, string desc, string typ, int stage, int tier, float basesz, float sg2, float amt);
	int getaOreSz();

private:
	float aSize; //Asteroid size
	vector<Resource>aOre; //Ore(s) contained in this asteroid
};
#endif

/*
Asteroid Belt Size

Each belt will have a limited amount of space.  Each asteroid added to a specific belt will take up some of that space until the space is completely used up.  A random will determine the number of asteroids
and this number will be multipiled by a random range times 13 divided by 6.

*/