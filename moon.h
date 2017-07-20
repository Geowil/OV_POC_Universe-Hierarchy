#ifndef MOON_H
#define MOON_H

#include <string>

using std::string;

class Moon {
public:
	Moon();
	Moon(string name);

	string getName();
	void setName(string name);

private:
	string mName;
};
#endif