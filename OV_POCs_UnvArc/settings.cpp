#include "settings.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>

namespace Settings {

	/*
		This function is used to load any non-difficulty related setting values
	*/
	void loadSettings() {
		//try {
		setLogLevel(rawSettings.at("Logging_Level"));
		getDifficulties(rawSettings.at("Difficulties"));
		setMisTypes(rawSettings.at("Missile_Class_Types"));
		getPltTyps(rawSettings.at("Planet_Types"));
		setMxPlts(rawSettings.at("Max_Planets"));
		getOreStages(rawSettings.at("Ore_Stages"));
		setPltPopRand1Rng(false, rawSettings.at("Planet_Pop_Rand1_Min"));
		setPltPopRand1Rng(true, rawSettings.at("Planet_Pop_Rand1_Max"));
		setPltPopRand2Rng(false, rawSettings.at("Planet_Pop_Rand2_Min"));
		setPltPopRand2Rng(true, rawSettings.at("Planet_Pop_Rand2_Max"));
		setPltPopRand3Rng(false, rawSettings.at("Planet_Pop_Rand3_Min"));
		setPltPopRand3Rng(true, rawSettings.at("Planet_Pop_Rand3_Max"));
		setPltDefRandRng(false, rawSettings.at("Planet_Def_Rand_Min"));
		setPltDefRandRng(true, rawSettings.at("Planet_Def_Rand_Max"));
		setPltShdRandRng(false, rawSettings.at("Planet_Shd_Rand_Min"));
		setPltShdRandRng(true, rawSettings.at("Planet_Shd_Rand_Max"));
		setPltSzRandRng(false, rawSettings.at("Planet_Size_Range_Min"));
		setPltSzRandRng(true, rawSettings.at("Planet_Size_Range_Max"));
		setPltEksRandRng(false, rawSettings.at("Planet_EKS_Range_Min"));
		setPltEksRandRng(true, rawSettings.at("Planet_EKS_Range_Max"));
		setUnvStrtSysAmt(rawSettings.at("Unv_Starting_Systems"));
		setMxABelts(rawSettings.at("Max_Asteroid_Belts"));
		setABeltMxRoids(false, rawSettings.at("Min_Asteroids"));
		setABeltMxRoids(true, rawSettings.at("Max_Asteroids"));
		setABeltSzRnd(false, rawSettings.at("ABelt_Size_Rand_Min"));
		setABeltSzRnd(true, rawSettings.at("ABelt_Size_Rand_Max"));
		setRdSmRng(false, rawSettings.at("Asteroid_Small_Range_Min"));
		setRdSmRng(true, rawSettings.at("Asteroid_Small_Range_Max"));
		setRdMdRng(false, rawSettings.at("Asteroid_Medium_Range_Min"));
		setRdMdRng(true, rawSettings.at("Asteroid_Medium_Range_Max"));
		setRdLgRng(false, rawSettings.at("Asteroid_Large_Range_Min"));
		setRdLgRng(true, rawSettings.at("Asteroid_Large_Range_Max"));
		setUnvExpRate(rawSettings.at("Unv_Exp_Rate"));
		//}
		//catch (const std::exception& e) {

		//}
	}

	/*
		This function is used to load any difficulty related setting values.  Separate from other settings due to having
		the player need to choose the diff before processing the proper setting keys/values
	*/
	void loadDiffSettings() {
		//Prepare gDiffSettings if not already
		if (gDiffSettings.size() < 1) {
			for (string diff : gameDiffs) {
				gDiffSettings.push_back(diffSettings(diff));
			}
		}

		//Diff based settings - Do these after non-diff settings are loaded		
		for (diffSettings& diff : gDiffSettings) {
			for (auto mapEl : rawSettings) {
				string tmpStr = mapEl.first;

				if (tmpStr.find(diff.getDiff()) != string::npos) {
					diff.setSetting(mapEl.first, mapEl.second);
				}
			}
		}
	}

	void setDiffSettings(){
		for (diffSettings diff : gDiffSettings) {
			if (diff.getDiff() == sGameDifficulty){
				setPlyCXPBVal(diff.getPlrCXPBVal());
				setPlyShdDmgMlt(diff.getPlrWpnShdDmgMulti());
				setPlyArmDmgMlt(diff.getPlrWpnArmDmgMulti());
				setPlyHulDmgMlt(diff.getPlrWpnHulDmgMulti());
				setNPShdDmgMlt(diff.getNPWpnShdDmgMulti());
				setNPArmDmgMlt(diff.getNPWpnArmDmgMulti());
				setNPHulDmgMlt(diff.getNPWpnHulDmgMulti());
				setScpYld(diff.getScpYld());
				setHSSpnRt(diff.getHSecSpawn());
				setMSSpnRt(diff.getMSecSpawn());
				setLSSpnRt(diff.getLSecSpawn());
				setNSSpnRt(diff.getNSecSpawn());
				setPlyCXPFac(diff.getPlrCXPFactor());
				setNPCXPFac(diff.getNPCXPFactor());
			}
		}
	}

	void loadPltSettings() {
		//Prepare pltTypSettings if not already
		if (gPltTypSettings.size() < 1) {
			for (string type : pltTypes) {
				gPltTypSettings.push_back(pltTypeSettings(type,atoi(type.c_str())));
			}
		}

		//Diff based settings - Do these after non-diff settings are loaded
		for (pltTypeSettings& pltSetting : gPltTypSettings) {
			for (auto mapEl : rawSettings) {
				string tmpStr = mapEl.first;

				if (tmpStr.find(pltSetting.getSettingType()) != string::npos) {
					pltSetting = processPltSettings(pltSetting, mapEl.first, mapEl.second);
				}
			}			
		}
	}

	void loadRoidOSettings() {
		//Prepare pltTypSettings if not already
		if (gRoidStgSettings.size() < 1) {
			for (string stage : oreStages) {
				gRoidStgSettings.push_back(roidStageSettings(stage));
			}
		}

		//Diff based settings - Do these after non-diff settings are loaded
		for (roidStageSettings& roidStage : gRoidStgSettings) {
			for (auto mapEl : rawSettings) {
				string tmpStr = mapEl.first;

				if (tmpStr.find(roidStage.getStage()) != string::npos) {
					roidStage = processRoidSettings(roidStage, mapEl.first, mapEl.second);
				}
			}
		}
	}

	//Process a single plt type's settings which are now stored in keys and vals vectors
	pltTypeSettings processPltSettings(pltTypeSettings plts, string key, string val) {
		if (key.find("EKS_Range_Min") != string::npos) { plts.setPltEksRng(false, stof(val)); }
		else if (key.find("EKS_Range_Max") != string::npos) { plts.setPltEksRng(true, stof(val)); }
		else if (key.find("Size_Range_Min") != string::npos) { plts.setPltSzRng(false, stoi(val)); }
		else if (key.find("Size_Range_Max") != string::npos) { plts.setPltSzRng(true, stoi(val)); }
		else if (key.find("Outlier_Range_Min") != string::npos) { plts.setPltOutlrRng(false, stof(val)); }
		else if (key.find("Outlier_Range_Max") != string::npos) { plts.setPltOutlrRng(true, stof(val)); }
		else if (key.find("Size_Rand_Min") != string::npos) { plts.setPltSzRndRng(false, stof(val)); }
		else if (key.find("Size_Rand_Max") != string::npos) { plts.setPltSzRndRng(true, stof(val)); }

		return plts;
	}

	//Process a single plt type's settings which are now stored in keys and vals vectors
	roidStageSettings processRoidSettings(roidStageSettings roid, string key, string val) {
		if (key.find("Multi_Rand_Min") != string::npos) { roid.setRoidOStgMulRnd(false, stof(val)); }
		else if (key.find("Multi_Rand_Max") != string::npos) { roid.setRoidOStgMulRnd(true, stof(val)); }
		else if (key.find("Size_Multi") != string::npos) { roid.setRoidStgMulti(stoi(val)); }

		return roid;
	}

	void setLogLevel(string val) { logLvl = stoi(val); }
	void setPlyCXPBVal(string val) { plyCXPBVal = stoi(val); }
	void getPltTyps(string val) { pltTypes = splitVal(val); }
	void getDifficulties(string val) { gameDiffs = splitVal(val); }
	void getOreStages(string val) { oreStages = splitVal(val); }
	void setDifficulty(string val) { sGameDifficulty = val; }
	void setPlyShdDmgMlt(string val) { shdDmgMultPly = stof(val); }
	void setPlyArmDmgMlt(string val) { armDmgMultPly = stof(val); }
	void setPlyHulDmgMlt(string val) { hulDmgMultPly = stof(val); }
	void setNPShdDmgMlt(string val) { shdDmgMultNP = stof(val); }
	void setNPArmDmgMlt(string val) { armDmgMultNP = stof(val); }
	void setNPHulDmgMlt(string val) { hulDmgMultNP = stof(val); }
	void setScpYld(string val) { scpYldRt = stof(val); }
	void setMisTypes(string val) { missClsTypes = splitVal(val); }
	void setLSSpnRt(string val) { lSecSpawnRt = stof(val); }
	void setMSSpnRt(string val) { mSecSpawnRt = stof(val); }
	void setHSSpnRt(string val) { hSecSpawnRt = stof(val); }
	void setNSSpnRt(string val) { nSecSpawnRt = stof(val); }
	void setPlyCXPFac(string val) { plyCXPFactor = stof(val); }
	void setNPCXPFac(string val) { npCXPFactor = stof(val); }

	void setMxPlts(string val) { maxPlanets = stoi(val); }
	void setPltPopRand1Rng(bool bIsMax, string val){
		if (bIsMax) { pltPopRand1.fHigh = stof(val); }
		else { pltPopRand1.fLow = stof(val); }
	}
	
	void setPltPopRand2Rng(bool bIsMax, string val){
		if (bIsMax) { pltPopRand2.fHigh = stof(val); }
		else { pltPopRand2.fLow = stof(val); }
	}
	
	void setPltPopRand3Rng(bool bIsMax, string val){
		if (bIsMax) { pltPopRand3.fHigh = stof(val); }
		else { pltPopRand3.fLow = stof(val); }
	}
	
	void setPltDefRandRng(bool bIsMax, string val){
		if (bIsMax) { pltDefRand.fHigh = stof(val); }
		else { pltDefRand.fLow = stof(val); }
	}
	
	void setPltShdRandRng(bool bIsMax, string val){
		if (bIsMax) { pltShdRand.fHigh = stof(val); }
		else { pltShdRand.fLow = stof(val); }
	}
	
	void setPltSzRandRng(bool bIsMax, string val){
		if (bIsMax) { pltSizeRand.iHigh = stoi(val); }
		else { pltSizeRand.iLow = stoi(val); }
	}
	
	void setPltEksRandRng(bool bIsMax, string val){
		if (bIsMax) { pltEksRand.fHigh = stof(val); }
		else { pltEksRand.fLow = stof(val); }
	}

	void setUnvStrtSysAmt(string val) { unvStartSystems = stoi(val); }
	void setMxABelts(string val) { maxAsteroidBelts = stoi(val); }
	void setABeltMxRoids(bool bIsMax, string val) {
		if (bIsMax) { abltMaxAsteroids.iHigh = stoi(val); }
		else { abltMaxAsteroids.iLow = stoi(val); }
	}

	void setABeltSzRnd(bool bIsMax, string val) {
		if (bIsMax) { abltSizeRandRng.fHigh = stof(val); }
		else { abltSizeRandRng.fLow = stof(val); }
	}

	extern void setRdSmRng(bool bIsMax, string val) {
		if (bIsMax) { roidSmallRng.fHigh = stof(val); }
		else { roidSmallRng.fLow = stof(val); }
	}

	extern void setRdMdRng(bool bIsMax, string val) {
		if (bIsMax) { roidMedRng.fHigh = stof(val); }
		else { roidMedRng.fLow = stof(val); }
	}

	extern void setRdLgRng(bool bIsMax, string val) {
		if (bIsMax) { roidLargeRng.fHigh = stof(val); }
		else { roidLargeRng.fLow = stof(val); }
	}
	
	void setSMap(map<string, string> settingMap) {
		rawSettings = settingMap;

		loadSettings();
	}

	void setUnvExpRate(string val) { unvExpRate = stoi(val); }

	vector<string> splitVal(string val) {		
		vector<string> temp;
		curPos = val.find(',');
		
		while (curPos != std::string::npos) {
			temp.push_back(val.substr(prvPos, curPos - prvPos));
			prvPos = curPos + 1;
			curPos = val.find(',', prvPos);
		}
		
		temp.push_back(val.substr(prvPos, curPos - prvPos));
		prvPos = 0; //Reset for next call

		return temp;
	}

	void printMods() {
		cout << "Target Damage Modifiers" << endl;
		cout << "Player:" << endl;
		cout << "Shield Damage:			" << shdDmgMultPly * 100.0f << "%" << endl;
		cout << "Armor Damage:			" << armDmgMultPly * 100 << "%" << endl;
		cout << "Hull Damage:			" << hulDmgMultPly * 100 << "%" << endl;
		cout << endl;
		cout << "NPC:" << endl;
		cout << "Shield Damage:			" << shdDmgMultNP * 100 << "%" << endl;
		cout << "Armor Damage:			" << armDmgMultNP * 100 << "%" << endl;
		cout << "Hull Damage:			" << hulDmgMultNP * 100 << "%" << endl;
		cout << endl << endl;

		cout << "Spawn Rates" << endl;
		cout << "High Sec Spawn Rate:		" << hSecSpawnRt * 100 << "%" << endl;
		cout << "Mid Sec Spawn Rate:		" << mSecSpawnRt * 100 << "%" << endl;
		cout << "Low Sec Spawn Rate:		" << lSecSpawnRt * 100 << "%" << endl;
		cout << "Null Sec Spawn Rate:		" << nSecSpawnRt * 100 << "%" << endl;
		cout << endl << endl;

		cout << "Misc" << endl;
		cout << "Scrap Yield:			" << scpYldRt * 100 << "%" << endl;
		cout << "Player CXP Base Value:		" << plyCXPBVal << endl;
		cout << "Player CXP Factor:		" << plyCXPFactor << endl;
		cout << "NPC CXP Factor:			" << npCXPFactor << endl;
		cout << endl << endl;
	}


	//diffSettings Functions
	diffSettings::diffSettings(string diff) { dSDiff = diff; }

	void diffSettings::setSetting(string key, string val) {
		if (key.find("CXP_P_BaseVal") != string::npos) { dSCXPBVal = val; }
		else if (key.find("P_Weapon_Shd_Dmg_Multi") != string::npos) { dSPWpnShdDmgMulti = val; }
		else if (key.find("P_Weapon_Arm_Dmg_Multi") != string::npos) { dSPWpnArmDmgMulti = val; }
		else if (key.find("P_Weapon_Hull_Dmg_Multi") != string::npos) { dSPWpnHulDmgMulti = val; }
		else if (key.find("N_Weapon_Shd_Dmg_Multi") != string::npos) { dSNWpnShdDmgMulti = val; }
		else if (key.find("N_Weapon_Arm_Dmg_Multi") != string::npos) { dSNWpnArmDmgMulti = val; }
		else if (key.find("N_Weapon_Hull_Dmg_Multi") != string::npos) { dSNWpnHulDmgMulti = val; }
		else if (key.find("Scrap_Yield") != string::npos) { dSScpYld = val; }
		else if (key.find("HSec_Ship_SRate") != string::npos) { dSHSSpnRt = val; }
		else if (key.find("MSec_Ship_SRate") != string::npos) { dSMSSpnRt = val; }
		else if (key.find("LSec_Ship_SRate") != string::npos) { dSLSSpnRt = val; }
		else if (key.find("NSec_Ship_SRate") != string::npos) { dSNSSpnRt = val; }
		else if (key.find("CXP_P_Factor") != string::npos) { dSPCXPFactor = val; }
		else if (key.find("CXP_E_Factor") != string::npos) { dSNCXPFactor = val; }
	}
	
	string diffSettings::getPlrCXPBVal() { return dSCXPBVal; }
	string diffSettings::getPlrWpnShdDmgMulti() { return dSPWpnShdDmgMulti; }
	string diffSettings::getPlrWpnArmDmgMulti() { return dSPWpnArmDmgMulti; }
	string diffSettings::getPlrWpnHulDmgMulti() { return dSPWpnHulDmgMulti; }
	string diffSettings::getNPWpnShdDmgMulti() { return dSNWpnShdDmgMulti; }
	string diffSettings::getNPWpnArmDmgMulti() { return dSNWpnArmDmgMulti; }
	string diffSettings::getNPWpnHulDmgMulti() { return dSNWpnHulDmgMulti; }
	string diffSettings::getScpYld() { return dSScpYld; }
	string diffSettings::getHSecSpawn() { return dSHSSpnRt; }
	string diffSettings::getMSecSpawn() { return dSMSSpnRt; }
	string diffSettings::getLSecSpawn() { return dSLSSpnRt; }
	string diffSettings::getNSecSpawn() { return dSNSSpnRt; }
	string diffSettings::getPlrCXPFactor() { return dSPCXPFactor; }
	string diffSettings::getNPCXPFactor() { return dSNCXPFactor; }
	string diffSettings::getDiff() { return dSDiff; }

	
	//pltTypSetting Functions
	pltTypeSettings::pltTypeSettings(string type, int typVal) {
		plSType = "Type_" + type;
		plType = typVal;
	}

	string pltTypeSettings::getSettingType() { return plSType; }

	void pltTypeSettings::setPltEksRng(bool bIsMax, float val) {
		if (bIsMax) { plEksRng.fHigh = val; }
		else { plEksRng.fLow = val; }
	}

	Range pltTypeSettings::getPltEksRng() { return plEksRng; }
	void pltTypeSettings::setPltSzRng(bool bIsMax, int val) {
		if (bIsMax) { plSizeRng.iHigh = val; }
		else { plSizeRng.iLow = val; }
	}

	Range pltTypeSettings::getPltSzRng() { return plSizeRng; }
	void pltTypeSettings::setPltOutlrRng(bool bIsMax, float val) {
		if (bIsMax) { plOutlierRng.fHigh = val; }
		else { plOutlierRng.fLow = val; }
	}

	Range pltTypeSettings::getPltOutlrRng() { return plOutlierRng; }
	void pltTypeSettings::setPltSzRndRng(bool bIsMax, float val) {
		if (bIsMax) { plSizeRndRng.fHigh = val; }
		else { plSizeRndRng.fLow = val; }
	}

	Range pltTypeSettings::getPltSzRndRng() { return plSizeRndRng; }


	//roidStageSettings Functions
	roidStageSettings::roidStageSettings(string stage) { roidStage = "Stage" + stage; }
	void roidStageSettings::setRoidOStgMulRnd(bool bIsMax, float val) {
		if (bIsMax) { roidOStgMulRnd.fHigh = val; }
		else { roidOStgMulRnd.fLow = val; }
	}

	string roidStageSettings::getStage() { return roidStage; }
	void roidStageSettings::setRoidStgMulti(float val) { roidStgMulti = val; }
	Range roidStageSettings::getRoidOStgMulRnd() { return roidOStgMulRnd; }
	float roidStageSettings::getRoidStgMulti() { return roidStgMulti; }



	//new functions
	

	//New members
		


	//Namespace Members
	//Int Settings
	int logLvl = 1; //Set to 1 at start, game will alter the value later
	int plyCXPBVal; //Base value to determine CXP to next level for player
	int maxPlanets; //Max number of planets in a system
	int unvStartSystems; //Number of starting systems
	int maxAsteroidBelts; //Max number of ABelts per planet
	int unvExpRate; //Rate, in number of turns, before the universe will start expanding at start of game
	
	//Float Settings
	float shdDmgMultPly; //Shield Damage Multiplier - For Player
	float armDmgMultPly; //Armor Damage Multiplier - For Player
	float hulDmgMultPly; //Hull Damage Multiplier - For Player
	float shdDmgMultNP; //Shield Damage Multiplier - For Non-Player
	float armDmgMultNP; //Armor Damage Multiplier - For Non-Player
	float hulDmgMultNP; //Hull Damage Multiplier - For Non-Player
	float scpYldRt; //Scrap yield rate; the chance to find salvage after destroying a ship
	float lSecSpawnRt; //Low Sec spawn rate for ships; non-TL
	float mSecSpawnRt; //Med Sec spawn rate for ships
	float hSecSpawnRt; //High Sec spawn rate for ships
	float nSecSpawnRt;	//Null Sec spawn rate for ships
	float plyCXPFactor; //Factor used to determine CXP to next level for player
	float npCXPFactor; //Factor used to determine the CXP given to the player for destroying and enemy

	//String Settings
	vector<string> gameDiffs; //Game Difficulties
	vector<string> missClsTypes; //Missile Class Types
	string sGameDifficulty; //Selected game difficulty
	vector<string> pltTypes; //Types of Planets (classes, 0-5 by default)
	vector<string> oreStages; //Types of ore stages
	
	//Range Settings
	Range pltPopRand1; //Range used to calculate planet population
	Range pltPopRand2; //Range used to calculate planet population
	Range pltPopRand3; //Range used to calculate planet population
	Range pltDefRand; //Sets the range used in calculating planetary defense installations
	Range pltShdRand; //Sets the range used in calculating plaentary shield installations
	Range pltSizeRand; //Sets the range used in determining the size of a planet
	Range pltEksRand; //Sets the range used in determining the eks/size of a planet
	Range abltMaxAsteroids; //Sets the min and max number of asteroids per belt
	Range abltSizeRandRng; //Sets the min and max random range for asteroid belt size
	Range roidSmallRng; //Random vals which correspond to a small asteroid
	Range roidMedRng; //Random vals which correspond to a medium asteroid
	Range roidLargeRng; //Random vals which correspond to a large asteroid

	//Reference Settings
	vector<diffSettings> gDiffSettings;
	vector<pltTypeSettings> gPltTypSettings;
	vector<roidStageSettings> gRoidStgSettings; //Stores all of the data related to specific ore/asteroid stages
	
							
	//Misc
	map<string, string> rawSettings, rawSettingsTemp;
	int curPos, prvPos;
	map<string, string>::iterator itr;
	vector<string> keys, vals;	
}