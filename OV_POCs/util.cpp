#include "util.h"
#include <stdexcept>
#include <algorithm>
#include <math.h>
#include "logging.h"
#include "settings.h"

//namespace setting = Settings;

namespace Util {
	Logging l_u;
	std::random_device rd;
	std::mt19937 gen(rd());

	map<string, float>::iterator itf1;
	map<string, int>::iterator iti1;
	map<string, float>rtnFMap;
	map<string, int>rtnIMap;

	vector<string> blankCond; //Use when no conditions needed for queries

	int i1;

	//For Debug
	string file, bLocale, bTDate;


	//Name: fillMap
	//Description: Fill a map reference passed through with the contents of another map from dataSystem
	/*Arguments:
	*argMap1 - This map contains a map of settings loaded passed in from another function
	*/
	map<string, float> fillMap(map<string, float>argMap1) {
		for (itf1 = argMap1.begin(); itf1 != argMap1.end(); itf1++) {
			rtnFMap.insert(pair<string, float>(itf1->first, itf1->second));
		}

		return rtnFMap;
	}

	//Name: fillMap
	//Description: Fill a map reference passed through with the contents of another map from dataSystem; int value override
	/*Arguments:
	*argMap1 - This map contains a map of settings loaded passed in from another function
	*/
	map<string, int> fillMap(map<string, int>argMap1) {
		for (iti1 = argMap1.begin(); iti1 != argMap1.end(); iti1++) {
			rtnIMap.insert(pair<string, int>(iti1->first, iti1->second));
		}

		return rtnIMap;
	}


	void createBInfo(string errType, string fl, string lnNm, string dt, string tm, string errCode, string errMsg, string fPath) {
		file = fl;
		bLocale = "File: " + file + "  Line: " + lnNm;
		bTDate = dt + "  " + tm;

		l_u.createLReport(errType, errCode, errMsg, bLocale, bTDate, fPath);
	}

	//Move this to player/ai classes when added
	int calcXP(int base, int level, float factor) {
		return trunc(base * (pow(level, factor)));
	}

	int getIRand(int low, int high) { return std::uniform_int_distribution<>{low, high}(gen); }
	float getFRand(float low, float high) { return std::uniform_real_distribution<float> {low, high}(gen); }

	bool validateInpInt(int val, int min, int max) {
		if (val < min || val > max) { return false; }
		else { return true; }
	}

	bool validateInpStr(string val, vector<string> possExpStr) {
		for (string sVal : possExpStr) {
			if (val == sVal) { return true; }
		}

		return false;
	}

	int updateVal(string op, int newval, int curval) {
		if (op == "set") { return newval; }
		else if (op == "add") { return newval + curval; }
		else if (op == "sub") { return curval - newval; }
	}

	float updateVal(string op, float newval, float curval) {
		if (op == "set") { return newval; }
		else if (op == "add") { return newval + curval; }
		else if (op == "sub") { return curval - newval; }
	}

	long long int updateVal(string op, long long int newval, long long int curval) {
		if (op == "set") { return newval; }
		else if (op == "add") { return newval + curval; }
		else if (op == "sub") { return curval - newval; }
	}

	vector<string> splitValToStr(string val) {
		return splitVal(val);
	}

	vector<float> splitValToFlt(string val) {
		vector<string> tempStr;
		vector<float> tempFlt;

		tempStr = splitVal(val);

		for (string val : tempStr) {
			tempFlt.push_back(stof(val));
		}

		return tempFlt;
	}

	vector<int> splitValToInt(string val) {
		vector<string> tempStr;
		vector<int> tempInt;

		tempStr = splitVal(val);

		for (string val : tempStr) {
			tempInt.push_back(stoi(val));
		}

		return tempInt;
	}

	Range splitValToRng(string val, string typ) {
		vector<string>tempStr;
		Range tempRng;

		tempStr = splitVal(val);

		//Do this here once instead of each time below
		if (tempStr.size() != 2) {
			createBInfo("Err", __FILE__, to_string(__LINE__), __DATE__, __TIME__, "Err004", "String passed to splitValToRng does not have two values", "./OV_Log.txt");
		}
		
		if (typ == "Int") {
			if (tempStr.size() == 2) {
				tempRng.iLow = stoi(tempStr.at(0));
				tempRng.iHigh = stoi(tempStr.at(1));
			}
			else {
				tempRng.iLow = 0;
				tempRng.iHigh = 0;
			}
		}
		else if (typ == "Float") {
			if (tempStr.size() == 2) {
				tempRng.fLow = stof(tempStr.at(0));
				tempRng.fHigh = stof(tempStr.at(1));
			}
			else {
				tempRng.fLow = 0.0f;
				tempRng.fHigh = 0.0f;
			}
		}
		else if (typ == "Double") {
			if (tempStr.size() == 2) {
				tempRng.dLow = stod(tempStr.at(0));
				tempRng.dHigh = stod(tempStr.at(1));
			}
			else {
				tempRng.dLow = 0.0;
				tempRng.dHigh = 0.0;
			}
		}

		return tempRng;		
	}

	namespace {
		vector<string> splitVal(string val) {
			vector<string> temp;
			curPos = val.find(',');
			prvPos = 0;

			while (curPos != std::string::npos) {
				temp.push_back(val.substr(prvPos, curPos - prvPos));
				prvPos = curPos + 1;
				curPos = val.find(',', prvPos);
			}

			temp.push_back(val.substr(prvPos, curPos - prvPos));
			prvPos = 0; //Reset for next call
		}
	}
}
