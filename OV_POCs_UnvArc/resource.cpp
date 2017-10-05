#include "resource.h"

Resource::Resource() {}

void Resource::setupRes(int id, string name, string type, string ore, int stg, float bsize, float sg2) {
	resID = id;
	resName = name;
	resType = type;
	resOre = ore;
	resStage = stg;
	resBaseSize = bsize;
	resSG2 = sg2;
}

int Resource::getID() { return resID; }
string Resource::getName() { return resName; }
string Resource::getType() { return resType; }
string Resource::getOre() { return resOre; }
int Resource::getStage() { return resStage; }
float Resource::getBaseSz() { return resBaseSize; }
float Resource::getSG2() { return resSG2; }
