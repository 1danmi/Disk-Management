#pragma once
#include "Disk.h"
#include "DirEntry.h"
enum MODE{W,R,WR,E};
class FCB
{
public:
	Disk* d;
	int path;
	DirEntry fileDesc;
	DATtype FAT;
	Sector buffer;
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;
	bool updateMode;
	bool lock = 0;
	MODE mode;
	int numOfRecords;
	string lastErrorMessage;
	

	FCB();
	FCB(Disk*);
	~FCB();

	void closeFile();
	void flushFile();
	void readRecord(char*, unsigned int = 0, unsigned int = -1);
	void writeRecord(char*, unsigned int = -1);
	//void seek(unsigned int, int);
	void updateCancel();
	void deleteRecord();
	void updateRecord(char *);

	string & GetLastErrorMessage();
	void SetLastErrorMessage(string lastErrorMessage);
};

