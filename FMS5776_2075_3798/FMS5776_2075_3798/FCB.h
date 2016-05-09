#pragma once
#include "Disk.h"
#include "DirEntry.h"
class FCB
{
public:
	Disk* d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector buffer;
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;
	bool updateMode;

	FCB();
	FCB(Disk*);
	~FCB();

	void closefile();
	void flushfile();
	void readRecord(char*, unsigned int=0);
	void writeRecord(char*);
	void seek(unsigned int, int);
	void updateCancel();
	void deleteRecord();
	void updateRecord(char *);
};

