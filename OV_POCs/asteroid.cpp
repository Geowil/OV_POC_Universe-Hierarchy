#include "asteroid.h"

Asteroid::Asteroid() {}
Asteroid::Asteroid(string name, float size, float x, float y, float z) {
	aSize = size;
	oName = name;
	xPos = x;
	yPos = y;
	zPos = z;
}

Asteroid::Asteroid(int aid, string name, float size, float x, float y, float z) {
	oID = aid;	
	aSize = size;
	oName = name;
	xPos = x;
	yPos = y;
	zPos = z;
}

void Asteroid::updateRoid(Asteroid roid) {
	aSize = roid.getSize();
	oName = roid.getName();
	xPos = roid.getXPos();
	yPos = roid.getYPos();
	zPos = roid.getZPos();
}

void Asteroid::updateOAmt(int pos, float val, string operation) { aOre.at(pos).updateOAmt(operation, val); }
string Asteroid::getODesc(int pos) { return aOre.at(pos).getDesc(); }
float  Asteroid::getSize() { return aSize; }
float  Asteroid::getOAmount(int pos) { return aOre.at(pos).getOAmt(); }
int Asteroid::getOID(int pos) { return aOre.at(pos).getID(); }
void Asteroid::addOre(int id, string name, string desc, string typ, int stage, int tier, float basesz, float sg2, float amt) {
	aOre.push_back(Resource(id,name,desc,typ,stage,tier,basesz,sg2,amt)); 
}

int Asteroid::getaOreSz() { return aOre.size(); }