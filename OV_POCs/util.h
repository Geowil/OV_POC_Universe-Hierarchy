#ifndef UTIL__H
#define UTIL__H
#include <string>
#include <vector>
#include <map>
#include <random>

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::to_string;

namespace Util {
	//Utility Function Predefs
	extern map<string, float> fillMap(map<string, float>argMap);
	extern map<string, int> fillMap(map<string, int>argMap);

	extern void createBInfo(string errType, string fl, string lnNm, string dt, string tm, string errCode, string errMsg, string fPath);
	extern int getIRand(int low, int high);
	extern float getFRand(float low, float high);
	extern int calcXP(int base, int level, float factor);
	extern bool validateInpInt(int val, int min, int max);

	extern int updateVal(string op, int newval , int curval);
	extern float updateVal(string op, float newval, float curval);
	extern long long int updateVal(string op, long long int newval, long long int curval);

	//Utility Members
	extern map<string, float>::iterator itf1;
	extern map<string, int>::iterator iti1;
	extern map<string, float>rtnFMap;
	extern map<string, int>rtnIMap;
	extern vector<string> blankCond; //Use when no conditions needed for queries

	extern int i1;

	//For Debug
	extern string file, bLocale, bTDate;
}
#endif