#ifndef SETTINGS__H
#define SETTINGS__H

#include <string>
#include <vector>
#include <iostream>
#include "range.h"
#include <map>

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;

namespace Settings {

	//classes
	class diffSettings;
	class pltTypeSettings;
	class roidStageSettings;
	class oreTierSettings;

	extern void loadSettings();
	extern void loadDiffSettings();
	extern void loadPltSettings();
	extern void loadRoidOSettings();
	extern void loadOreTypeSettings();

	extern pltTypeSettings processPltSettings(pltTypeSettings plts, string key, string val);
	extern roidStageSettings processRoidSettings(roidStageSettings roid, string key, string val);
	extern oreTierSettings processOreTierSettings(oreTierSettings tier, string key, string val);

	extern void setDiffSettings();
	extern void setLogLevel(string val);
	extern void setPlyCXPBVal(string val);	
	extern void setDifficulty(string val);
	extern void setPlyShdDmgMlt(string val);
	extern void setPlyArmDmgMlt(string val);
	extern void setPlyHulDmgMlt(string val);
	extern void setNPShdDmgMlt(string val);
	extern void setNPArmDmgMlt(string val);
	extern void setNPHulDmgMlt(string val);
	extern void setScpYld(string val);
	extern void setMisTypes(string val);
	extern void setLSSpnRt(string val);
	extern void setMSSpnRt(string val);
	extern void setHSSpnRt(string val);
	extern void setNSSpnRt(string val);
	extern void setPlyCXPFac(string val);
	extern void setNPCXPFac(string val);
	extern void setMxPlts(string val);
	extern void setPltPopRand1Rng(bool bIsMax, string val);
	extern void setPltPopRand2Rng(bool bIsMax, string val);
	extern void setPltPopRand3Rng(bool bIsMax, string val);
	extern void setPltDefRandRng(bool bIsMax, string val);
	extern void setPltShdRandRng(bool bIsMax, string val);
	extern void setPltSzRandRng(bool bIsMax, string val);
	extern void setPltEksRandRng(bool bIsMax, string val);
	extern void setUnvStrtSysAmt(string val);
	extern void setMxABelts(string val);
	extern void setABeltMxRoids(bool bIsMax, string val);
	extern void setABeltSzRnd(bool bIsMax, string val);
	extern void setRdSzRandRng(bool bIsMax, string val);
	extern void setRdSmRng(bool bIsMax, string val);
	extern void setRdMdRng(bool bIsMax, string val);
	extern void setRdLgRng(bool bIsMax, string val);
	extern void setUnvExpRate(string val);
	extern void setHighSecRng(bool bIsMax, string val);
	extern void setMidSecRng(bool bIsMax, string val);
	extern void setLowSecRng(bool bIsMax, string val);
	extern void setNullSecRng(bool bIsMax, string val);

	extern void getDifficulties(string val);
	extern void getPltTyps(string val);
	extern void getOreStages(string val);
	extern void getOreTiers(string val);
	
	extern void setSMap(map<string, string> settingMap);
	extern vector<string> splitVal(string val);
	extern void printMods();

	
	

	//Int Settings
	extern int logLvl;
	extern int plyCXPBVal; //Base value to determine CXP to next level for player
	extern int maxPlanets; //Max number of planets in a system
	extern int unvStartSystems; //Number of starting systems
	extern int maxAsteroidBelts; //Max number of ABelts per planet
	extern int unvExpRate; //Rate, in number of turns, before the universe will start expanding at start of game

	//Float Settings
	extern float shdDmgMultPly; //Shield Damage Multiplier - For Player
	extern float armDmgMultPly; //Armor Damage Multiplier - For Player
	extern float hulDmgMultPly; //Hull Damage Multiplier - For Player
	extern float shdDmgMultNP; //Shield Damage Multiplier - For Non-Player
	extern float armDmgMultNP; //Armor Damage Multiplier - For Non-Player
	extern float hulDmgMultNP; //Hull Damage Multiplier - For Non-Player
	extern float scpYldRt; //Scrap yield rate; the chance to find salvage after destroying a ship
	extern float lSecSpawnRt; //Low Sec spawn rate for ships; non-TL
	extern float mSecSpawnRt; //Med Sec spawn rate for ships
	extern float hSecSpawnRt; //High Sec spawn rate for ships
	extern float nSecSpawnRt; //Null Sec spawn rate for ships
	extern float plyCXPFactor; //Factor used to determine CXP to next level for player
	extern float npCXPFactor; //Factor used to determine the CXP given to the player for destroying and enemy

	//String Settings
	extern vector<string> gameDiffs; //Game Difficulties
	extern vector<string> missClsTypes; //Missile Class Types
	extern vector<string> pltTypes; //Types of Planets (classes, 0-5 by default)
	extern vector<string> oreStages; //Types of ore stages
	extern vector<string> oreTiers; //Types of ore tiers
	extern string sGameDifficulty; //Selected game difficulty

	//Range Settings
	extern Range pltPopRand1; //Range used to calculate planet population
	extern Range pltPopRand2; //Range used to calculate planet population
	extern Range pltPopRand3; //Range used to calculate planet population
	extern Range pltDefRand; //Sets the range used in calculating planetary defense installations
	extern Range pltShdRand; //Sets the range used in calculating plaentary shield installations
	extern Range pltSizeRand; //Sets the range used in determining the size of a planet
	extern Range pltEksRand; //Sets the range used in determining the eks/size of a planet
	extern Range abltMaxAsteroids; //Sets the min and max number of asteroids per belt
	extern Range abltSizeRandRng; //Sets the min and max random range for asteroid belt size
	extern Range roidSizeRandRng; //Sets the min and max range for asteroid size calculation
	extern Range roidSmallRng; //Random vals which correspond to a small asteroid
	extern Range roidMedRng; //Random vals which correspond to a medium asteroid
	extern Range roidLargeRng; //Random vals which correspond to a large asteroid
	extern Range secRtHighRng; //High security rating range
	extern Range secRtMidRng; //Mid security rating range
	extern Range secRtLowRng; //Low security rating range
	extern Range secRtNullRng; //Null security rating range


	//Reference Settings
	extern vector<diffSettings> gDiffSettings; //Stores all of the data related to setting difficulty-specific values
	extern vector<pltTypeSettings> gPltTypSettings; //Stores all of the data related to specific planet type settings
	extern vector<roidStageSettings> gRoidStgSettings; //Stores all of the data related to specific ore/asteroid stages
	extern vector<oreTierSettings> gOreTierSettings; //Stores all of the data related to specific ore tiers

	//Misc - used to process setting data
	extern map<string, string> rawSettings, rawSettingsTemp;
	extern int curPos, prvPos;
	extern map<string, string>::iterator itr;
	extern map<string, string> plSettings;
	extern vector<string> keys, vals;
}


class Settings::diffSettings {
public:
	diffSettings(string diff);

	void setSetting(string key, string val);

	string getPlrCXPBVal();
	string getPlrWpnShdDmgMulti();
	string getPlrWpnArmDmgMulti();
	string getPlrWpnHulDmgMulti();
	string getNPWpnShdDmgMulti();
	string getNPWpnArmDmgMulti();
	string getNPWpnHulDmgMulti();
	string getScpYld();
	string getHSecSpawn();
	string getMSecSpawn();
	string getLSecSpawn();
	string getNSecSpawn();
	string getPlrCXPFactor();
	string getNPCXPFactor();
	string getDiff();

private:
	string dSDiff; //Difficulty being stored

	//Difficulty settings
	string dSCXPBVal;
	string dSPWpnShdDmgMulti;
	string dSPWpnArmDmgMulti;
	string dSPWpnHulDmgMulti;
	string dSNWpnShdDmgMulti;
	string dSNWpnArmDmgMulti;
	string dSNWpnHulDmgMulti;
	string dSScpYld;
	string dSHSSpnRt;
	string dSMSSpnRt;
	string dSLSSpnRt;
	string dSNSSpnRt;
	string dSPCXPFactor;
	string dSNCXPFactor;
};

class Settings::pltTypeSettings {
public:
	pltTypeSettings(string type, int typVal);

	string getSettingType();
	//int getPltType();

	//void setSetting(string key, string val);

	void setPltEksRng(bool bIsMax, float val);
	Range getPltEksRng();

	void setPltSzRng(bool bIsMax, int val);
	Range getPltSzRng();

	void setPltOutlrRng(bool bIsMax, float val);
	Range getPltOutlrRng();

	void setPltSzRndRng(bool bIsMax, float val);
	Range getPltSzRndRng();

private:
	string plSType;
	int plType;

	Range plEksRng;
	Range plSizeRng;
	Range plOutlierRng;
	Range plSizeRndRng;
};

class Settings::roidStageSettings {
public:
	roidStageSettings(string stage);

	string getStage();
	int getStageI();
	void setRoidOStgMulRnd(bool bIsMax, float val);
	void setRoidStgMulti(float val);

	Range getRoidOStgMulRnd();
	float getRoidStgMulti();

private:
	string roidStage;
	int roidStageI;

	Range roidOStgMulRnd;
	float roidStgMulti;

};

class Settings::oreTierSettings {
public:
	oreTierSettings(string tier);

	void setHighRng(bool bIsMax, float val);
	void setMidRng(bool bIsMax, float val);
	void setLowRng(bool bIsMax, float val);
	void setNullRng(bool bIsMax, float val);

	string getTier();
	int getTierVal();
	Range getHighRng();
	Range getMidRng();
	Range getLowRng();
	Range getNullRng();

private:
	string tierName;
	int tierVal;

	Range tierHighRng;
	Range tierMidRng;
	Range tierLowRng;
	Range tierNullRng;
};


#endif

/*
 Shield Damage mutiplier functionality:
 raw damage comes into function
 raw damage (outgoing damage not incoming) times multiplier
 apply any modifications via effects
 apply damage to shield 

 if any remainder, remove multiplier and any effect multipliers for shield damage
 apple any effect multipliers for armor damage etc.
*/