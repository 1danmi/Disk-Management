#pragma once
#include "dirEntry.h"
#include "DAT.h"
using namespace std;


class FileHeader
{
public:
	FileHeader() {};
	FileHeader(unsigned int, DirEntry, DATtype);
	~FileHeader() {};
	DATtype getFat();
private:
	unsigned int sectorNr;
	DirEntry fileDesc;
	DATtype fat;
	char emptyArea[744] = { 0 };
};
