#ifndef RESORUCE__H
#define RESORUCE__H

#include <string>
#include "settings.h"
#include "dataSystem.h"

using std::string;

class Resource {
public:
	Resource();
	Resource(int id, string name, string desc, string type, int stg, int tier, float bsize, float sg2, float amt);

	int getID();
	string getName();
	string getType();
	int getTier();
	int getStage();
	float getBaseSz();
	float getSG2();
	string getDesc();
	float getOAmt();

	void updateOAmt(string operation, float val);

private:
	int resID;
	string resName; //Resource Name
	string resDesc; //Resource Description
	int resStage; //Resource Stage (ore)
	int resTier; //Resource tier (not 'resource')
	string resType; //Is this an ore or a resource
	float resBaseSize; //Used for calculating asteroid size
	float resSG2;
	float resOAmt; //Ore Amount
};

#endif;