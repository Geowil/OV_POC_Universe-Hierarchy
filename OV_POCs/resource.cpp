#include "resource.h"
#include "util.h"

namespace u = Util;

Resource::Resource() {}
Resource::Resource(int id, string name, string desc, string type, int stg, int tier, float bsize, float sg2, float amt) {
	resID = id;
	resName = name;
	resDesc = desc;
	resType = type;
	resStage = stg;
	resTier = tier;
	resBaseSize = bsize;
	resSG2 = sg2;
	resOAmt = amt;
}

void Resource::updateOAmt(string operation, float val) { resOAmt = u::updateVal(operation, val, resOAmt); }
int Resource::getID() { return resID; }
string Resource::getName() { return resName; }
string Resource::getType() { return resType; }
int Resource::getStage() { return resStage; }
float Resource::getBaseSz() { return resBaseSize; }
float Resource::getSG2() { return resSG2; }
string Resource::getDesc() { return resDesc; }
int Resource::getTier() { return resTier; }
float Resource::getOAmt() { return resOAmt; }
