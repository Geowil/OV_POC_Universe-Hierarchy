#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <direct.h>
#include "logging.h"

using namespace std;

Logging::Logging() {}

void Logging::createLReport(string ltype, string lname, string ldesc, string llocale, string ltstamp, string PATH) {
	lType = ltype;
	lName = lname;
	lDesc = ldesc;
	lLocale = llocale;
	lTStamp = ltstamp;

	printToFile(PATH.c_str());
}

void Logging::printToFile(string PATH) {
	if (!fileExists(PATH.c_str())) {
		ofstream oF(PATH.c_str());

		if (oF) {
			oF << "Odyssian Void Logging File V1.1" << endl;
			oF << "Please report any Warn or Err log entries at http ://bugs.lmpgames.com/tbg/index.php" << endl;
			oF << "Please include entire line of log entry along with the above logging file version" << endl << endl;

			oF << lTStamp << " [" << lType << "]: " << lName << " - " << lDesc << " at " << lLocale << "." << endl;
		}

		oF.close();
	}
	else {
		ofstream oF;

		oF.open(PATH.c_str(), ios::app);

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
	}
	else {
		ifile.close();
		return false;
	}
}