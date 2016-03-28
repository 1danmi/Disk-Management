#pragma once
#include "Disk.h"
#include "DirEntry.h"
class FCB
{
	Disk* d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector Buffer;
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;
	bool updateMode;
public:
	FCB();
	FCB(Disk*);
	~FCB();

	//FCB* openfile(string&, string&, string&);
	void closefile();
	void flushfile();
	void readRecord(char*, unsigned int=0);
	void writeRecord(char*);
	void seek(unsigned int, int);
	void updateCancel();
	void deleteRecord();
	void updateRecord(char *);
};

