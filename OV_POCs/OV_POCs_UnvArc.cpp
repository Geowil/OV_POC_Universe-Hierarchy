#include "universe.h"
#include "save.h"
#include "load.h"
#include <iostream>
#include "util.h"
#include "settings.h"
#include "dataSystem.h"
#include <Windows.h>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::system;
using std::map;

namespace u = Util;
namespace setting = Settings;

int main() {
	Universe uni_main;
	dataSystem ds_main;

	//vars
	int gDiffSelect, i1 = 1;
	char cInp;

	/*uni.createUniverse();
	uni.createPlSystems();

	cout << "There are " << uni.getSystems().size() << " planetary systems in the game universe..." << endl;
	for (int i1 = 0; i1 < uni.getSystems().size(); i1++) {
		cout << endl;
		cout << "System Name: " << uni.getSystems().at(i1).getName() << endl;
		cout << "\t Planets: " << endl;

		for (int i2 = 0; i2 < uni.getSystems().at(i1).getPlanets().size(); i2++) {
			cout << "\t\t" << uni.getSystems().at(i1).getPlanets().at(i2).getName() << endl;
			cout << "\t\t Population: " << uni.getSystems().at(i1).getPlanets().at(i2).getPopS() << endl;
			cout << "\t\t Size: " << uni.getSystems().at(i1).getPlanets().at(i2).getSize() << endl;
			cout << "\t\t EKS: " << uni.getSystems().at(i1).getPlanets().at(i2).getEKS() << endl;

			cout << endl;
		}
	}

	//cout << u::calcPop(30, 200, 10, 25, 30) << endl;*/
	
	if (!ds_main.openDB()) {
		cout << "Problem opening database.  Please check error log." << endl;
	} else {
		ds_main.prepQuery("Settings", "select from", 0, u::blankCond);
		setting::setSMap(ds_main.getSettings());
		
		setting::loadSettings();
		setting::loadPltSettings();
		setting::loadDiffSettings();
		setting::loadOreTypeSettings();
		setting::loadRoidOSettings();

		uni_main.createUniverse();
	}

	system("pause");

	return 0;
}