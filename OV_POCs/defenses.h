#ifndef DEFENSES_H
#define DEFENSES_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Defense {
public:
	Defense(); //defense contructor
	Defense(string name); //defense contructor

	Defense* rDefense();

	string getName(); //get weapon name

										 
private:
	
	string	dName; //name
			
};


class Shield {
public:
	Shield();
	Shield(string name);

	Shield* rShield();
	
	string getName();

	

private:
	string	mName;
	
};
#endif