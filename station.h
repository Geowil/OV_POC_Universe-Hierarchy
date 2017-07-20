#ifndef STATION_H
#define STATION_H

#include <string>

using std::string;

class Game;

class Station {
public:
	Station();


	Station(string sname);

	string getName();
	
	void setName(string name);
	

private:
	string		sName; //Name
};
#endif
