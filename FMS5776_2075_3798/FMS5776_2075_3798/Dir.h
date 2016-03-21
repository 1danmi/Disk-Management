#pragma once
#include "DirEntry.h"

struct SectorDir
{
	int sectorNr;
	DirEntry dirEntry[14];
	char unUsed[12];
public:
	SectorDir(void) {};
	SectorDir(int);
	~SectorDir() {};
};

struct RootDir
{
	SectorDir msbSector;
	SectorDir lsbSector;

public:
	RootDir();
	~RootDir(){};
};
