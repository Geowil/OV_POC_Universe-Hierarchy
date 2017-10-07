#ifndef DATASYSTEM__H
#define DATASYSTEM__H

#include <string>
#include <vector>
#include <map>
#include "dataStructs.h"
#include "range.h"
#include "SQLite/sqlite3.h"

using std::string;
using std::vector;
using std::map;
using std::initializer_list;

class dataSystem {
public:
	dataSystem();

	//"RData"-like functions, deliniated for different id types
	void prepQuery(string table, string stmtOperation, int id, vector<string> whereConds); //Get specific item data or all item data from table
	void prepQueryRng(string table, string stmtOperation, Range ids, vector<string> whereConds); //Get range of item data from table
	void prepQueryVec(string table, string stmtOperation, vector<int> ids, vector<string> whereConds); //Get multiple specific item data from table
	bool openDB();
	bool openSave();

	//create function for querying based on conditions with unknown ids such as cpus with x power requirement which are for destroyers

	strcAPlating getAPlate();
	strcCap getCap();
	strcClone getClone();
	strcCpu getCPU();
	strcDisp getDisp();
	strcEng getEng();
	strcEquipment getEquip();
	strcHull getHull();
	strcMsg getMsg();
	strcMission getMission();
	strcMReward getMReward();
	strcName getName();
	strcNPCShp getNPCShp();
	strcODP getODP();
	strcPSys getPSys();
	strcPShd getPShd();
	strcRace getRace();
	strcRam getRam();
	strcRank getRank();
	strcReproc getReproc();
	strcResc getResc();
	strcShpCls getShpCls();
	strcShip getShp();
	strcSkill getSkill();
	strcSklTraining getSklTraining();
	strcSMtx getSMtx();
	strcSysName getSysName();
	strcWeapon getWpn();
	strcWFGen getWFGen();
	strcWTSys getWTSys();

	vector<strcAPlating> getAPlates();
	vector<strcCap> getCaps();
	vector<strcClone> getClones();
	vector<strcCpu> getCPUs();
	vector<strcDisp> getDisps();
	vector<strcEng> getEngs();
	vector<strcEquipment> getEquips();
	vector<strcHull> getHulls();
	vector<strcMsg> getMsgs();
	vector<strcMission> getMissions();
	vector<strcMReward> getMRewards();
	vector<strcName> getNames();
	vector<strcNPCShp> getNPCShps();
	vector<strcODP> getODPs();
	vector<strcPSys> getPSyss();
	vector<strcPShd> getPShds();
	vector<strcRace> getRaces();
	vector<strcRam> getRams();
	vector<strcRank> getRanks();
	vector<strcReproc> getReprocs();
	vector<strcResc> getRescs();
	vector<strcShpCls> getShpClss();
	vector<strcShip> getShps();
	vector<strcSkill> getSkills();
	vector<strcSklTraining> getSklTrainings();
	vector<strcSMtx> getSMtxs();
	vector<strcSysName> getSysNames();
	vector<strcWeapon> getWpns();
	vector<strcWFGen> getWFGens();
	vector<strcWTSys> getWTSyss();

	map<string, string> getSettings();



private:

	//Build query stmt - private, only this class should be able to call these
	void buildStmt(string table, string operation, int id, vector<string> whereConds);
	void buildStmt(string table, string operation, Range ids, vector<string> whereConds);
	void buildStmt(string table, string operation, vector<int> ids, vector<string> whereConds);

	void queryData(string table); //Function which will actually call query functions

	void openDBFile(const char* dbFile);

	//Query Functions	
	void rtnAPlates();	
	void rtnCaps();	
	void rtnClones();	
	void rtnCPUs();	
	void rtnDisps();	
	void rtnEngs();
	void rtnEquips();	
	void rtnHulls();	
	void rtnMsgs();	
	void rtnMissions();	
	void rtnMRewards();	
	void rtnNames();	
	void rtnNPCShps();	
	void rtnODPs();	
	void rtnPShds();	
	void rtnPSystems();	
	void rtnRaces();	
	void rtnRam();	
	void rtnRanks();
	void rtnReproc();
	void rtnRescs();	
	void rtnShpClasses();
	void rtnShps();	
	void rtnSkills();	
	void rtnSklTraining();	
	void rtnSMtxs();	
	void rtnSysNames();
	void rtnWpns();	
	void rtnWFGens();	
	void rtnWTSystems();
	void rtnSet();

	sqlite3_stmt* prepStmt(string table, int line);
	sqlite3_stmt* prepStmt2(string table, int line);
	void procStep(string table, int line);
	void procStep2(string table, int line);
	int getRtnCols(string table, int line);
	int getRtnRows(string table, int line);
	void clearVec(string vecName);

	strcAPlating getAPlateData(sqlite3_stmt* stm, strcAPlating apData);
	strcCap getCapData(sqlite3_stmt* stm, strcCap capData);
	strcClone getCloneData(sqlite3_stmt* stm, strcClone clnData);
	strcCpu getCPUData(sqlite3_stmt* stm, strcCpu cpuData);
	strcDisp getDispData(sqlite3_stmt* stm, strcDisp dispData);
	strcEng getEngData(sqlite3_stmt* stm, strcEng engData);
	strcEquipment getEquipData(sqlite3_stmt* stm, strcEquipment eqpData);
	strcHull getHullData(sqlite3_stmt* stm, strcHull hullData);
	strcMsg getMsgData(sqlite3_stmt* stm, strcMsg msgData);
	strcMission getMissionData(sqlite3_stmt* stm, strcMission missData);
	strcMReward getMRewardData(sqlite3_stmt* stm, strcMReward mrwdData);
	strcName getNameData(sqlite3_stmt* stm, strcName nmData);
	strcNPCShp getNPCShpData(sqlite3_stmt* stm, strcNPCShp npcshpData);
	strcODP getODPData(sqlite3_stmt* stm, strcODP odpData);
	strcPShd getPShdData(sqlite3_stmt* stm, strcPShd pshdData);
	strcPSys getPSysData(sqlite3_stmt* stm, strcPSys psysData);
	strcRace getRaceData(sqlite3_stmt* stm, strcRace rceData);
	strcRam getRamData(sqlite3_stmt* stm, strcRam ramData);
	strcRank getRankData(sqlite3_stmt* stm, strcRank rnkData);
	strcReproc getReprocData(sqlite3_stmt* stm, strcReproc rpcData);
	strcResc getRescData(sqlite3_stmt* stm, strcResc rscData);
	strcShpCls getShpClsData(sqlite3_stmt* stm, strcShpCls shpclsData);
	strcShip getShpData(sqlite3_stmt* stm, strcShip shpData);
	strcSkill getSkillData(sqlite3_stmt* stm, strcSkill sklData);
	strcSklTraining getSklTrainingData(sqlite3_stmt* stm, strcSklTraining skltrnData);
	strcSMtx getSMtxData(sqlite3_stmt* stm, strcSMtx smtxData);
	strcSysName getSysNameData(sqlite3_stmt* stm, strcSysName sysnmData);
	strcWeapon getWpnData(sqlite3_stmt* stm, strcWeapon wpnData);
	strcWFGen getWFGenData(sqlite3_stmt* stm, strcWFGen wfgData);
	strcWTSys getWTSysData(sqlite3_stmt* stm, strcWTSys wtsData);
	
	string getStrCol(sqlite3_stmt* s, int colNum, int line);
	void checkValidity(const char* data, string table, int line);
	void finalize(sqlite3_stmt* stmt, int line);
	void closeDB();

	sqlite3 *dBase;
	sqlite3_stmt* sStmt;
	sqlite3_stmt* sStmt2;
	sqlite3_stmt* stmt;
	sqlite3_stmt* stmt2;

	string sqlStr,sqlStr2; //Store built stmt before it is cast to char*
	const char* sqlStmt; //Store cast stmt for prepare call
	const char* sqlStmt2;
	string whereCondStr; //Store where conditions for certain query stmt builders
	
	//Utility vars
	int result,cols, i1, i2,rows;
	const char* data;
	bool bStmtErr,bStepErr,bNoCols,bStrNull,bDidDBOpen; //Bools used to determine if there were any errors during a specific step of the query process
	string sqlTable; //For logging

	//Resutls vectors
	vector<strcAPlating> rsltAPlts;
	vector<strcCap> rsltCaps;
	vector<strcClone> rsltClones;
	vector<strcCpu> rsltCpus;
	vector<strcDisp> rsltDisps;
	vector<strcEng> rsltEngs;
	vector<strcEquipment> rsltEquips;	
	vector<strcHull> rsltHulls;
	vector<strcMsg> rsltMsgs;
	vector<strcMission> rsltMissions;
	vector<strcMReward> rsltMRwrds;
	vector<strcName> rsltNames;
	vector<strcNPCShp> rsltNPCShps;
	vector<strcODP> rsltODPs;
	vector<strcPShd> rsltPShds;
	vector<strcPSys> rsltPSystems;
	vector<strcRace> rsltRaces;
	vector<strcRam> rsltRam;
	vector<strcRank> rsltRanks;
	vector<strcReproc> rsltRpc;
	vector<strcResc> rsltRescs;
	vector<strcShpCls> rsltShpClss;
	vector<strcShip> rsltShps;	
	vector<strcSkill> rsltSkills;
	vector<strcSklTraining> rsltSkTrangs;
	vector<strcSMtx> rsltSMtxs;
	vector<strcSysName> rsltSNames;
	vector<strcWeapon> rsltWeps;	
	vector<strcWFGen> rsltWFGens;
	vector<strcWTSys> rsltWTSystems;
	vector<strcSetting> rsltSets;

	//Results maps
	map<string, string> rtnSettings;
};
#endif