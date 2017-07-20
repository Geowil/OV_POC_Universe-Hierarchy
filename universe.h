#ifndef UNIVERSE__H
#define UNIVERSE__H

#include <string>
#include <vector>
#include "plSystem.h"

using std::string;
using std::vector;

class Universe {
public:
	Universe();

	void createUniverse();
	void createPlSystems();
	void addSystem(planetarySystem plSys);
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

	float uSize; //Universe size in ?; how would this be useful or needed?

};

#endif
