#pragma once
#include "DAT.h"
#include "DirEntry.h"

class FileHeader
{
public:
	FileHeader() {};
	FileHeader(unsigned int, DirEntry, DATtype);
	~FileHeader() {};
	DATtype getFat();
	unsigned int sectorNr;
	DirEntry fileDesc;
	DATtype fat;
	char emptyArea[744] = { 0 };
};
