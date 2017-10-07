#include "asteroid.h"


Asteroid::Asteroid() {

}

Asteroid::Asteroid(string name, float size, float x, float y, float z) {
	aSize = size;
	aName = name;
	xPos = x;
	yPos = y;
	zPos = z;
}

Asteroid::Asteroid(int aid, string name, float size, float x, float y, float z) {
	aID = aid;	
	aSize = size;
	aName = name;
	xPos = x;
	yPos = y;
	zPos = z;
}

string Asteroid::getName() {
	return aName;
}

void Asteroid::updateOAmt(int pos, float val, string operation) {
	aOre.at(pos).updateOAmt(operation, val);
}

string Asteroid::getODesc(int pos) {
	return aOre.at(pos).getDesc();
}

float  Asteroid::getSize() {
	return aSize;
}

float  Asteroid::getOAmount(int pos) {
	return aOre.at(pos).getOAmt();
}

int Asteroid::getOID(int pos) {
	return aOre.at(pos).getID();
}

int Asteroid::getAID() {
	return aID;
}

void Asteroid::addOre(Resource ore) { aOre.push_back(Resource(ore.getID(), ore.getName(), ore.getDesc(), ore.getType(), ore.getStage(), ore.getTier(), ore.getBaseSz(), ore.getSG2(), 0.0f)); }