#include <string>
#include <vector>
#include <iostream>
#include "station.h"


using namespace std;



Station::Station() {
	oName = "default";
	
}

Station::Station(string sname) //pseudo constructor for stationProc array and other story/mission based stations
{
	oName = sname;
	
}

string Station::getName() {
	return oName;
}

void Station::setName(string name) {
	oName = name;
}