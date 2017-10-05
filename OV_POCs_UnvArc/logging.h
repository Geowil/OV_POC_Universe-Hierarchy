#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <vector>

using std::string;

class Logging {
public:
	Logging();

	void createLReport(string ltype, string lname, string ldesc, string lclass, string ltstamp, string PATH); //create bug report

	void printToFile(const char* PATH);

	bool fileExists(const char *filename);

private:
	string		lName;
	string		lDesc;
	string		lLocale;
	string		lTStamp;
	string		fData; //file data storage
	string		lType; //Type of log (ie: Warn, Err, Info, etc.)
};
#endif