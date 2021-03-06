#ifndef UNIVERSE__H
#define UNIVERSE__H

#include <string>
#include <vector>
#include "plSystem.h"
#include "dataStructs.h"

using std::string;
using std::vector;

class Universe {
public:
	Universe();

	void createUniverse();
	void loadSystemNames();
	void createPlSystems();
	void addSystem(string name);
	void updateSystem(planetarySystem plSys);
	void setupSystems();

	planetarySystem getSystem(int index);
	vector<planetarySystem> getSystems();

	void updateExpTime(int tick, string operation);
	int calculateExpTime();
	void expansionPhase(); //Trigger an expansion phase
private:
	vector<planetarySystem> uSystems; //All known systems in the universe
	float uExpRate; //Rate that the universe expands at, exposing new systems
	int uTTNextExp; //Time to next expansion
	int uTSLastExp; //Time since last expansion
	int uNOfExp; //Number of expansions for calculations
	vector<string> uSysNames; //List of names from the database to be used for system creation
	float uSize; //Universe size in ?; how would this be useful or needed?
	

	int sysNmEl; //Element position for current system name
	string curSysName; //Storage for system creation	
	planetarySystem plSysInst;
	vector<strcSysName> tempSysNms;

	float sec;
};

#endif
