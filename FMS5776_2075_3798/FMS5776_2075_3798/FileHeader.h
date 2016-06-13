#pragma once
#include "DAT.h"
#include "DirEntry.h"
#include "user.h"
#include "RecInfo.h"

class FileHeader
{
public:
	unsigned int sectorNr;
	DirEntry fileDesc;
	DATtype fat;
	RecInfo recInfo;
	char emptyArea[16] = { 0 };


	FileHeader() {};
	FileHeader(unsigned int, DirEntry, DATtype,SLEVEL);
	~FileHeader() {};
	SLEVEL sLevel;
	DATtype getFat();
	
};
