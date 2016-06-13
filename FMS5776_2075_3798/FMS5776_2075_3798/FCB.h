#pragma once
#include "Disk.h"
#include "RecInfo.h"
enum MODE{W,R,WR,E};
class Disk;
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
	unsigned int numOfRecords;
	string lastErrorMessage;
	int maxRecNum;
	int DAT[46];
	// recInfo _recInfo;
	FCB();
	FCB(Disk*);
	~FCB();
	RecInfo recInfo;
	void closeFile();
	void flushFile();
	void readRecord(char*, unsigned int = 0, unsigned int = -1);
	void addRecord(char*, unsigned int = -1);
	//void seek(unsigned int, int);
	void updateCancel();
	void deleteRecord(int rec);
	void updateRecord(char *);
	int findRecByKey(string&);

	string & GetLastErrorMessage();
	void SetLastErrorMessage(string lastErrorMessage);
};

