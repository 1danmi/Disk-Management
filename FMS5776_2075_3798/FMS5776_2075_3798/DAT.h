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
	unsigned int sectorNr = 1;
private:
	char emptyArea[820];
	
};

