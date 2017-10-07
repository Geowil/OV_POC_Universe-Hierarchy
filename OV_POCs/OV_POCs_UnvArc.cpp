#include "universe.h"
#include "save.h"
#include "load.h"
#include <iostream>
#include "util.h"
#include "settings.h"
#include "dataSystem.h"
#include <Windows.h>
#include <map>

using namespace std;
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
		ds_main.prepQuery("Settings", "select from", 0, vector<string>());
		setting::setSMap(ds_main.getSettings());
		setting::loadPltSettings();

		for (setting::pltTypeSettings pt : setting::gPltTypSettings) {
			cout << pt.getSettingType() << " EKS Range: " << pt.getPltEksRng().fLow << "-" << pt.getPltEksRng().fHigh << endl;
			cout << pt.getSettingType() << " Size Range: " << pt.getPltSzRng().iLow << "-" << pt.getPltSzRng().iHigh << endl;
			cout << pt.getSettingType() << " Outlier Range: " << pt.getPltOutlrRng().fLow << "-" << pt.getPltOutlrRng().fHigh << endl;
			cout << pt.getSettingType() << " Size Random Range: " << pt.getPltSzRndRng().fLow << "-" << pt.getPltSzRndRng().fHigh << endl;
	
			cout << endl << endl;
		}

		/*for (string diff : setting::gameDiffs) {
			cout << i1 << ": " << diff << endl;
			i1++;
		}
		
		cout << endl;
		cout << "Please select the game difficulty: >";
		cin >> gDiffSelect;
		cout << endl;
		 
		if (cin && u::validateInpInt(gDiffSelect, 1, setting::gameDiffs.size())) {
			system("CLS");

			setting::setDifficulty(setting::gameDiffs.at(gDiffSelect - 1));
			setting::loadDiffSettings();
			setting::setDiffSettings();
			cout << "You have chosen " << setting::sGameDifficulty << ".  Here is how this setting affects the game: " << endl << endl;
			setting::printMods();
		} else {
			cout << "You made an invalid entry" << endl;
		}*/
	}

	system("pause");

	return 0;
}