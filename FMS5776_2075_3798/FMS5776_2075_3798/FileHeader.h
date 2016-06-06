#pragma once
#include "DAT.h"
#include "DirEntry.h"
#include "user.h"

class FileHeader
{
public:
	FileHeader() {};
	FileHeader(unsigned int, DirEntry, DATtype,SLEVEL);
	~FileHeader() {};
	SLEVEL sLevel;
	DATtype getFat();
	unsigned int sectorNr;
	DirEntry fileDesc;
	DATtype fat;
	char emptyArea[744] = { 0 };
};
