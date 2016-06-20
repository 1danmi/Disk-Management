#pragma once
#include "DirEntry.h"
struct SectorDir
{
public:
	int sectorNr;
	DirEntry dirEntry[14];
	char unUsed[12];

	SectorDir(void) {};
	SectorDir(int);
	~SectorDir() {};
};

struct RootDir
{
	SectorDir lsbSector;
	SectorDir msbSector;
public:
	RootDir();
	RootDir(unsigned int, unsigned int);
	~RootDir(){};
	
};
