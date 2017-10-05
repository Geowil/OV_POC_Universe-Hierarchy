#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <vector>
#include "moon.h"
#include "defenses.h"
#include "station.h"
#include "aBelt.h"
#include "object.h"

using std::string;
using std::vector;

class Planet : public Object{
public:
	Planet();  //constructor
	Planet(string name); //constructor 2
	Planet(string name, float eks, long long int pop); //constructor 3

	Planet createPlanet() { return Planet(); }

	Planet* getPlanet(); //Return this

	void addPDefenses(bool defense, int odid, bool shield, int psid, bool defender); //Initailize planetray defenses

	string getName(); //Get planet name
	
	long long int getPop(); //Get planet population
	string getPopS();
	long long int getMPop(); //Get planet max population
	string getMPopS();
	float getSize(); //Ger planet size
	float getEKS(); //Get EKS rating

	bool bPIsDest();
	//bool bPIsPOwned();

	void setName(string name);
	void updatePop(long long int pop, string operation);
	void updateMPop(long long int pop, string operation);
	void setSize(float size);
	void setEKS(float eks);
	
	void setPDest(int i);
	

	void setupPlanetObjects();
	void createBelts();
	void addBelt(string name, float size, int ramount, bool full); //Load a saved asteroid belt
	void modifyABelt(aBelt ab);
	vector<aBelt> getABelts();
	aBelt getABelt(int index);

	void createMoons();
	void addMoon(string name); //Load a saved asteroid belt
	void modifyMoon(Moon moon);
	vector<Moon> getMoons();
	Moon getMoon(int index);

	void createStations();
	void addStation(string name); //Load a saved asteroid belt
	void modifyStation(Station stat);
	vector<Station> getStations();
	Station getStation(int index);

	void modifyDefense(Defense def);
	vector<Defense> getDefenses();
	Defense getDefense(int index);

	void modifyShield(Shield shd);
	vector<Shield> getShields();
	Shield getShield(int index);

	
							
private:

	string plName; //planet name
	string plDispo; //Planet Disposition
	string plAffil; //Planet Affiliation
	string plRace;
	float pEKS; //planet enhanced kardasev scale value
	float pSize; //planet size, determines the total population possible
	long long int pPop, pMPop; //planet population/max population
	bool bIsPOwned; //bool: is this planet owned by the player?
	bool bIsDest; //bool: is this planet destroyed (has it been attacked and laid barren)?
	string pStatus; //Planet status, for battle processing

	string name;
	int ramount;
	float size;
	bool full;

	int i; //For for loops

	int pTDist; //Store the distance needed to travel to reach this planet; for calculating if a ship is encountered

	string trailer, sStorage, sPPop, sPMPop; //Strings for simplified planet population returns
	float popStorage;

	int beltRand; //Rand for belt creation
	vector<aBelt> belts; //A. Belts
	vector<Moon> moons;
	vector<Station> stations;
	vector<Defense> pDef;
	vector<Shield> pShd;


				  
};
#endif