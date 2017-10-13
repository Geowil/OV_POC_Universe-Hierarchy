#ifndef DEFENSES_H
#define DEFENSES_H

#include <string>
#include <vector>
#include "object.h"

using std::string;
using std::vector;

class Defense : public Object {
public:
	Defense(); //defense contructor
	Defense(string name); //defense contructor

	Defense* rDefense();


										 
private:
			
};


class Shield : public Object {
public:
	Shield();
	Shield(string name);

	Shield* rShield();
	

	

private:
	
};
#endif