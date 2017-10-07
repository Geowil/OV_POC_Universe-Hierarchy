#include "object.h"

void Object::setXPos(float x) {
	xPos = x;
}

void Object::setYPos(float y) {
	yPos = y;
}

void Object::setZPos(float z) {
	zPos = z;
}

void Object::setName(std::string name) {
	oName = name;
}

float Object::getXPos() {
	return xPos;
}

float Object::getYPos() {
	return yPos;
}

float Object::getZPos() {
	return zPos;
}

std::string Object::getName() {
	return oName;
}
