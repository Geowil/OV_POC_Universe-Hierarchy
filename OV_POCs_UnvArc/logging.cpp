#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <direct.h>
#include "logging.h"
#include <chrono>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include "settings.h"


using std::string;
using std::put_time;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::ios;
using std::chrono::system_clock;
using std::chrono::time_point;
using Settings::logLvl;

Logging::Logging() {}

void Logging::createLReport(string ltype, string lname, string ldesc, string llocale, string ltstamp, string PATH) {
	lType = ltype;
	lName = lname;
	lDesc = ldesc;
	lLocale = llocale;
	lTStamp = ltstamp;

	if (logLvl == 1 && lType == "Err") { //If logging level is 1 only print errors
		printToFile(PATH.c_str());
	} else if (logLvl == 2 && (lType == "Err" || lType == "Warn")) { //If logging level is 2; errors and warnings
		printToFile(PATH.c_str());
	} else if (logLvl == 3) { //If logging level is 3 then print all logging messages
		printToFile(PATH.c_str());
	}
}

void Logging::printToFile(const char* PATH) {	
	// Prints UTC timestamp

	time_point<system_clock> now = system_clock::now();
	const time_t now_time = system_clock::to_time_t(now);

	auto gmt_time = localtime(&now_time);
	auto lTStamp = put_time(gmt_time, "%b %d %Y %T ");


	if (!fileExists(PATH)) {
		ofstream oF(PATH);

		if (oF) {
			oF << "Odyssian Void Logging File V1.1" << endl;
			oF << "Please report any Warn or Err log entries at http://bugs.lmpgames.com/tbg/index.php" << endl; //Check bug genie, probably broken
			oF << "Please include entire line of log entry along with the above logging file version" << endl << endl;

			oF << lTStamp << " [" << lType << "]: " << lName << " - " << lDesc << " at " << lLocale << "." << endl;
		}

		oF.close();
	} else {
		ofstream oF;

		oF.open(PATH, ios::app);

		if (oF) {
			oF << lTStamp << " [" << lType << "]: " << lName << " - " << lDesc << " at " << lLocale << "." << endl;
		}

		oF.close();
	}
}

bool Logging::fileExists(const char *filename) {
	ifstream ifile(filename);

	if (ifile.good()) {
		ifile.close();
		return true;
	} else {
		ifile.close();
		return false;
	}
}