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
	planetarySystem(int id, string sysName, float sec);

	planetarySystem createPSystem() { return planetarySystem(); }

	
	float getSecRating();

	void createPlanets();
	void addPlanet(Planet plt); //Only used when loading
	void modifyPlanet(Planet pl);
	vector<Planet> getPlanets();
	Planet getPlanet(int index);
	

	void updateSecRating(float sec, string operation);
	void generatePlanets();

	int getDefenses(float rand, float eks);
	int getShields(float rand, float eks);
	float calcPop(float pERand, float pSRand, float popRand1, float popRand2, float popRand3);

	Planet addDefenses(Planet plt);
	Planet addShields(Planet plt);

private:
	float plsSec; //Security Rating
	vector<Planet> plsPlanets;

	float pERand2, pSRand2, pPStore2;
	int pSRRand2, numODef, numOShd;
	long long int pPMax2;
	bool bPPGen2;

	Planet pltInst; //Temp instance to store a planet while being generated
		
	int nOfDef;
	int nOfShd;
	int i1; //Iterators
};
#endif