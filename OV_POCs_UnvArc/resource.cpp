#include "resource.h"

Resource::Resource() {}

void Resource::setupRes(int id, string name, string desc, string type, string ore, int stg, int tier, float bsize, float sg2) {
	resID = id;
	resName = name;
	resDesc = desc;
	resType = type;
	resOre = ore;
	resStage = stg;
	resTier = tier;
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
string Resource::getDesc() { return resDesc; }
int Resource::getTier() { return resTier; }
