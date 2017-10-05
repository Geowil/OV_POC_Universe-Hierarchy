#ifndef PLSYSTEM__H
#define PLSYSTEM__H

#include <string>
#include <vector>
#include "planet.h"
#include "object.h"

using std::vector;
using std::string;

class planetarySystem: public Object {
public:
	planetarySystem();
	planetarySystem(string sysName);
	planetarySystem(string sysName, float sec);

	planetarySystem createPSystem() { return planetarySystem(); }

	void setName(string name);
	
	float getSecRating();
	string getName();

	void createPlanets();
	void addPlanet(string name);
	void modifyPlanet(Planet pl);
	vector<Planet> getPlanets();
	Planet getPlanet(int index);
	

	void updateSecRating(float sec, string operation);
	void generatePlanets();


	Planet addDefenses(Planet plt);
	Planet addShields(Planet plt);

private:
	string plsName;
	float plsSec; //Security Rating

	float pERand2; //External value tag: float range
	int pSRRand2; //External value tag: int range
	float pSRand2;
	float pPStore2; //Calculate the population and return to pPStore2
	long long int pPMax2;
	bool bPPGen2;

	int numODef, numOShd;
	Planet pltInst;

	vector<Planet> plsPlanets;
};
#endif