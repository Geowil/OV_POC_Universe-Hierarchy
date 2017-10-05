#ifndef MOON_H
#define MOON_H

#include <string>
#include "object.h"

using std::string;

class Moon : public Object{
public:
	Moon();
	Moon(string name);

	string getName();
	void setName(string name);

private:
	string mName;
};
#endif