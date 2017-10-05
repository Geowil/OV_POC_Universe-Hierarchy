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

	int i1;
	int nOfDef;
	int nOfShd;

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

	int calcXP(int base, int level, float factor) {
		return trunc(base * (pow(level, factor)));
	}

	int getDefenses(int rand, float eks) {
		if ((eks > 0.0f) && (eks < 1.0f)) { //Type 0 Planet
			if ((rand >= 1) && (rand <= 35)) { nOfDef = 0; } //36% chance for 0 defenses		
			else if ((rand >= 36) && (rand <= 60)) { nOfDef = 1; } //25% chance for 1 defense
			else if ((rand >= 61) && (rand <= 78)) { nOfDef = 2; } //18% chance for 2 defenses
			else if ((rand >= 79) && (rand <= 87)) { nOfDef = 3; } //7% chance for 3 defenses
			else if ((rand >= 88) && (rand <= 94)) { nOfDef = 4; } //7% chance for 4 defenses
			else if ((rand >= 95) && (rand <= 98)) { nOfDef = 5; } //4% chance for 5 defenses
			else if (rand >= 99) { nOfDef = 6; } //2% Chance for 6 defenses
		}
		else if ((eks >= 1.0f) && (eks < 2.0f)) { //Type 1 Planet
			if ((rand >= 1) && (rand <= 28)) { nOfDef = 0; } //29% chance for 0 defenses		
			else if ((rand >= 29) && (rand <= 55)) { nOfDef = 1; } //28% chance for 1 defense
			else if ((rand >= 56) && (rand <= 71)) { nOfDef = 2; } //16% chance for 2 defenses
			else if ((rand >= 72) && (rand <= 82)) { nOfDef = 3; } //11% chance for 3 defenses
			else if ((rand >= 83) && (rand <= 90)) { nOfDef = 4; } //8% chance for 4 defenses
			else if ((rand >= 91) && (rand <= 96)) { nOfDef = 5; } //7% chance for 5 defenses
			else if (rand >= 97) { nOfDef = 6; } //4% Chance for 6 defenses
		}
		else if ((eks >= 2.0f) && (eks < 3.0f)) { //Type 2 Planet
			if ((rand >= 1) && (rand <= 28)) { nOfDef = 0; } //29% chance for 0 defenses		
			else if ((rand >= 29) && (rand <= 56)) { nOfDef = 1; } //28% chance for 1 defense
			else if ((rand >= 57) && (rand <= 70)) { nOfDef = 2; } //14% chance for 2 defenses
			else if ((rand >= 71) && (rand <= 82)) { nOfDef = 3; } //12% chance for 3 defenses
			else if ((rand >= 83) && (rand <= 91)) { nOfDef = 4; } //9% chance for 4 defenses
			else if ((rand >= 92) && (rand <= 96)) { nOfDef = 5; } //5% chance for 5 defenses
			else if (rand >= 97) { nOfDef = 6; } //4% Chance for 6 defenses
		}
		else if ((eks >= 3.0f) && (eks < 4.0f)) { //Type 3 Planet
			if ((rand >= 1) && (rand <= 20)) { nOfDef = 0; } //21% chance for 0 defenses		
			else if ((rand >= 21) && (rand <= 46)) { nOfDef = 1; } //26% chance for 1 defense
			else if ((rand >= 47) && (rand <= 68)) { nOfDef = 2; } //19% chance for 2 defenses
			else if ((rand >= 69) && (rand <= 80)) { nOfDef = 3; } //13% chance for 3 defenses
			else if ((rand >= 81) && (rand <= 89)) { nOfDef = 4; } //9% chance for 4 defenses
			else if ((rand >= 90) && (rand <= 95)) { nOfDef = 5; } //6% chance for 5 defenses
			else if (rand >= 96) { nOfDef = 6; } //3% Chance for 6 defenses
		}
		else if ((eks >= 4.0f) && (eks < 5.0f)) { //Type 4 Planet
			if (rand >= 1 && rand <= 18) { nOfDef = 0; } //19% chance for 0 defenses		
			else if (rand >= 19 && rand <= 35) { nOfDef = 1; } //15% chance for 1 defense
			else if (rand >= 36 && rand <= 55) { nOfDef = 2; } //20% chance for 2 defenses
			else if (rand >= 56 && rand <= 68) { nOfDef = 3; } //13% chance for 3 defenses
			else if (rand >= 69 && rand <= 80) { nOfDef = 4; } //12% chance for 4 defenses
			else if (rand >= 81 && rand <= 89) { nOfDef = 5; } //9% chance for 5 defenses
			else if (rand >= 90 && rand <= 95) { nOfDef = 6; } //6% Chance for 6 defenses
			else if (rand >= 96) { nOfDef = 7; } //5% chance for 7 defenses
		}
		else if (eks >= 5.0f) { //Type 5 Planet
			if (rand >= 1 && rand <= 12) { nOfDef = 0; } //13% chance for 0 defenses		
			else if (rand >= 13 && rand <= 28) { nOfDef = 1; } //16% chance for 1 defense
			else if (rand >= 29 && rand <= 48) { nOfDef = 2; } //20% chance for 2 defenses
			else if (rand >= 49 && rand <= 62) { nOfDef = 3; } //14% chance for 3 defenses
			else if (rand >= 63 && rand <= 74) { nOfDef = 4; } //12% chance for 4 defenses
			else if (rand >= 75 && rand <= 85) { nOfDef = 5; } //11% chance for 5 defenses
			else if (rand >= 86 && rand <= 92) { nOfDef = 6; } //9% Chance for 6 defenses
			else if (rand >= 93 && rand <= 97) { nOfDef = 7; } //5% Chance for 7 defenses
			else if (rand >= 98) { nOfDef = 8; } //3% chance for 8 defenses
		}

		return nOfDef;
	}

	int getShields(int rand, float eks) {
		if ((eks > 0.0f) && (eks < 1.0f)) { //Type 0 Planet
			if ((rand >= 1) && (rand <= 60)) { nOfShd = 0; } //61% chance for 0 shields
			else if ((rand >= 61) && (rand <= 86)) { nOfShd = 1; } //26% chance for 1 shields
			else if (rand >= 86) { nOfShd = 2; } //17% chance for 2 shields
		}
		else if ((eks >= 1.0f) && (eks < 2.0f)) { //Type 1 Planet
			if ((rand >= 1) && (rand <= 52)) { nOfShd = 0; } //53% chance for 0 shields
			else if ((rand >= 53) && (rand <= 84)) { nOfShd = 1; } //22% chance for 1 shields
			else if (rand >= 85) { nOfShd = 2; } //15% chance for 2 shields
		}
		else if ((eks >= 2.0f) && (eks < 3.0f)) { //Type 2 Planet
			if ((rand >= 1) && (rand <= 35)) { nOfShd = 0; } //36% chance for 0 shields
			else if ((rand >= 36) && (rand <= 68)) { nOfShd = 1; } //33% chance for 1 shields
			else if ((rand >= 68) && (rand <= 87)) { nOfShd = 2; } //18% chance for 2 shields
			else if (rand >= 88) { nOfShd = 3; } //13% chance for 3 shields
		}
		else if ((eks >= 3.0f) && (eks < 4.0f)) { //Type 3 Planet
			if ((rand >= 1) && (rand <= 27)) { nOfShd = 0; } //28% chance for 0 shields
			else if ((rand >= 28) && (rand <= 64)) { nOfShd = 1; } //27% chance for 1 shields
			else if ((rand >= 65) && (rand <= 84)) { nOfShd = 2; } //21% chance for 2 shields
			else if (rand >= 85) { nOfShd = 3; } //16% chance for 3 shields
		}
		else if ((eks >= 4.0f) && (eks < 5.0f)) { //Type 4 Planet
			if ((rand >= 1) && (rand <= 20)) { nOfShd = 0; } //21% chance for 0 shields
			else if ((rand >= 21) && (rand <= 48)) { nOfShd = 1; } //28% chance for 1 shields
			else if ((rand >= 49) && (rand <= 74)) { nOfShd = 2; } //26% chance for 2 shields
			else if ((rand >= 75) && (rand <= 88)) { nOfShd = 3; } //14% chance for 3 shields
			else if (rand >= 89) { nOfShd = 4; } //12% chance for 4 shields
		}
		else if (eks >= 5.0f) { //Type 5 Planet
			if ((rand >= 1) && (rand <= 18)) { nOfShd = 0; } //19% chance for 0 shields
			else if ((rand >= 19) && (rand <= 36)) { nOfShd = 1; } //18% chance for 1 shields
			else if ((rand >= 37) && (rand <= 65)) { nOfShd = 2; } //29% chance for 2 shields
			else if ((rand >= 66) && (rand <= 84)) { nOfShd = 3; } //19% chance for 3 shields
			else if (rand >= 85) { nOfShd = 4; } //16% chance for 4 shields
		}

		return nOfShd;
	}

	float calcPop(float pERand, float pSRand, float popRand1, float popRand2, float popRand3) {
		float rPop = ((((((8000.0f * popRand1) * popRand2) * pERand) * pSRand) * popRand3) / 6.0f);

		//if rPop is negative, flip the sign
		if (rPop < 0) { rPop = rPop * -1; }

		return rPop;
	}

	int getIRand(int low, int high) { return std::uniform_int_distribution<>{low, high}(gen); }
	float getFRand(float low, float high) { return std::uniform_real_distribution<float> {low, high}(gen); }

	extern bool validateInpInt(int val, int min, int max) {
		if (val < min || val > max) { return false; }
		else { return true; }
	}
}
