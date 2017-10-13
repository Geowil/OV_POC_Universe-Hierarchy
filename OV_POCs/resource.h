#ifndef RESORUCE__H
#define RESORUCE__H

#include <string>
#include "settings.h"
#include "dataSystem.h"
#include "object.h"

using std::string;

class Resource : public Object{
public:
	Resource();
	Resource(int id, string name, string desc, string type, int stg, int tier, float bsize, float sg2, float amt);

	int getTier();
	int getStage();
	float getBaseSz();
	float getOAmt();

	void updateOAmt(string operation, float val);

private:
	int resStage; //Resource Stage (ore)
	int resTier; //Resource tier (not 'resource')
	float resBaseSize; //Used for calculating asteroid size
	float resOAmt; //Ore Amount
};

#endif;