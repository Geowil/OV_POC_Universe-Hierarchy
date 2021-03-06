#include "object.h"
#include "util.h"

namespace u = Util;

void Object::setXPos(float x) { xPos = x; }
void Object::setYPos(float y) { yPos = y; }
void Object::setZPos(float z) { zPos = z; }
void Object::setID(int id) { oID = id;}
void Object::setName(std::string name) { oName = name;}
void Object::setDesc(std::string desc) { oDesc = desc; }
void Object::setType(std::string typ) { oType = typ; }
void Object::setCls(std::string cls) { oCls = cls; }
void Object::setSubCls(std::string subcls) { oSubCls = subcls; }
void Object::setSG2(float sg2) { oSG2 = sg2; }

float Object::getXPos() { return xPos; }
float Object::getYPos() { return yPos; }
float Object::getZPos() { return zPos; }
int Object::getID() { return oID; }
std::string Object::getName() { return oName; }
std::string Object::getDesc() { return oDesc; }
std::string Object::getType() { return oType; }
std::string Object::getCls() { return oCls; }
std::string Object::getSubCls() { return oSubCls; }
float Object::getSG2() { return oSG2; }
