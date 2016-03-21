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
	DATtype dat;
private:
	unsigned int sectorNr = 1;
	
	char emptyArea[820];
	
};

