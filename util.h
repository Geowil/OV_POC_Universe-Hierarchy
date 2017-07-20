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
	map<string, float> fillMap(map<string, float>argMap);
	map<string, int> fillMap(map<string, int>argMap);

	void createBInfo(string errType, string fl, string lnNm, string dt, string tm, string errCode, string errMsg, string fPath);
	float calcPop(int pERand, int pSRand, int popRand1, int popRand2, int popRand3);
	int getDefenses(int rand, float eks);
	int getShields(int rand, float eks);
	int getIRand(int low, int high);
	float getFRand(float low, float high);
	int calcXP(int base, int level, float factor);

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