#ifndef RANGE_H
#define RANGE_H

struct Range {
	int iLow;
	int iHigh;
	int iOLow;
	int iOHigh;
	int iVal; //For non-low/high ranges

	float fLow;
	float fHigh;
	int fVal; //For non-low/high ranges

	double dLow;
	double dHigh;
	int dVal; //For non-low/high ranges
};

#endif