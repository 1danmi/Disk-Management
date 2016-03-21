#pragma once
#include <bitset>
using namespace std;

typedef bitset<1600> DATtype;

class DAT
{
public:
	DAT();
	~DAT();
	bool operator==(DAT const& dat);
private:
	unsigned int sectorNr = 1;
	DATtype dat;
	char emptyArea[820];
	
};

