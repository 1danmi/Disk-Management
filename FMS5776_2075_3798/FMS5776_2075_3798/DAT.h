#pragma once
#include <bitset>
using namespace std;

typedef bitset<1600> DATtype;

class DAT
{
public:
	DAT();
	~DAT();

private:
	unsigned int sectorNr = 1;
	DATtype dat;
	char emptyArea[820];
};

