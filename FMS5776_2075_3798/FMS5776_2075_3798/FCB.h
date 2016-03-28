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
public:
	FCB();
	FCB(Disk*);
	~FCB();

	//FCB* openfile(string&, string&, string&);
	void closefile();
	void flushfile();
	void read(char*, [unsigned int]);
	void write(char*);
	void seek(unsigned int, int);
	void updateCancel();
	void Delete();
	void update(char *);
};

