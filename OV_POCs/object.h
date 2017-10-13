#ifndef OBJECT__H
#define OBJECT__H

#include <string>
#include <vector>

class Object {
public:
	void setXPos(float x);
	void setYPos(float y);
	void setZPos(float z);
	void setID(int id);
	void setName(std::string name);
	void setDesc(std::string desc);
	void setType(std::string typ);
	void setCls(std::string cls);
	void setSubCls(std::string subcls);
	void setSG2(float newsg2);

	float getXPos();
	float getYPos();
	float getZPos();
	int getID();
	std::string getName();
	std::string getDesc();
	std::string getType();
	std::string getCls();
	std::string getSubCls();
	float getSG2();

protected:
	float xPos;
	float yPos;
	float zPos;

	int oID;
	std::string oName;
	std::string oDesc;
	std::string oType;
	std::string oCls;
	std::string oSubCls;
	float oSG2;
};

#endif
