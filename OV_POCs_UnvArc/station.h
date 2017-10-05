#ifndef STATION_H
#define STATION_H

#include <string>
#include "object.h"

using std::string;

class Game;

class Station : public Object{
public:
	Station();


	Station(string sname);

	string getName();
	
	void setName(string name);
	

private:
	int			sSLevel; //Station Level
	float		sCMulti; //Cost Multiplier
};
#endif
