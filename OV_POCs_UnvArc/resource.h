#ifndef RESORUCE__H
#define RESORUCE__H

#include <string>
#include "settings.h"
#include "dataSystem.h"

using std::string;

class Resource {
public:
	Resource();

	void setupRes(int id, string name, string type, string ore, int stg, float bsize, float sg2);

	int getID();
	string getName();
	string getType();
	string getOre();
	int getStage();
	float getBaseSz();
	float getSG2();

private:
	int resID;
	string resName; //Resource Name
	int resStage; //Resource Stage (ore)
	string resType; //Is this an ore or a resource
	float resBaseSize; //Used for calculating asteroid size
	float resSG2;
	string resOre; //Ore name, if any
};

#endif;