#include "dataSystem.h"
#include "util.h"

namespace u = Util;

dataSystem::dataSystem() {}

//These are interface functions to allow external classes to call private functions for building queries.
void dataSystem::prepQuery(string table, string stmtOperation, int id, vector<string> whereConds) {
	sqlTable = table;
	
	buildStmt(table, stmtOperation, id, whereConds);
	queryData(table);
}

void dataSystem::prepQueryRng(string table, string stmtOperation, Range ids, vector<string> whereConds) {
	sqlTable = table;

	buildStmt(table, stmtOperation, ids, whereConds);
	queryData(table);
}

void dataSystem::prepQueryVec(string table, string stmtOperation, vector<int> ids, vector<string> whereConds) {
	sqlTable = table;
	
	buildStmt(table, stmtOperation, ids, whereConds);
	queryData(table);
}

//Query buidlers; in future will need to expand these out or create a new override which can use other fields which can be specified from in game for sorting or something similar, more specific searches (such as based on max resource cost or ship type reqs)
void dataSystem::buildStmt(string table, string operation, int id, vector<string> whereConds) {
	string sID = to_string(id);

	if (operation == "select from" && id > 0) {
		sqlStr = "Select * From " + table + " Where ID = " + sID;
		rows = 1;
	} else if (operation == "select from" && id == 0) {
		sqlStr = "Select * From " + table;
		rows = -1; //-1 is an ad-hoc flag to pull the count of the table later on
	} else if (operation == "select from where" && id == 0 && whereConds.size() > 0) {
		//Type = 'Ore', Stage = '1'
		whereCondStr = " Where ";

		for (i1 = 0; i1 < whereConds.size(); i1++) {
			if (i1 == whereConds.size() - 1) { whereCondStr += whereConds.at(i1); }
			else { whereCondStr += whereConds.at(i1) + " and "; }
		}

		sqlStr = "Select * From " + table + whereCondStr;

		rows = -1;
	}

	sqlStmt = sqlStr.c_str();
}

void dataSystem::buildStmt(string table, string operation, Range ids, vector<string> whereConds) {
	string lID = to_string(ids.iLow);
	string hID = to_string(ids.iHigh);

	if (operation == "select from") {
		sqlStr = "Select * From " + table + " Where ID >= " + lID + " and ID <= " + hID;

		rows = ids.iHigh - ids.iLow + 1; //Get number of IDs in the range to be returned + 1 offset; considerations to be made when we move on to filtering lists though
	}

	sqlStmt = sqlStr.c_str();
}

void dataSystem::buildStmt(string table, string operation, vector<int> ids, vector<string> whereConds) {
	whereCondStr = " Where ID IN (";

	//Build where condition list
	for (i1 = 0; i1 < ids.size(); i1++) {
		string sID = to_string(ids.at(i1));
		
		if (i1 == ids.size() - 1) { whereCondStr += sID + ")"; }
		else { whereCondStr += sID + ","; }
	}

	if (operation == "select from") {
		sqlStr = "Select * From " + table + whereCondStr;

		rows = ids.size(); //Same as for build from range, filtering will cause some issues with the logic as is; TODO: think about handling for scenario where not all ids passed to funtions are present in the database
	}

	sqlStmt = sqlStr.c_str();
}

//This function will call query functions to get data from the database
void dataSystem::queryData(string table) {
	if (table == "APlating") { rtnAPlates(); }
	else if (table == "Capacitors") { rtnCaps(); }
	else if (table == "Clones") { rtnClones(); }
	else if (table == "Cpus") { rtnCPUs(); }
	else if (table == "Dispositions") { rtnDisps(); }
	/*else if (table == "Effects") { rtnEffects(); }*/
	else if (table == "Engines") { rtnEngs(); }
	else if (table == "Equipment") { rtnEquips(); }
	else if (table == "Hulls") { rtnHulls(); }
	else if (table == "Messages") { rtnMsgs(); }
	else if (table == "Missions") { rtnMissions(); }
	else if (table == "MissRewards") { rtnMRewards(); }
	else if (table == "Names") { rtnNames(); }
	else if (table == "NPCShips") { rtnNPCShps(); }
	else if (table == "ODPlatforms") { rtnODPs(); }
	else if (table == "PShields") { rtnPShds(); }
	else if (table == "PWRSystems") { rtnPSystems(); }
	else if (table == "Races") { rtnRaces(); }
	else if (table == "Ram") { rtnRam(); }
	else if (table == "Ranks") { rtnRanks(); }
	else if (table == "Reprocessing") { rtnReproc(); }
	else if (table == "Resources") { rtnRescs(); }
	else if (table == "Settings") { rtnSet(); }
	else if (table == "ShipClasses") { rtnShpClasses(); }
	else if (table == "Ships") { rtnShps(); }
	else if (table == "Skills") { rtnSkills(); }
	else if (table == "SMatrices") { rtnSMtxs(); }
	else if (table == "SysNames") { rtnSysNames(); }
	else if (table == "Weapons"){ rtnWpns(); }
	else if (table == "WFGens") { rtnWFGens(); }
	else if (table == "WTSystems") { rtnWTSystems(); }
}

bool dataSystem::openDB() {
	openDBFile("ovDB.sqlite");

	return bDidDBOpen;
}

bool dataSystem::openSave() {
	openDBFile("ovSave.sqlite");

	return bDidDBOpen;
}

void dataSystem::openDBFile(const char* dbFile) {
	int rst = sqlite3_open_v2(dbFile, &dBase, SQLITE_OPEN_READWRITE,0);
	if (rst != SQLITE_OK) {
		u::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err003", "Could not open " + string(dbFile) + ": " + sqlite3_errmsg(dBase), "./OV_Log.txt");
		
		bDidDBOpen = false;
	} else {
		bDidDBOpen = true;
	}
}

void dataSystem::rtnAPlates() {
	clearVec("rsltAPlts");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltAPlts.push_back(strcAPlating());
		}

		for (strcAPlating &sAPlate : rsltAPlts) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sAPlate = getAPlateData(stmt, sAPlate);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnCaps(){
	clearVec("rsltCaps");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltCaps.push_back(strcCap());
		}

		for (strcCap &sCap : rsltCaps) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sCap = getCapData(stmt, sCap);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnClones(){
	clearVec("rsltClones");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltClones.push_back(strcClone());
		}

		for (strcClone &sClone : rsltClones) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sClone = getCloneData(stmt, sClone);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnCPUs(){
	clearVec("rsltCpus");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltCpus.push_back(strcCpu());
		}

		for (strcCpu &sCpu : rsltCpus) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sCpu = getCPUData(stmt, sCpu);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnDisps(){
	clearVec("rsltDisps");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltDisps.push_back(strcDisp());
		}

		for (strcDisp &sDisp : rsltDisps) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sDisp = getDispData(stmt, sDisp);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnEngs(){
	clearVec("rsltEngs");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltEngs.push_back(strcEng());
		}

		for (strcEng &sEng : rsltEngs) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sEng = getEngData(stmt, sEng);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnEquips() {
	clearVec("rsltEquips");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltEquips.push_back(strcEquipment());
		}

		for (strcEquipment &sEquip : rsltEquips) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sEquip = getEquipData(stmt, sEquip);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnHulls(){
	clearVec("rsltHulls");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltHulls.push_back(strcHull());
		}

		for (strcHull &sHull : rsltHulls) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sHull = getHullData(stmt, sHull);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnMsgs(){
	clearVec("rsltMsgs");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltMsgs.push_back(strcMsg());
		}

		for (strcMsg &sMsg : rsltMsgs) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sMsg = getMsgData(stmt, sMsg);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnMissions(){
	clearVec("rsltMissions");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {		
		for (i1 = 0; i1 < rows; i1++) {
			rsltMissions.push_back(strcMission());
		}

		for (strcMission &sMiss : rsltMissions) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sMiss = getMissionData(stmt, sMiss);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnMRewards(){
	clearVec("rsltMRwrds");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltMRwrds.push_back(strcMReward());
		}

		for (strcMReward &sMRwd : rsltMRwrds) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sMRwd = getMRewardData(stmt, sMRwd);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnNames(){
	clearVec("rsltNames");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltNames.push_back(strcName());
		}

		for (strcName &sName : rsltNames) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sName = getNameData(stmt, sName);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnNPCShps(){
	clearVec("rsltNPCShps");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltNPCShps.push_back(strcNPCShp());
		}

		for (strcNPCShp &sNPCShp : rsltNPCShps) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sNPCShp = getNPCShpData(stmt, sNPCShp);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnODPs(){
	clearVec("rsltODPs");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltODPs.push_back(strcODP());
		}

		for (strcODP &sODP : rsltODPs) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sODP = getODPData(stmt, sODP);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnPShds(){
	clearVec("rsltPShds");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltPShds.push_back(strcPShd());
		}

		for (strcPShd &sPShd : rsltPShds) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sPShd = getPShdData(stmt, sPShd);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnPSystems(){
	clearVec("rsltPSystems");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {		
		for (i1 = 0; i1 < rows; i1++) {
			rsltPSystems.push_back(strcPSys());
		}

		for (strcPSys &sPSys : rsltPSystems) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sPSys = getPSysData(stmt, sPSys);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnRaces(){
	clearVec("rsltRaces");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltRaces.push_back(strcRace());
		}

		for (strcRace &sRace : rsltRaces) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sRace = getRaceData(stmt, sRace);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnRam(){
	clearVec("rsltRam");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltRam.push_back(strcRam());
		}

		for (strcRam &sRam : rsltRam) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sRam = getRamData(stmt, sRam);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnRanks(){
	clearVec("rsltRanks");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltRanks.push_back(strcRank());
		}

		for (strcRank &sRank : rsltRanks) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sRank = getRankData(stmt, sRank);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnReproc(){
	clearVec("rsltRpc");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltRpc.push_back(strcReproc());
		}

		for (strcReproc &sRpc : rsltRpc) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) {
				cols = getRtnCols(sqlTable, __LINE__);

				if (!bNoCols) {
					sRpc = getReprocData(stmt, sRpc);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnRescs(){
	clearVec("rsltRescs");	
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltRescs.push_back(strcResc());
		}

		for (strcResc &sResc : rsltRescs) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sResc = getRescData(stmt, sResc);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnShpClasses(){
	clearVec("rsltShpClss");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltShpClss.push_back(strcShpCls());
		}

		for (strcShpCls &sShpCls : rsltShpClss) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sShpCls = getShpClsData(stmt, sShpCls);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnShps() {
	clearVec("rsltShps");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltShps.push_back(strcShip());
		}

		for (strcShip &sShip : rsltShps) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sShip = getShpData(stmt, sShip);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnSkills(){
	clearVec("rsltSkills");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltSkills.push_back(strcSkill());
		}

		for (strcSkill &sSkill : rsltSkills) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sSkill = getSkillData(stmt, sSkill);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnSklTraining(){
	clearVec("rsltSkTrangs");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltSkTrangs.push_back(strcSklTraining());
		}

		for (strcSklTraining &sSkTrning : rsltSkTrangs) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sSkTrning = getSklTrainingData(stmt, sSkTrning);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnSMtxs(){
	clearVec("rsltSMtxs");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltSMtxs.push_back(strcSMtx());
		}

		for (strcSMtx &sSMtx : rsltSMtxs) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sSMtx = getSMtxData(stmt, sSMtx);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnSysNames(){
	clearVec("rsltSNames");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltSNames.push_back(strcSysName());
		}

		for (strcSysName &sSysNm : rsltSNames) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sSysNm = getSysNameData(stmt, sSysNm);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnWpns() {
	clearVec("rsltWeps");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltWeps.push_back(strcWeapon());
		}

		for (strcWeapon &sWeap : rsltWeps) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sWeap = getWpnData(stmt, sWeap);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnWFGens(){
	clearVec("rsltWFGens");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltWFGens.push_back(strcWFGen());
		}

		for (strcWFGen &sWfg : rsltWFGens) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sWfg = getWFGenData(stmt, sWfg);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnWTSystems(){
	clearVec("rsltWTSystems");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltWTSystems.push_back(strcWTSys());
		}

		for (strcWTSys &sWts : rsltWTSystems) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					sWts = getWTSysData(stmt, sWts);
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

void dataSystem::rtnSet() {
	clearVec("rsltSets");
	stmt = prepStmt(sqlTable, __LINE__);

	if (!bStmtErr) {
		for (i1 = 0; i1 < rows; i1++) {
			rsltSets.push_back(strcSetting());
		}

		for (strcSetting &sSet : rsltSets) {
			procStep(sqlTable, __LINE__);

			if (!bStepErr) { 
				cols = getRtnCols(sqlTable, __LINE__); 

				if (!bNoCols) { 
					for (i1 = 0; i1 <= cols; i1++) { 
						switch (i1) { 
						case 1:
							sSet.sKey = getStrCol(stmt,i1,__LINE__); //Save data into the vector element
							break;

						case 2:
							sSet.sVal = getStrCol(stmt, i1, __LINE__); //Save data into the vector element
							break;

						default:
							u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + i1, "./OV_Log.txt");
							break;
						}
					}
				}
			}
		}
	}

	finalize(stmt, __LINE__);
}

sqlite3_stmt* dataSystem::prepStmt(string table, int line) {
	bStmtErr = false;
	//Check if the statement can be created

	int rslt = sqlite3_prepare_v2(dBase, sqlStmt, sqlStr.size(), &stmt, 0);

	if (rslt != SQLITE_OK){
		bStmtErr = true;
		u::createBInfo("Err", __FILE__, to_string(line), __DATE__, __TIME__, "Err002", "Query on " + table + " could not be prepared: " + sqlite3_errmsg(dBase), "./OV_Log.txt");
	}

	if (!bStmtErr) {
		if (rows == -1) {
			rows = getRtnRows(sqlTable, __LINE__);
		}
	}

	return stmt;
}

sqlite3_stmt* dataSystem::prepStmt2(string table, int line) {
	bStmtErr = false;
	//Check if the statement can be created
	if (sqlite3_prepare_v2(dBase, sqlStmt2, sqlStr2.size(), &stmt2, 0) == SQLITE_OK) { return stmt2; }
	else {
		bStmtErr = true;
		u::createBInfo("Err", __FILE__, to_string(line), __DATE__, __TIME__, "Err002", "Query on " + table + " could not be prepared: " + sqlite3_errmsg(dBase), "./OV_Log.txt");

		return stmt2;
	}
}

void dataSystem::procStep(string table, int line) {
	bStepErr = false;
	int rslt = sqlite3_step(stmt);
	
	if (rslt != SQLITE_ROW && rslt != SQLITE_DONE && rslt != SQLITE_OK) {
		bStepErr = true;

		u::createBInfo("Err", __FILE__, to_string(line), __DATE__, __TIME__, "Err001", "Query on " + table + " failed: " + sqlite3_errmsg(dBase), "./OV_Log.txt");
	}
}

void dataSystem::procStep2(string table, int line) {
	bStepErr = false;
	int rslt = sqlite3_step(stmt2);

	if (rslt != SQLITE_ROW && rslt != SQLITE_DONE && rslt != SQLITE_OK) {
		bStepErr = true;

		u::createBInfo("Err", __FILE__, to_string(line), __DATE__, __TIME__, "Err001", "Query on " + table + " failed: " + sqlite3_errmsg(dBase), "./OV_Log.txt");
	}
}

int dataSystem::getRtnCols(string table, int line) {
	bNoCols = false;

	int c = sqlite3_column_count(stmt);

	if (c == 0) {
		bNoCols = true;
		u::createBInfo("Warn", __FILE__, to_string(line), __DATE__, __TIME__, "Warn001", "No columns queried from " + table, "./OV_Log.txt");

		return c;
	} else { return c; }
}

strcAPlating dataSystem::getAPlateData(sqlite3_stmt * stm, strcAPlating apData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			apData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			apData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			apData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			apData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			apData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 5:
			apData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			apData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			apData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			apData.drb = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			apData.pwrcons = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			apData.reprate = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			apData.rdly = sqlite3_column_int(stm, i1);
			break;

		case 12:
			apData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 13:
			apData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			apData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			apData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			apData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			apData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 18:
			apData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 19:
			apData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 20:
			apData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return apData;
}

strcCap dataSystem::getCapData(sqlite3_stmt * stm, strcCap capData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			capData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			capData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			capData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			capData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 4:
			capData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 5:
			capData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			capData.capt = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			capData.rchgrate = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			capData.rchgamt = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			capData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			capData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 11:
			capData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 12:
			capData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			capData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			capData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			capData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			capData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			capData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return capData;
}

strcClone dataSystem::getCloneData(sqlite3_stmt * stm, strcClone clnData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			clnData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			clnData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			clnData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			clnData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			clnData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 5:
			clnData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			clnData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 7:
			clnData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 8:
			clnData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 9:
			clnData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 10:
			clnData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 11:
			clnData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 12:
			clnData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			clnData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return clnData;
}

strcCpu dataSystem::getCPUData(sqlite3_stmt * stm, strcCpu cpuData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			cpuData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			cpuData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			cpuData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			cpuData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			cpuData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 5:
			cpuData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			cpuData.capt = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			cpuData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			cpuData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 9:
			cpuData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 10:
			cpuData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 11:
			cpuData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 12:
			cpuData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			cpuData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			cpuData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			cpuData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return cpuData;
}

strcDisp dataSystem::getDispData(sqlite3_stmt * stm, strcDisp dispData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			dispData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			dispData.disp = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			dispData.relval = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return dispData;
}

strcEng dataSystem::getEngData(sqlite3_stmt * stm, strcEng engData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			engData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			engData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			engData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			engData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			engData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 5:
			engData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			engData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			engData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			engData.maxspd = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			engData.acclrate = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			engData.navadjrate = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			engData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 12:
			engData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			engData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			engData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			engData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			engData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			engData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 18:
			engData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 19:
			engData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return engData;
}

strcEquipment dataSystem::getEquipData(sqlite3_stmt* stm, strcEquipment eqpData) {
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			eqpData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			eqpData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			eqpData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			eqpData.type = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			eqpData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 5:
			eqpData.subcls = getStrCol(stm, i1, __LINE__);
			break;

		case 6:
			eqpData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 7:
			eqpData.mindmg = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			eqpData.maxdmg = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			eqpData.maxdist = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			eqpData.targtime = sqlite3_column_int(stm, i1);
			break;

		case 11:
			eqpData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 12:
			eqpData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 13:
			eqpData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 14:
			eqpData.rchgrate = (float)sqlite3_column_double(stm, i1);
			break;

		case 15:
			eqpData.pwrcons = (float)sqlite3_column_double(stm, i1);
			break;

		case 16:
			eqpData.initpwrcon = (float)sqlite3_column_double(stm, i1);
			break;

		case 17:
			eqpData.dlytime = (float)sqlite3_column_double(stm, i1);
			break;

		case 18:
			eqpData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 19:
			eqpData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 20:
			eqpData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 21:
			eqpData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 22:
			eqpData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 23:
			eqpData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 24:
			eqpData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 25:
			eqpData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 26:
			eqpData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return eqpData;
}

strcHull dataSystem::getHullData(sqlite3_stmt * stm, strcHull hullData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			hullData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			hullData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			hullData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			hullData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			hullData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 5:
			hullData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			hullData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			hullData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			hullData.reprate = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			hullData.pwrcons = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			hullData.repamt = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			hullData.repdly = sqlite3_column_int(stm, i1);
			break;
		
		case 12:
			hullData.drb = (float)sqlite3_column_double(stm, i1);
			break;

		case 13:
			hullData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 14:
			hullData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			hullData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			hullData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			hullData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 18:
			hullData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 19:
			hullData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 20:
			hullData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 21:
			hullData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return hullData;
}

strcMsg dataSystem::getMsgData(sqlite3_stmt * stm, strcMsg msgData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			msgData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			msgData.msg = getStrCol(stm, i1, __LINE__);
			break;
		
		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return msgData;
}

strcMission dataSystem::getMissionData(sqlite3_stmt * stm, strcMission missData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			missData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			missData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			missData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			missData.reqcel = sqlite3_column_int(stm, i1);
			break;

		case 4:
			missData.tlim = sqlite3_column_int(stm, i1);
			break;

		case 5:
			missData.diff = getStrCol(stm, i1, __LINE__);
			break;

		case 6:
			missData.sec = getStrCol(stm, i1, __LINE__);
			break;

		case 7:
			missData.sec = getStrCol(stm, i1, __LINE__);
			break;

		case 8:
			missData.targnm = getStrCol(stm, i1, __LINE__);
			break;

		case 9:
			missData.targshpcls = getStrCol(stm, i1, __LINE__);
			break;

		case 10:
			missData.type = getStrCol(stm, i1, __LINE__);
			break;		

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return missData;
}

strcMReward dataSystem::getMRewardData(sqlite3_stmt * stm, strcMReward mrwdData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			mrwdData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			mrwdData.rwdtyp = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			mrwdData.rwdamt = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return mrwdData;
}

strcName dataSystem::getNameData(sqlite3_stmt * stm, strcName nmData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
			case 1:
				nmData.name = getStrCol(stm, i1, __LINE__);
				break;

			case 2:
				nmData.nmtyp = getStrCol(stm, i1, __LINE__);
				break;

			case 3:
				nmData.applraces = getStrCol(stm, i1, __LINE__);
				break;

			default:
				u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
				break;
		}
	}

	return nmData;
}

strcNPCShp dataSystem::getNPCShpData(sqlite3_stmt * stm, strcNPCShp npcshpData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			npcshpData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			npcshpData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			npcshpData.shpcls = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			npcshpData.minlvrng = sqlite3_column_int(stm, i1);
			break;

		case 4:
			npcshpData.maxlvrng = sqlite3_column_int(stm, i1);
			break;

		case 5:
			npcshpData.basecxp = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return npcshpData;
}

strcODP dataSystem::getODPData(sqlite3_stmt * stm, strcODP odpData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			odpData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			odpData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			odpData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			odpData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			odpData.subcls = getStrCol(stm, i1, __LINE__);
			break;

		case 5:
			odpData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 6:
			odpData.cpu = sqlite3_column_int(stm, i1);
			break;
		
		case 7:
			odpData.ram = sqlite3_column_int(stm, i1);
			break;
		
		case 8:
			odpData.psys = sqlite3_column_int(stm, i1);
			break;

		case 9:
			odpData.cap = sqlite3_column_int(stm, i1);
			break;

		case 10:
			odpData.smtx = sqlite3_column_int(stm, i1);
			break;

		case 11:
			odpData.aplt = sqlite3_column_int(stm, i1);
			break;

		case 12:
			odpData.hull = sqlite3_column_int(stm, i1);
			break;

		case 13:
			odpData.wtsys = sqlite3_column_int(stm, i1);
			break;

		case 14:
			odpData.tslots = sqlite3_column_int(stm, i1);
			break;

		case 15:
			odpData.lslots = sqlite3_column_int(stm, i1);
			break;

		case 16:
			odpData.mslots = sqlite3_column_int(stm, i1);
			break;

		case 17:
			odpData.hslots = sqlite3_column_int(stm, i1);
			break;

		case 18:
			odpData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 19:
			odpData.cargo = (float)sqlite3_column_double(stm, i1);
			break;

		case 20:
			odpData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 21:
			odpData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 22:
			odpData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 23:
			odpData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 24:
			odpData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 25:
			odpData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 26:
			odpData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 27:
			odpData.nwcost = sqlite3_column_int(stm, i1);
			break;

		case 28:
			odpData.cxp = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return odpData;
}

strcPShd dataSystem::getPShdData(sqlite3_stmt * stm, strcPShd pshdData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			pshdData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			pshdData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			pshdData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			pshdData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 4:
			pshdData.psys = sqlite3_column_int(stm, i1);
			break;

		case 5:
			pshdData.cpu = sqlite3_column_int(stm, i1);
			break;

		case 6:
			pshdData.ram = sqlite3_column_int(stm, i1);
			break;

		case 7:
			pshdData.smtx = sqlite3_column_int(stm, i1);
			break;

		case 8:
			pshdData.tslots = sqlite3_column_int(stm, i1);
			break;

		case 9:
			pshdData.lslots = sqlite3_column_int(stm, i1);
			break;

		case 10:
			pshdData.mslots = sqlite3_column_int(stm, i1);
			break;

		case 11:
			pshdData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 12:
			pshdData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			pshdData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			pshdData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			pshdData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			pshdData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			pshdData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 18:
			pshdData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 19:
			pshdData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return pshdData;
}

strcPSys dataSystem::getPSysData(sqlite3_stmt * stm, strcPSys psysData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			psysData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			psysData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			psysData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			psysData.typ = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			psysData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 5:
			psysData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			psysData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			psysData.capt = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			psysData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			psysData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 10:
			psysData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 11:
			psysData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 12:
			psysData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			psysData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			psysData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			psysData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			psysData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return psysData;
}

strcRace dataSystem::getRaceData(sqlite3_stmt * stm, strcRace rceData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 1:
			rceData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			rceData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			rceData.emp = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			rceData.cap = getStrCol(stm, i1, __LINE__);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return rceData;
}

strcRam dataSystem::getRamData(sqlite3_stmt * stm, strcRam ramData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			ramData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			ramData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			ramData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			ramData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 4:
			ramData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 5:
			ramData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			ramData.capt = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			ramData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			ramData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 9:
			ramData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 10:
			ramData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 11:
			ramData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 12:
			ramData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			ramData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			ramData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			ramData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return ramData;
}

strcRank dataSystem::getRankData(sqlite3_stmt * stm, strcRank rnkData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 1:
			rnkData.name = getStrCol(stm, i1, __LINE__);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return rnkData;
}

strcReproc dataSystem::getReprocData(sqlite3_stmt * stm, strcReproc rpcData){
	for (i1 = 0; i1 <= cols; i1++) {
		switch (i1) {
		case 0:
			rpcData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			rpcData.oid = sqlite3_column_int(stm, i1);
			break;

		case 2:
			rpcData.rid = sqlite3_column_int(stm, i1);
			break;

		case 3:
			rpcData.repunits= (float)sqlite3_column_double(stm, i1);
			break;

		case 4:
			rpcData.resprod = (float)sqlite3_column_double(stm, i1);
			break;

		case 5:
			rpcData.rescost = sqlite3_column_int(stm, i1);
			break;

		case 6: 
			rpcData.resprodloss = (float)sqlite3_column_double(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return rpcData;
}

strcResc dataSystem::getRescData(sqlite3_stmt * stm, strcResc rscData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			rscData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			rscData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			rscData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			rscData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 4:
			rscData.typ = getStrCol(stm, i1, __LINE__);
			break;

		case 5:
			rscData.stg = sqlite3_column_int(stm, i1);
			break;

		case 6: rscData.tier = sqlite3_column_int(stm, i1);
			break;

		case 7:
			rscData.bsize = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			rscData.xcost = sqlite3_column_int(stm, i1);
			break;
		
		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return rscData;
}

strcShpCls dataSystem::getShpClsData(sqlite3_stmt * stm, strcShpCls shpclsData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			shpclsData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			shpclsData.name = getStrCol(stm, i1, __LINE__);
			break;
		
		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return shpclsData;
}

strcShip dataSystem::getShpData(sqlite3_stmt* stm, strcShip shpData) {
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			shpData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			shpData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			shpData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			shpData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			shpData.subcls = getStrCol(stm, i1, __LINE__);
			break;

		case 5:
			shpData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 6:
			shpData.cpu = sqlite3_column_int(stm, i1);
			break;

		case 7:
			shpData.ram = sqlite3_column_int(stm, i1);
			break;

		case 8:
			shpData.psys = sqlite3_column_int(stm, i1);
			break;

		case 9:
			shpData.cap = sqlite3_column_int(stm, i1);
			break;

		case 10:
			shpData.eng = sqlite3_column_int(stm, i1);
			break;

		case 11:
			shpData.wfgen = sqlite3_column_int(stm, i1);
			break;

		case 12:
			shpData.smtx = sqlite3_column_int(stm, i1);
			break;

		case 13:
			shpData.aplt = sqlite3_column_int(stm, i1);
			break;

		case 14:
			shpData.hull = sqlite3_column_int(stm, i1);
			break;

		case 15:
			shpData.wtsys = sqlite3_column_int(stm, i1);
			break;

		case 16:
			shpData.tslots = sqlite3_column_int(stm, i1);
			break;

		case 17:
			shpData.lslots = sqlite3_column_int(stm, i1);
			break;

		case 18:
			shpData.mslots = sqlite3_column_int(stm, i1);
			break;

		case 19:
			shpData.hslots = sqlite3_column_int(stm, i1);
			break;

		case 20:
			shpData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 21:
			shpData.crg = (float)sqlite3_column_double(stm, i1);
			break;

		case 22:
			shpData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 23:
			shpData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 24:
			shpData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 25:
			shpData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 26:
			shpData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 27:
			shpData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 28:
			shpData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 29:
			shpData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return shpData;
}

strcSkill dataSystem::getSkillData(sqlite3_stmt * stm, strcSkill sklData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			sklData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			sklData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			sklData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			sklData.typ = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			sklData.sgrp = getStrCol(stm, i1, __LINE__);
			break;

		case 5:
			sklData.ttm = sqlite3_column_int(stm, i1);
			break;

		case 6:
			sklData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			sklData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 8:
			sklData.cxpcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return sklData;
}

strcSklTraining dataSystem::getSklTrainingData(sqlite3_stmt * stm, strcSklTraining skltrnData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			skltrnData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			skltrnData.skid = sqlite3_column_int(stm, i1);
			break;

		case 2:
			skltrnData.rk1TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 3:
			skltrnData.rk2TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 4:
			skltrnData.rk3TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 5:
			skltrnData.rk4TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			skltrnData.rk5TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			skltrnData.rk6TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			skltrnData.rk7TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			skltrnData.rk8TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			skltrnData.rk9TMod = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			skltrnData.rk10TMod = (float)sqlite3_column_double(stm, i1);
			break;		

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return skltrnData;
}

strcSMtx dataSystem::getSMtxData(sqlite3_stmt * stm, strcSMtx smtxData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			smtxData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			smtxData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			smtxData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			smtxData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 4:
			smtxData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 5:
			smtxData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			smtxData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			smtxData.rchgrate = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			smtxData.pwrcons = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			smtxData.rchgamt = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			smtxData.rchgdly = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			smtxData.capt = (float)sqlite3_column_double(stm, i1);
			break;

		case 12:
			smtxData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 13:
			smtxData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			smtxData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			smtxData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			smtxData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			smtxData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 18:
			smtxData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 19:
			smtxData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 20:
			smtxData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return smtxData;
}

strcSysName dataSystem::getSysNameData(sqlite3_stmt * stm, strcSysName sysnmData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			sysnmData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			sysnmData.name = getStrCol(stm, i1, __LINE__);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return sysnmData;
}

strcWeapon dataSystem::getWpnData(sqlite3_stmt* stm, strcWeapon wpnData) {
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			wpnData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			wpnData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			wpnData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			wpnData.cls = getStrCol(stm, i1, __LINE__);
			break;

		case 4:
			wpnData.subcls = getStrCol(stm, i1, __LINE__);
			break;

		case 5:
			wpnData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 6:
			wpnData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			wpnData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			wpnData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			wpnData.mindmg = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			wpnData.maxdmg = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			wpnData.ammocap = sqlite3_column_int(stm, i1);
			break;

		case 12:
			wpnData.ammocons = sqlite3_column_int(stm, i1);
			break;

		case 13:
			wpnData.dmgintlow = (float)sqlite3_column_double(stm, i1);
			break;

		case 14:
			wpnData.dmginthi = (float)sqlite3_column_double(stm, i1);
			break;

		case 15:
			wpnData.mineffrng = (float)sqlite3_column_double(stm, i1);
			break;

		case 16:
			wpnData.minopteffrng = (float)sqlite3_column_double(stm, i1);
			break;

		case 17:
			wpnData.maxopteffrng = (float)sqlite3_column_double(stm, i1);
			break;

		case 18:
			wpnData.maxeffrng = (float)sqlite3_column_double(stm, i1);
			break;

		case 19:
			wpnData.atkspd = (float)sqlite3_column_double(stm, i1);
			break;

		case 20:
			wpnData.pwrcons = (float)sqlite3_column_double(stm, i1);
			break;

		case 21:
			wpnData.initpwrcon = (float)sqlite3_column_double(stm, i1);
			break;

		case 22:
			wpnData.mcdur = (float)sqlite3_column_double(stm, i1);
			break;

		case 23:
			wpnData.mcyld = (float)sqlite3_column_double(stm, i1);
			break;

		case 24:
			wpnData.mass = (float)sqlite3_column_double(stm, i1);
			break;

		case 25:
			wpnData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 26:
			wpnData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 27:
			wpnData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 28:
			wpnData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 29:
			wpnData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 30:
			wpnData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 31:
			wpnData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 32:
			wpnData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 33:
			wpnData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return wpnData;
}

strcWFGen dataSystem::getWFGenData(sqlite3_stmt * stm, strcWFGen wfgData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			wfgData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			wfgData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			wfgData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			wfgData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 4:
			wfgData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 5:
			wfgData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 6:
			wfgData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			wfgData.pwrcons = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			wfgData.wrpstblrate = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			wfgData.maxspd = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			wfgData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			wfgData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 12:
			wfgData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			wfgData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			wfgData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			wfgData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			wfgData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			wfgData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 18:
			wfgData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return wfgData;
}

strcWTSys dataSystem::getWTSysData(sqlite3_stmt * stm, strcWTSys wtsData){
	for (i1 = 0; i1 <= cols; i1++) { 
		switch (i1) { 
		case 0:
			wtsData.id = sqlite3_column_int(stm, i1);
			break;

		case 1:
			wtsData.name = getStrCol(stm, i1, __LINE__);
			break;

		case 2:
			wtsData.desc = getStrCol(stm, i1, __LINE__);
			break;

		case 3:
			wtsData.tlvl = sqlite3_column_int(stm, i1);
			break;

		case 4:
			wtsData.maxtrg = sqlite3_column_int(stm, i1);
			break;

		case 5:
			wtsData.trgrate = sqlite3_column_int(stm, i1);
			break;

		case 6:
			wtsData.pwrreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 7:
			wtsData.cpureq = (float)sqlite3_column_double(stm, i1);
			break;

		case 8:
			wtsData.ramreq = (float)sqlite3_column_double(stm, i1);
			break;

		case 9:
			wtsData.maxscnrng = (float)sqlite3_column_double(stm, i1);
			break;

		case 10:
			wtsData.sg2 = (float)sqlite3_column_double(stm, i1);
			break;

		case 11:
			wtsData.xcost = sqlite3_column_int(stm, i1);
			break;

		case 12:
			wtsData.rcost = sqlite3_column_int(stm, i1);
			break;

		case 13:
			wtsData.dicost = sqlite3_column_int(stm, i1);
			break;

		case 14:
			wtsData.dcost = sqlite3_column_int(stm, i1);
			break;

		case 15:
			wtsData.lcost = sqlite3_column_int(stm, i1);
			break;

		case 16:
			wtsData.ucost = sqlite3_column_int(stm, i1);
			break;

		case 17:
			wtsData.pcost = sqlite3_column_int(stm, i1);
			break;

		case 18:
			wtsData.nwcost = sqlite3_column_int(stm, i1);
			break;

		default:
			u::createBInfo("Warn", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Warn002", "Unexpected case value " + to_string(i1), "./OV_Log.txt");
			break;
		}
	}

	return wtsData;
}

string dataSystem::getStrCol(sqlite3_stmt* s, int colNum, int line) {
	data = (char*)sqlite3_column_text(s, colNum); //Store returned data temporarily for null checking for string returns
	checkValidity(data, sqlTable, line);

	if (!bStrNull) { return data; }
	else { return "na"; }
}

void dataSystem::checkValidity(const char* data, string table, int line) {
	if (data != NULL) { bStrNull = false; }
	else {
		u::createBInfo("Err", __FILE__, to_string(line), __DATE__, __TIME__, "Err002", "Null string queried from " + table, "./OV_Log.txt");

		bStrNull = true;
	}
}

int dataSystem::getRtnRows(string table, int line) {
	if (whereCondStr.length() != 0){ sqlStr2 = "Select Count(*) from " + table + whereCondStr; }
	else{ sqlStr2 = "Select Count(*) from " + table; }
	
	sqlStmt2 = sqlStr2.c_str();

	stmt2 = prepStmt2(sqlTable, __LINE__);

	if (!bStmtErr) {
		procStep2(sqlTable, __LINE__);
		if (!bStepErr) {
			int nRows = sqlite3_column_int(stmt2, 0);

			finalize(stmt2, __LINE__);

			return nRows;
		}
	} else { return 0; }
}

void dataSystem::clearVec(string vecName){
	if (vecName == "rsltAPlts") { rsltAPlts.clear(); }
	else if (vecName == "rsltCaps") { rsltCaps.clear(); }
	else if (vecName == "rsltClones") { rsltClones.clear(); }
	else if (vecName == "rsltCpus") { rsltCpus.clear(); }
	else if (vecName == "rsltDisps") { rsltDisps.clear(); }
	else if (vecName == "rsltEngs") { rsltEngs.clear(); }
	else if (vecName == "rsltEquips") { rsltEquips.clear(); }
	else if (vecName == "rsltHulls") { rsltHulls.clear(); }
	else if (vecName == "rsltMsgs") { rsltMsgs.clear(); }
	else if (vecName == "rsltMissions") { rsltMissions.clear(); }
	else if (vecName == "rsltMRwrds") { rsltMRwrds.clear(); }
	else if (vecName == "rsltNames") { rsltNames.clear(); }
	else if (vecName == "rsltNPCShps") { rsltNPCShps.clear(); }
	else if (vecName == "rsltODPs") { rsltODPs.clear(); }
	else if (vecName == "rsltPShds") { rsltPShds.clear(); }
	else if (vecName == "rsltPSystems") { rsltPSystems.clear(); }
	else if (vecName == "rsltRaces") { rsltRaces.clear(); }
	else if (vecName == "rsltRam") { rsltRam.clear(); }
	else if (vecName == "rsltRanks") { rsltRanks.clear(); }
	else if (vecName == "rsltRescs") { rsltRescs.clear(); }
	else if (vecName == "rsltShpClss") { rsltShpClss.clear(); }
	else if (vecName == "rsltShps") { rsltShps.clear(); }
	else if (vecName == "rsltSkills") { rsltSkills.clear(); }
	else if (vecName == "rsltSkTrangs") { rsltSkTrangs.clear(); }
	else if (vecName == "rsltSMtxs") { rsltSMtxs.clear(); }
	else if (vecName == "rsltSNames") { rsltSNames.clear(); }
	else if (vecName == "rsltWFGens") { rsltWFGens.clear(); }
	else if (vecName == "rsltWTSystems") { rsltWTSystems.clear(); }
	else if (vecName == "rsltSets") { rsltSets.clear(); }
}

void dataSystem::finalize(sqlite3_stmt* stmt, int line) {
	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		string sqlErr = sqlite3_errmsg(dBase);
		u::createBInfo("Err", __FILE__, to_string(line), __DATE__, __TIME__, "Err005", "Unable to finalize statement: "  + sqlErr, "./OV_Log.txt");
	}
}

void dataSystem::closeDB() {
	if (sqlite3_close(dBase) != SQLITE_OK) {
		string sqlErr = sqlite3_errmsg(dBase);
		u::createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err006", "Unable to close database: " + sqlErr, "./OV_Log.txt");
	}
}

strcAPlating dataSystem::getAPlate() { return rsltAPlts.at(0); }
vector<strcAPlating> dataSystem::getAPlates() { return rsltAPlts; }
strcCap dataSystem::getCap() { return rsltCaps.at(0); }
vector<strcCap> dataSystem::getCaps() { return rsltCaps; }
strcClone dataSystem::getClone() { return rsltClones.at(0); }
vector<strcClone> dataSystem::getClones() { return rsltClones; }
strcCpu dataSystem::getCPU() { return rsltCpus.at(0); }
vector<strcCpu> dataSystem::getCPUs() { return rsltCpus; }
strcDisp dataSystem::getDisp() { return rsltDisps.at(0); }
vector<strcDisp> dataSystem::getDisps() { return rsltDisps; }
strcEng dataSystem::getEng() { return rsltEngs.at(0); }
vector<strcEng> dataSystem::getEngs() { return rsltEngs; }
strcEquipment dataSystem::getEquip() { return rsltEquips.at(0); }
vector<strcEquipment> dataSystem::getEquips() { return rsltEquips; }
strcHull dataSystem::getHull() { return rsltHulls.at(0); }
vector<strcHull> dataSystem::getHulls() { return rsltHulls; }
strcMsg dataSystem::getMsg() { return rsltMsgs.at(0); }
vector<strcMsg> dataSystem::getMsgs() { return rsltMsgs; }
strcMission dataSystem::getMission() { return rsltMissions.at(0); }
vector<strcMission> dataSystem::getMissions() { return rsltMissions; }
strcMReward dataSystem::getMReward() { return rsltMRwrds.at(0); }
vector<strcMReward> dataSystem::getMRewards() { return rsltMRwrds; }
strcName dataSystem::getName() { return rsltNames.at(0); }
vector<strcName> dataSystem::getNames() { return rsltNames; }
strcNPCShp dataSystem::getNPCShp() { return rsltNPCShps.at(0); }
vector<strcNPCShp> dataSystem::getNPCShps() { return rsltNPCShps; }
strcODP dataSystem::getODP() { return rsltODPs.at(0); }
vector<strcODP> dataSystem::getODPs() { return rsltODPs; }
strcPShd dataSystem::getPShd() { return rsltPShds.at(0); }
vector<strcPShd> dataSystem::getPShds() { return rsltPShds; }
strcPSys dataSystem::getPSys() { return rsltPSystems.at(0); }
vector<strcPSys> dataSystem::getPSyss() { return rsltPSystems; }
strcRace dataSystem::getRace() { return rsltRaces.at(0); }
vector<strcRace> dataSystem::getRaces() { return rsltRaces; }
strcRam dataSystem::getRam() { return rsltRam.at(0); }
vector<strcRam> dataSystem::getRams() { return rsltRam; }
strcRank dataSystem::getRank() { return rsltRanks.at(0); }
strcReproc dataSystem::getReproc()
{
	return strcReproc();
}
vector<strcRank> dataSystem::getRanks() { return rsltRanks; }
vector<strcReproc> dataSystem::getReprocs()
{
	return vector<strcReproc>();
}
strcResc dataSystem::getResc() { return rsltRescs.at(0); }
vector<strcResc> dataSystem::getRescs() { return rsltRescs; }
strcShpCls dataSystem::getShpCls() { return rsltShpClss.at(0); }
vector<strcShpCls> dataSystem::getShpClss() { return rsltShpClss; }
strcShip dataSystem::getShp() { return rsltShps.at(0); }
vector<strcShip> dataSystem::getShps() { return rsltShps; }
strcSkill dataSystem::getSkill() { return rsltSkills.at(0); }
vector<strcSkill> dataSystem::getSkills() { return rsltSkills; }
strcSklTraining dataSystem::getSklTraining() { return rsltSkTrangs.at(0); }
vector<strcSklTraining> dataSystem::getSklTrainings() { return rsltSkTrangs; }
strcSMtx dataSystem::getSMtx() { return rsltSMtxs.at(0); }
vector<strcSMtx> dataSystem::getSMtxs() { return rsltSMtxs; }
strcSysName dataSystem::getSysName() { return rsltSNames.at(0); }
vector<strcSysName> dataSystem::getSysNames() { return rsltSNames; }
strcWeapon dataSystem::getWpn() { return rsltWeps.at(0); }
vector<strcWeapon> dataSystem::getWpns() { return rsltWeps; }
strcWFGen dataSystem::getWFGen() { return rsltWFGens.at(0); }
vector<strcWFGen> dataSystem::getWFGens() { return rsltWFGens; }
strcWTSys dataSystem::getWTSys() { return rsltWTSystems.at(0); }
vector<strcWTSys> dataSystem::getWTSyss() { return rsltWTSystems; }

map<string, string> dataSystem::getSettings() {
	for (strcSetting set : rsltSets) {
		rtnSettings.insert(std::make_pair(set.sKey, set.sVal));
	}

	return rtnSettings;
}