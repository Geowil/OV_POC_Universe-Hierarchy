#include "sranges.h"

SRanges::SRanges() {
	//dirty dirty dirty crap, but neccessary
	Range r1;
	Range r2;
	Range r3;

	r1.fLow = 0.3f;
	r1.fHigh = 1.68f;

	r2.fLow = 0.2f;
	r2.fHigh = 1.52f;

	r3.fLow = 0.1f;
	r3.fHigh = 1.18f;

	ranges.push_back(r1);
	ranges.push_back(r2);
	ranges.push_back(r3);

}

float SRanges::getLRange(int pos) {
	return ranges.at(pos).fLow;
}

float SRanges::getHRange(int pos) {
	return ranges.at(pos).fHigh;
}