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
	class moonClsSettings;

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
	extern void setPltPopRand1Rng(Range rng);
	extern void setPltPopRand2Rng(Range rng);
	extern void setPltPopRand3Rng(Range rng);
	extern void setPltDefRandRng(Range rng);
	extern void setPltShdRandRng(Range rng);
	extern void setPltSzRandRng(Range rng);
	extern void setPltEksRandRng(Range rng);
	extern void setUnvStrtSysAmt(string val);
	extern void setMxABelts(string val);
	extern void setABeltMxRoids(Range rng);
	extern void setABeltSzRnd(Range rng);
	extern void setRdSzRandRng(Range rng);
	extern void setRdSmRng(Range rng);
	extern void setRdMdRng(Range rng);
	extern void setRdLgRng(Range rng);
	extern void setRdHgRng(Range rng);
	extern void setUnvExpRate(string val);
	extern void setHighSecRng(Range rng);
	extern void setMidSecRng(Range rng);
	extern void setLowSecRng(Range rng);
	extern void setNullSecRng(Range rng);

	extern void getDifficulties(string val);
	extern void getPltTyps(string val);
	extern void getOreStages(string val);
	extern void getOreTiers(string val);
	
	extern void setSMap(map<string, string> settingMap);
	extern vector<string> splitVal(string val);
	extern void printMods();

	
	//New Functions
	extern void setOreStgRndRng(Range rng);
	extern void setOreTrRndRng(Range rng);
	extern void setMnClsRng(Range rng);
	extern void setDpoSmSzRng(Range rng);
	extern void setDpoMdSzRng(Range rng);
	extern void setDpoLgSzRng(Range rng);
	extern void setDpoHgSzRng(Range rng);
	extern void setMnClsRndRng(Range rng);
	extern void setMnAmtRndRng(Range rng);
	extern void loadMnClsSettings();
	extern moonClsSettings processMnClsSettings(moonClsSettings mcs, string key, string val);


	//New Members
	extern Range oreStgRnd;
	extern Range oreTrRnd;
	extern Range mnCls;
	extern Range dpoSmSz;
	extern Range dpoMdSz;
	extern Range dpoLgSz;
	extern Range dpoHgSz;
	extern Range mnClsRnd;
	extern Range mnAmtRnd;
	extern vector<moonClsSettings> gMnClsSettings;



	//Int Settings
	extern int logLvl;
	extern int plyCXPBVal;
	extern int maxPlanets;
	extern int unvStartSystems;
	extern int maxAsteroidBelts;
	extern int unvExpRate;

	//Float Settings
	extern float shdDmgMultPly;
	extern float armDmgMultPly;
	extern float hulDmgMultPly;
	extern float shdDmgMultNP;
	extern float armDmgMultNP;
	extern float hulDmgMultNP;
	extern float scpYldRt;
	extern float lSecSpawnRt;
	extern float mSecSpawnRt;
	extern float hSecSpawnRt;
	extern float nSecSpawnRt;
	extern float plyCXPFactor;
	extern float npCXPFactor;

	//String Settings
	extern vector<string> gameDiffs;
	extern vector<string> missClsTypes;
	extern vector<string> pltTypes;
	extern vector<string> oreStages;
	extern vector<string> oreTiers;
	extern string sGameDifficulty;

	//Range Settings
	extern Range pltPopRand1; 
	extern Range pltPopRand2; 
	extern Range pltPopRand3; 
	extern Range pltDefRand; 
	extern Range pltShdRand; 
	extern Range pltSizeRand; 
	extern Range pltEksRand; 
	extern Range abltMaxAsteroids;
	extern Range abltSizeRandRng;
	extern Range roidSizeRandRng; 
	extern Range roidSmallRng;
	extern Range roidMedRng;
	extern Range roidLargeRng;
	extern Range roidHugeRng;
	extern Range secRtHighRng;
	extern Range secRtMidRng;
	extern Range secRtLowRng;
	extern Range secRtNullRng;


	//Reference Settings
	extern vector<diffSettings> gDiffSettings;
	extern vector<pltTypeSettings> gPltTypSettings;
	extern vector<roidStageSettings> gRoidStgSettings;
	extern vector<oreTierSettings> gOreTierSettings;

	//Misc - used to process setting data
	extern map<string, string> rawSettings, rawSettingsTemp;
	extern int i1;
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

	void addPltDefRng(float val);
	void addPltShdRng(float val);

	float getPltDefRng(int pos);
	float getPltShdRng(int pos);

	int getPltDefRngSz();
	int getPltShdRngSz();

	void setPltEksRng(Range rng);
	Range getPltEksRng();

	void setPltSzRng(Range rng);
	Range getPltSzRng();

	void setPltOutlrRng(Range rng);
	Range getPltOutlrRng();

	void setPltSzRndRng(Range rng);
	Range getPltSzRndRng();

	int getPltMnClsSz();
	int getPltMnAmtSz();
	int getPltMnCls(int pos);
	int getPltMnAmt(int pos);

	Range getPltMnClsRng();

	void setPltMnCls(Range rng);
	void setPltMnClsVect(vector<int> vect);
	void setPltMnAmtVect(vector<int> vect);

private:
	string plSType;
	int plType;

	Range plEksRng;
	Range plSizeRng;
	Range plOutlierRng;
	Range plSizeRndRng;
	Range pltMoonCLS;
	vector<Range> plDefRngs;
	vector<Range> plShdRngs;
	vector<int> pltMoonClsVect; //Stores single-range values for what types of moons can be generated for the given planet type
	vector<int> pltMoonAmtVect; //Stores single-range values for the number of moons that can be generated for the given planet type
};

class Settings::roidStageSettings {
public:
	roidStageSettings(string stage);

	string getStage();
	int getStageI();
	void setRoidOStgMulRnd(Range rng);
	void setRoidStgMulti(float val);

	void setRoidSmRng(Range rng);
	void setRoidMdRng(Range rng);
	void setRoidLgRng(Range rng);
	void setRoidHgRng(Range rng);

	Range getRoidOStgMulRnd();
	float getRoidStgMulti();
	Range getRoidSmRng();
	Range getRoidMdRng();
	Range getRoidLgRng();
	Range getRoidHgRng();

private:
	string roidStage;
	int roidStageI;

	Range roidOStgMulRnd;
	float roidStgMulti;

	//Ranges that determine what rates ore stages are used within certain roid sizes
	Range roidSmallRng;
	Range roidMedRng;
	Range roidLargeRng;
	Range roidHugeRng;

};

class Settings::oreTierSettings {
public:
	oreTierSettings(string tier);

	void setHighRng(Range rng);
	void setMidRng(Range rng);
	void setLowRng(Range rng);
	void setNullRng(Range rng);

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

class Settings::moonClsSettings {
public:
	moonClsSettings(string cls);

	void setMnDpSmSpnRng(Range rng);
	void setMnDpMdSpnRng(Range rng);
	void setMnDpLgSpnRng(Range rng);
	void setMnDpHgSpnRng(Range rng);

	string getMnCls();
	int getMnClsInt();
	Range getMnDpSmSpnRng();
	Range getMnDpMdSpnRng();
	Range getMnDpLgSpnRng();
	Range getMnDpHgSpnRng();


private:
	string mnCls;
	int mnClsInt;

	Range mnDepoSmSpnRng;
	Range mnDepoMdSpnRng;
	Range mnDepoLgSpnRng;
	Range mnDepoHgSpnRng;

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