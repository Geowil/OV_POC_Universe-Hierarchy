#ifndef PLSYSTEM__H
#define PLSYSTEM__H

#include <string>
#include <vector>
#include "planet.h"

using std::vector;
using std::string;

class planetarySystem {
public:
	planetarySystem();
	planetarySystem(string sysName, float sec);

	void setSysName(string name);
	
	float getSecRating();
	string getSysName();

	void createPlanets();
	void addPlanet(Planet pl);
	void modifyPlanet(Planet pl);
	vector<Planet> getPlanets();
	Planet getPlanet(int index);

	

	void updateSecRating(float sec, string operation);
	void generatePlanets();


	Planet addDefenses(Planet plt);
	Planet addShields(Planet plt);

	string getName();

private:
	string plsName;
	float plsSec;

	float pERand2; //External value tag: float range
	int pSRRand2; //External value tag: int range
	float pSRand2;
	float pPStore2; //Calculate the population and return to pPStore2
	long long int pPMax2;
	bool bPPGen2;

	int numODef, numOShd;

	vector<Planet> plsPlanets;
};
#endif