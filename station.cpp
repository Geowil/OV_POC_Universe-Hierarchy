#include <string>
#include <vector>
#include <iostream>
#include "station.h"


using namespace std;



Station::Station() {
	sName = "default";
	
}

Station::Station(string sname) //pseudo constructor for stationProc array and other story/mission based stations
{
	sName = sname;
	
}

string Station::getName() {
	return sName;
}

void Station::setName(string name) {
	sName = name;
}