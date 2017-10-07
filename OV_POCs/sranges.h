#ifndef SRANGES_H
#define SRANGES_H
#include <string>
#include <vector>
#include "range.h"

class SRanges {
public:
	SRanges();

	float getLRange(int pos);
	float getHRange(int pos);

private:
	std::vector<Range> ranges;
};
#endif