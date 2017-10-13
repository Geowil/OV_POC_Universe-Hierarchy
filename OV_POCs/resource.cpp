#include "resource.h"
#include "util.h"

namespace u = Util;

Resource::Resource() {}
Resource::Resource(int id, string name, string desc, string type, int stg, int tier, float bsize, float sg2, float amt) {
	oID = id;
	oName = name;
	oDesc = desc;
	oType = type;
	resStage = stg;
	resTier = tier;
	resBaseSize = bsize;
	oSG2 = sg2;
	resOAmt = amt;
}

void Resource::updateOAmt(string operation, float val) { resOAmt = u::updateVal(operation, val, resOAmt); }
int Resource::getStage() { return resStage; }
float Resource::getBaseSz() { return resBaseSize; }
int Resource::getTier() { return resTier; }
float Resource::getOAmt() { return resOAmt; }
