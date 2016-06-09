#pragma once
#include "DAT.h"
#include "DirEntry.h"
#include "user.h"

class FileHeader
{
public:
	unsigned int sectorNr;
	DirEntry fileDesc;
	DATtype fat;
	char emptyArea[744] = { 0 };


	FileHeader() {};
	FileHeader(unsigned int, DirEntry, DATtype,SLEVEL);
	~FileHeader() {};
	SLEVEL sLevel;
	DATtype getFat();
	
};
