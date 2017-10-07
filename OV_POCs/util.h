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
	extern float calcPop(float pERand, float pSRand, float popRand1, float popRand2, float popRand3);
	extern int getDefenses(int rand, float eks);
	extern int getShields(int rand, float eks);
	extern int getIRand(int low, int high);
	extern float getFRand(float low, float high);
	extern int calcXP(int base, int level, float factor);
	extern bool validateInpInt(int val, int min, int max);

	extern int updateVal(string op, int val1, int val2);
	extern float updateVal(string op, float val1, float val2);
	extern long long int updateVal(string op, long long int val1, long long int val2);

	//Utility Members
	extern map<string, float>::iterator itf1;
	extern map<string, int>::iterator iti1;
	extern map<string, float>rtnFMap;
	extern map<string, int>rtnIMap;

	extern int i1;
	extern int nOfDef;
	extern int nOfShd;

	//For Debug
	extern string file, bLocale, bTDate;
}
#endif