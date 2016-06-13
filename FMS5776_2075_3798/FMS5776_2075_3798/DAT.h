#pragma once
#include <bitset>
using namespace std;
typedef bitset<1600> DATtype;

class DAT
{
public:
	DAT();
	~DAT();
	unsigned int sectorNr = 1;
	DATtype dat;
	bool operator==(DAT const& dat);
	
private:
	char emptyArea[816];
	
};

