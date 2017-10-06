#include "asteroid.h"


Asteroid::Asteroid() {

}

Asteroid::Asteroid(int aid, float size, float oamount, float x, float y, float z) {
	aID = aid;	
	aSize = size;
	aOAmount = oamount;
	xPos = x;
	yPos = y;
	zPos = z;
}

void Asteroid::updateOAmount(float amount, string operation) {
	if (operation == "add") {
		aOAmount += amount;
	}

	else if (operation == "sub") {
		aOAmount -= amount;
	}

	else if (operation == "set") {
		aOAmount = amount;
	}
}


string Asteroid::getName(int pos) {
	return aOre.at(pos).getName();
}

string Asteroid::getDesc(int pos) {
	return aOre.at(pos).getDesc();
}

string Asteroid::getOName(int pos) {
	return aOre.at(pos).getOre;
}

float  Asteroid::getSize() {
	return aSize;
}

float  Asteroid::getOAmount() {
	return aOAmount;
}

int Asteroid::getOID(int pos) {
	return aOre.at(pos).getID();
}

int Asteroid::getAID() {
	return aID;
}