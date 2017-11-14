#include "settings.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "util.h"

namespace u = Util;

namespace Settings {

	/*
		This function is used to load any non-difficulty related setting values
	*/
	void loadSettings() {
		try {
			setLogLevel(rawSettings.at("Logging_Level"));
			getDifficulties(rawSettings.at("Difficulties"));
			setMisTypes(rawSettings.at("Missile_Class_Types"));
			getPltTyps(rawSettings.at("Planet_Types"));
			setMxPlts(rawSettings.at("Max_Planets"));
			getOreStages(rawSettings.at("Ore_Stages"));
			getOreTiers(rawSettings.at("Ore_Tiers"));
			setPltPopRand1Rng(u::splitValToRng(rawSettings.at("Planet_Pop_Rand1_Rng"),"Int"));
			setPltPopRand2Rng(u::splitValToRng(rawSettings.at("Planet_Pop_Rand2_Rng"), "Int"));
			setPltPopRand3Rng(u::splitValToRng(rawSettings.at("Planet_Pop_Rand3_Rng"), "Int"));
			setPltDefRandRng(u::splitValToRng(rawSettings.at("Planet_Def_Rnd_Rng"), "Int"));
			setPltShdRandRng(u::splitValToRng(rawSettings.at("Planet_Shd_Rnd_Rng"), "Int"));
			setPltSzRandRng(u::splitValToRng(rawSettings.at("Planet_Size_Rnd_Rng"), "Int"));
			setPltEksRandRng(u::splitValToRng(rawSettings.at("Planet_EKS_Rnd_Rng"), "Int"));
			setUnvStrtSysAmt(rawSettings.at("Unv_Starting_Systems"));
			setMxABelts(rawSettings.at("Max_Asteroid_Belts"));
			setABeltMxRoids(u::splitValToRng(rawSettings.at("Asteroids_Rng"), "Int"));
			setABeltSzRnd(u::splitValToRng(rawSettings.at("ABelt_Size_Rnd_Rng"), "Int"));
			setRdSzRandRng(u::splitValToRng(rawSettings.at("Asteroid_Size_Rnd_Rng"), "Int"));
			setRdSmRng(u::splitValToRng(rawSettings.at("Asteroid_Small_Rng"), "Int"));
			setRdMdRng(u::splitValToRng(rawSettings.at("Asteroid_Medium_Rng"), "Int"));
			setRdLgRng(u::splitValToRng(rawSettings.at("Asteroid_Large_Rng"), "Int"));
			setRdHgRng(u::splitValToRng(rawSettings.at("Asteroid_Huge_Rng"), "Int"));
			setUnvExpRate(rawSettings.at("Unv_Exp_Rate"));
			setHighSecRng(u::splitValToRng(rawSettings.at("Sec_Rating_High_Rng"), "Int"));
			setMidSecRng(u::splitValToRng(rawSettings.at("Sec_Rating_Mid_Rng"), "Int"));
			setLowSecRng(u::splitValToRng(rawSettings.at("Sec_Rating_Low_Rng"), "Int"));
			setNullSecRng(u::splitValToRng(rawSettings.at("Sec_Rating_Null_Rng"), "Int"));
			setOreStgRndRng(u::splitValToRng(rawSettings.at("Ore_Stage_Rnd_Rng"), "Int"));
			setOreTrRndRng(u::splitValToRng(rawSettings.at("Ore_Tier_Rnd_Rng"), "Float"));
			setMnClsRng(u::splitValToRng(rawSettings.at("Moon_CLS_Rng"), "Int"));
			setDpoSmSzRng(u::splitValToRng(rawSettings.at("Deposit_Small_Size_Rng"), "Int"));
			setDpoMdSzRng(u::splitValToRng(rawSettings.at("Deposit_Med_Size_Rng"), "Int"));
			setDpoLgSzRng(u::splitValToRng(rawSettings.at("Deposit_Lrg_Size_Rng"), "Int"));
			setDpoHgSzRng(u::splitValToRng(rawSettings.at("Deposit_Huge_Size_Rng"), "Int"));
			setMnClsRndRng(u::splitValToRng(rawSettings.at("Moon_CLS_Rnd_Rng"), "Int"));
			setMnAmtRndRng(u::splitValToRng(rawSettings.at("Moon_Amt_Rnd_Rng"), "Int"));
		}
		catch (std::out_of_range& const e) {
			exit(EXIT_FAILURE);
		}
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

	void loadOreTypeSettings() {
		//Prepare oreTierSettings if not ready
		if (gOreTierSettings.size() < 1) {
			for (string tier : oreTiers) {
				gOreTierSettings.push_back(oreTierSettings(tier));
			}
		}

		//Now get the settings for each tier
		for (oreTierSettings& tierSetting : gOreTierSettings) {
			for (auto mapEl : rawSettings) {
				string tmpStr = mapEl.first;

				if (tmpStr.find(tierSetting.getTier()) != string::npos) {
					tierSetting = processOreTierSettings(tierSetting, mapEl.first, mapEl.second);
				}
			}
		}
	}

	//Process a single plt type's settings which are now stored in keys and vals vectors
	pltTypeSettings processPltSettings(pltTypeSettings plts, string key, string val) {
		if (key.find("EKS_Rng") != string::npos) { plts.setPltEksRng(u::splitValToRng(val,"Float")); }
		else if (key.find("Size_Rng") != string::npos) { plts.setPltSzRng(u::splitValToRng(val,"Int")); }
		else if (key.find("Outlier_Rng") != string::npos) { plts.setPltOutlrRng(u::splitValToRng(val,"Float")); }
		else if (key.find("Size_Rnd_Rng") != string::npos) { plts.setPltSzRndRng(u::splitValToRng(val,"Float")); }
		else if (key.find("Def_Max") != string::npos) { plts.addPltDefRng(stof(val)); }
		else if (key.find("Shd_Max") != string::npos) { plts.addPltShdRng(stof(val)); }
		else if (key.find("Moon_CLS_Rng") != string::npos) { plts.setPltMnCls(u::splitValToRng(val, "Int")); }
		else if (key.find("Moon_CLS_Vect") != string::npos) { plts.setPltMnClsVect(u::splitValToInt(val)); }
		else if (key.find("Moon_Num_Vect") != string::npos) { plts.setPltMnAmtVect(u::splitValToInt(val)); }

		return plts;
	}

	//Process a single plt type's settings which are now stored in keys and vals vectors
	roidStageSettings processRoidSettings(roidStageSettings roid, string key, string val) {
		if (key.find("Multi_Rnd_Rng") != string::npos) { roid.setRoidOStgMulRnd(u::splitValToRng(val,"Float")); }
		else if (key.find("Size_Multi") != string::npos) { roid.setRoidStgMulti(stoi(val)); }
		else if (key.find("Small_Rng") != string::npos) { roid.setRoidSmRng(u::splitValToRng(val,"Int")); }
		else if (key.find("Medium_Rng") != string::npos) { roid.setRoidMdRng(u::splitValToRng(val,"Int")); }
		else if (key.find("Large_Rng") != string::npos) { roid.setRoidLgRng(u::splitValToRng(val, "Int")); }
		else if (key.find("Huge_Rng") != string::npos) { roid.setRoidHgRng(u::splitValToRng(val, "Int")); }

		return roid;
	}

	oreTierSettings processOreTierSettings(oreTierSettings tier, string key, string val) {
		if (key.find("High_Sec_Rng") != string::npos) { tier.setHighRng(u::splitValToRng(val, "Int")); }
		else if (key.find("Mid_Sec_Rng") != string::npos) { tier.setMidRng(u::splitValToRng(val, "Int")); }
		else if (key.find("Low_Sec_Rng") != string::npos) { tier.setLowRng(u::splitValToRng(val, "Int")); }
		else if (key.find("Null_Sec_Rng") != string::npos) { tier.setNullRng(u::splitValToRng(val, "Int")); }

		return tier;
	}

	void setLogLevel(string val) { logLvl = stoi(val); }
	void setPlyCXPBVal(string val) { plyCXPBVal = stoi(val); }
	void getPltTyps(string val) { pltTypes = u::splitValToStr(val); }
	void getDifficulties(string val) { gameDiffs = u::splitValToStr(val); }
	void getOreStages(string val) { oreStages = u::splitValToStr(val); }
	void getOreTiers(string val) { oreTiers = u::splitValToStr(val); }
	void setDifficulty(string val) { sGameDifficulty = val; }
	void setPlyShdDmgMlt(string val) { shdDmgMultPly = stof(val); }
	void setPlyArmDmgMlt(string val) { armDmgMultPly = stof(val); }
	void setPlyHulDmgMlt(string val) { hulDmgMultPly = stof(val); }
	void setNPShdDmgMlt(string val) { shdDmgMultNP = stof(val); }
	void setNPArmDmgMlt(string val) { armDmgMultNP = stof(val); }
	void setNPHulDmgMlt(string val) { hulDmgMultNP = stof(val); }
	void setScpYld(string val) { scpYldRt = stof(val); }
	void setMisTypes(string val) { missClsTypes = u::splitValToStr(val); }
	void setLSSpnRt(string val) { lSecSpawnRt = stof(val); }
	void setMSSpnRt(string val) { mSecSpawnRt = stof(val); }
	void setHSSpnRt(string val) { hSecSpawnRt = stof(val); }
	void setNSSpnRt(string val) { nSecSpawnRt = stof(val); }
	void setPlyCXPFac(string val) { plyCXPFactor = stof(val); }
	void setNPCXPFac(string val) { npCXPFactor = stof(val); }
	void setMxPlts(string val) { maxPlanets = stoi(val); }
	void setPltPopRand1Rng(Range rng) { pltPopRand1 = rng; }
	void setPltPopRand2Rng(Range rng) { pltPopRand2 = rng; }
	void setPltPopRand3Rng(Range rng) { pltPopRand3 = rng; }
	void setPltDefRandRng(Range rng) { pltDefRand = rng; }
	void setPltShdRandRng(Range rng) { pltShdRand = rng; }
	void setPltSzRandRng(Range rng) { pltSizeRand = rng; }
	void setPltEksRandRng(Range rng) { pltEksRand = rng; }
	void setUnvStrtSysAmt(string val) { unvStartSystems = stoi(val); }
	void setMxABelts(string val) { maxAsteroidBelts = stoi(val); }
	void setABeltMxRoids(Range rng) { abltMaxAsteroids = rng; }
	void setABeltSzRnd(Range rng) { abltSizeRandRng = rng; }
	void setRdSzRandRng(Range rng) { roidSizeRandRng = rng; }
	void setRdSmRng(Range rng) { roidSmallRng = rng; }
	void setRdMdRng(Range rng) { roidMedRng = rng; }
	void setRdLgRng(Range rng) { roidLargeRng = rng; }
	void setRdHgRng(Range rng) { roidHugeRng = rng; }
	void setHighSecRng(Range rng) { secRtHighRng = rng; }
	void setMidSecRng(Range rng) { secRtMidRng = rng; }
	void setLowSecRng(Range rng) { secRtLowRng = rng; }
	void setNullSecRng(Range rng) { secRtNullRng = rng; }
	void setSMap(map<string, string> settingMap) {
		rawSettings = settingMap;
		loadSettings();
	}

	void setUnvExpRate(string val) { unvExpRate = stoi(val); }
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
		else if (key.find("P_Weapon_Shd_Dmg_Mod") != string::npos) { dSPWpnShdDmgMulti = val; }
		else if (key.find("P_Weapon_Arm_Dmg_Mod") != string::npos) { dSPWpnArmDmgMulti = val; }
		else if (key.find("P_Weapon_Hull_Dmg_Mod") != string::npos) { dSPWpnHulDmgMulti = val; }
		else if (key.find("N_Weapon_Shd_Dmg_Mod") != string::npos) { dSNWpnShdDmgMulti = val; }
		else if (key.find("N_Weapon_Arm_Dmg_Mod") != string::npos) { dSNWpnArmDmgMulti = val; }
		else if (key.find("N_Weapon_Hull_Dmg_Mod") != string::npos) { dSNWpnHulDmgMulti = val; }
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
	void pltTypeSettings::setPltEksRng(Range rng) { plEksRng = rng; }
	Range pltTypeSettings::getPltEksRng() { return plEksRng; }
	void pltTypeSettings::setPltSzRng(Range rng) { plSizeRng = rng; }
	Range pltTypeSettings::getPltSzRng() { return plSizeRng; }
	void pltTypeSettings::setPltOutlrRng(Range rng) { plOutlierRng = rng; }
	Range pltTypeSettings::getPltOutlrRng() { return plOutlierRng; }
	void pltTypeSettings::setPltSzRndRng(Range rng) { plSizeRndRng = rng; }
	Range pltTypeSettings::getPltSzRndRng() { return plSizeRndRng; }
	int pltTypeSettings::getPltMnClsSz() { return pltMoonClsVect.size(); }
	int pltTypeSettings::getPltMnAmtSz() { return pltMoonAmtVect.size(); }
	int pltTypeSettings::getPltMnCls(int pos) { return pltMoonClsVect.at(pos); }
	int pltTypeSettings::getPltMnAmt(int pos) { return pltMoonAmtVect.at(pos); }
	Range pltTypeSettings::getPltMnClsRng() { return pltMoonCLS; }
	void pltTypeSettings::setPltMnCls(Range rng) { pltMoonCLS = rng; }
	void pltTypeSettings::setPltMnClsVect(vector<int> vect) { pltMoonClsVect = vect; }
	void pltTypeSettings::setPltMnAmtVect(vector<int> vect) { pltMoonAmtVect = vect; }
	void pltTypeSettings::addPltDefRng(float maxVal) {
		plDefRngs.push_back(Range());
		plDefRngs.back().fHigh = maxVal; //Set fHigh for new Range element
	}
	
	void pltTypeSettings::addPltShdRng(float maxVal){
		plShdRngs.push_back(Range());
		plShdRngs.back().fHigh = maxVal; //Set fHigh for new Range element
	}

	float pltTypeSettings::getPltDefRng(int pos) { return plDefRngs.at(pos).fHigh; }
	float pltTypeSettings::getPltShdRng(int pos) { return plShdRngs.at(pos).fHigh; }
	int pltTypeSettings::getPltDefRngSz() { return plDefRngs.size(); }
	int pltTypeSettings::getPltShdRngSz() { return plShdRngs.size(); }


	//roidStageSettings Functions
	roidStageSettings::roidStageSettings(string stage) {
		roidStage = "Stage" + stage; 
		roidStageI = stoi(stage);
	}

	void roidStageSettings::setRoidOStgMulRnd(Range rng) { roidOStgMulRnd = rng; }
	void roidStageSettings::setRoidSmRng(Range rng) { roidSmallRng = rng; }
	void roidStageSettings::setRoidMdRng(Range rng) { roidMedRng = rng; }
	void roidStageSettings::setRoidLgRng(Range rng) { roidLargeRng = rng; }
	void roidStageSettings::setRoidHgRng(Range rng) { roidHugeRng = rng; }
	string roidStageSettings::getStage() { return roidStage; }
	int roidStageSettings::getStageI() { return roidStageI; }
	void roidStageSettings::setRoidStgMulti(float val) { roidStgMulti = val; }
	Range roidStageSettings::getRoidOStgMulRnd() { return roidOStgMulRnd; }
	float roidStageSettings::getRoidStgMulti() { return roidStgMulti; }
	Range roidStageSettings::getRoidSmRng() { return roidSmallRng; }
	Range roidStageSettings::getRoidMdRng() { return roidMedRng; }
	Range roidStageSettings::getRoidLgRng() { return roidLargeRng; }
	Range roidStageSettings::getRoidHgRng() { return roidHugeRng; }


	//oreTierSettings Functions
	oreTierSettings::oreTierSettings(string tier) {
		tierName = "Tier" + tier;
		tierVal = stoi(tier);
	}

	void oreTierSettings::setHighRng(Range rng) { tierHighRng = rng; }
	void oreTierSettings::setMidRng(Range rng) { tierMidRng = rng; }
	void oreTierSettings::setLowRng(Range rng) { tierLowRng = rng; }
	void oreTierSettings::setNullRng(Range rng) { tierNullRng = rng; }
	string oreTierSettings::getTier() { return tierName; }
	int oreTierSettings::getTierVal() { return tierVal; }
	Range oreTierSettings::getHighRng() { return tierHighRng; }
	Range oreTierSettings::getMidRng() { return tierMidRng; }
	Range oreTierSettings::getLowRng() { return tierLowRng; }
	Range oreTierSettings::getNullRng() { return tierNullRng; }


	//moonClsSettings Functions
	moonClsSettings::moonClsSettings(string cls){
		mnCls = "CLS " + cls;
		mnClsInt = stoi(cls);
	}

	void moonClsSettings::setMnDpSmSpnRng(Range rng) { mnDepoSmSpnRng = rng; }
	void moonClsSettings::setMnDpMdSpnRng(Range rng) { mnDepoMdSpnRng = rng; }
	void moonClsSettings::setMnDpLgSpnRng(Range rng) { mnDepoLgSpnRng = rng; }
	void moonClsSettings::setMnDpHgSpnRng(Range rng) { mnDepoHgSpnRng = rng; }
	string moonClsSettings::getMnCls() { return mnCls; }
	int moonClsSettings::getMnClsInt() { return mnClsInt; }
	Range moonClsSettings::getMnDpSmSpnRng() { return mnDepoSmSpnRng; }
	Range moonClsSettings::getMnDpMdSpnRng() { return mnDepoMdSpnRng; }
	Range moonClsSettings::getMnDpLgSpnRng() { return mnDepoLgSpnRng; }
	Range moonClsSettings::getMnDpHgSpnRng() { return mnDepoHgSpnRng; }


	//New Functions
	void setOreStgRndRng(Range rng) { oreStgRnd = rng; }
	void setOreTrRndRng(Range rng) { oreTrRnd = rng; }
	void setMnClsRng(Range rng) { mnCls = rng; }	
	void setDpoSmSzRng(Range rng) { dpoSmSz = rng; }
	void setDpoMdSzRng(Range rng) { dpoMdSz = rng; }
	void setDpoLgSzRng(Range rng) { dpoLgSz = rng; }
	void setDpoHgSzRng(Range rng) { dpoHgSz = rng; }
	void setMnClsRndRng(Range rng) { mnClsRnd = rng; }
	void setMnAmtRndRng(Range rng) { mnAmtRnd = rng; }
	
	void loadMnClsSettings() {
		//Prepare pltTypSettings if not already
		if (gMnClsSettings.size() < 1) {
			for (i1 = 1; i1 <= mnCls.iHigh; i1++) {
				gMnClsSettings.push_back(moonClsSettings(to_string(i1)));
			}
		}

		//Diff based settings - Do these after non-diff settings are loaded
		for (moonClsSettings& mcsSetting : gMnClsSettings) {
			for (auto mapEl : rawSettings) {
				string tmpStr = mapEl.first;

				if (tmpStr.find(mcsSetting.getMnCls()) != string::npos) {
					mcsSetting = processMnClsSettings(mcsSetting, mapEl.first, mapEl.second);
				}
			}
		}
	}

	moonClsSettings processMnClsSettings(moonClsSettings mcs, string key, string val) {
		if (key.find("Small_Depos_Rnd") != string::npos) { mcs.setMnDpSmSpnRng(u::splitValToRng(val,"Int")); }
		else if (key.find("Med_Depos_Rnd") != string::npos) { mcs.setMnDpMdSpnRng(u::splitValToRng(val, "Int")); }
		else if (key.find("Lrg_Depos_Rnd") != string::npos) { mcs.setMnDpLgSpnRng(u::splitValToRng(val, "Int")); }
		else if (key.find("Huge_Depos_Rnd") != string::npos) { mcs.setMnDpHgSpnRng(u::splitValToRng(val, "Int")); }
	}

	//New Members
	

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
	vector<string> oreTiers; //Types of ore tiers
	
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
	Range roidSizeRandRng; //Sets the min and max range for asteroid size calculation
	Range roidSmallRng; //Random vals which correspond to a small asteroid
	Range roidMedRng; //Random vals which correspond to a medium asteroid
	Range roidLargeRng; //Random vals which correspond to a large asteroid
	Range roidHugeRng; //Random vals which correspond to a huge asteroid
	Range secRtHighRng; //High security rating range
	Range secRtMidRng; //Mid security rating range
	Range secRtLowRng; //Low security rating range
	Range secRtNullRng; //Null security rating range
	Range oreStgRnd; //Ore stage random range
	Range oreTrRnd; //Ore tier random range
	Range mnCls; //Min/Max moon class
	Range dpoSmSz; //Small deposit size range
	Range dpoMdSz; //Medium deposit size range
	Range dpoLgSz; //Large deposit size range
	Range dpoHgSz; //Huge deposit size range
	Range mnClsRnd; //Moon class random range
	Range mnAmtRnd; //Num of moons range range

	//Reference Settings
	vector<diffSettings> gDiffSettings; //Stores all of the data related to specific game difficulties
	vector<pltTypeSettings> gPltTypSettings; //Stores all of the data related to specific planet types
	vector<roidStageSettings> gRoidStgSettings; //Stores all of the data related to specific ore/asteroid stages
	vector<oreTierSettings> gOreTierSettings; //Stores all of the data related to specific ore tiers
	vector<moonClsSettings> gMnClsSettings; //Stores all of the data related to specific moon classes
							
	//Misc
	map<string, string> rawSettings, rawSettingsTemp;
	int i1;
	map<string, string>::iterator itr;
	vector<string> keys, vals;	
}
