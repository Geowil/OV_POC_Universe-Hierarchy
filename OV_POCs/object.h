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
	void setSecLvl(float seclvl);
	void setAffil(std::string afil);
	void setDisp(); //Don't pass to it, this is based off of relation which will be added later
	void setRace(std::string race);

	void updateSecLvl(std::string operation, float new_sec);

	float getXPos();
	float getYPos();
	float getZPos();
	int getID();
	std::string getName();
	std::string getDesc();
	std::string getType();
	std::string getCls();
	std::string getSubCls();
	std::string getAffil();
	std::string getDisp();
	std::string getRace();
	float getSG2();
	float getSecLevel();

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
	std::string oAffil; //affilliated organization, coporation, or government
	std::string oDisp;
	std::string oRace;

	/*
	Relations
		This should be a vector of a new class called Relations.  The class should have two values, first the name of the organization, if met, and second the relation with that organization

		Other features can be built around this later
	*/
	float oSecLvl;
	float oSG2;
};

#endif
