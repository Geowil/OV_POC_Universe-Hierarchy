#ifndef OBJECT__H
#define OBJECT__H

#include <string>
#include <vector>

class Object {
public:
	void setXPos(float x);
	void setYPos(float y);
	void setZPos(float z);
	void setName(std::string name);

	float getXPos();
	float getYPos();
	float getZPos();
	std::string getName();

protected:
	float xPos;
	float yPos;
	float zPos;

	std::string oName;
	std::vector<float> oRes; //Resources (ie xarn, diamonds, etc.); see database setting for ordering of elements
};

#endif
