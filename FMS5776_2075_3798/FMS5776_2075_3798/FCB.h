#pragma once
#include "Disk.h"
#include "DirEntry.h"
enum MODE{W,R,WR,E};
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
	bool lock = 0;
	MODE mode;
	

	FCB();
	FCB(Disk*);
	~FCB();

	void closeFile();
	void flushFile();
	void readRecord(char*, unsigned int=0);
	void writeRecord(char*);
	void seek(unsigned int, int);
	void updateCancel();
	void deleteRecord();
	void updateRecord(char *);
};

