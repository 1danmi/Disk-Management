#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Dir.h"
#include "VHD.h"
#include "DirEntry.h"
#include "FileHeader.h"
#include "Sector.h"
#include "DAT.h"
#include "FCB.h"

using namespace std;
class TestLevel_0;

class Disk
{
private:
	VHD vhd;
	bool vhdUpdate;
	DAT dat;
	bool datUpdate;
	RootDir rootDir;
	bool rootDirUpdate;
	bool mounted;
	fstream dskfl;
	unsigned int currDiskSectorNr;
	//char buffer[sizeof(Sector)];


public:
#pragma region Level0

	//Ctor
	Disk(void);
	Disk(string&, string&, char);
	~Disk(void);
	
	void createDisk(string&, string&);
	void mountDisk(string&);
	void unmountDisk(void);
	void recreateDisk(string&);

	fstream * getDskFl();
	void seekToSector(unsigned int);
	void writeSector(unsigned int, Sector*);
	void writeSector(Sector*);
	void readSector(int, Sector*);
	void readSector(Sector*);
	friend class TestLevel_0;

#pragma endregion

#pragma region Level1

	void format(string&);
	int howMuchEmpty();
	int howMuchEmpty(unsigned int);

	bool firstFit(DATtype&, unsigned int,unsigned int);
	bool bestFit(DATtype&, unsigned int, unsigned int);
	bool worstFit(DATtype&, unsigned int, unsigned int);

	void alloc(DATtype&, unsigned int, unsigned int);
	void allocExtend(DATtype&, unsigned int, unsigned int);
	void dealloc(DATtype&);

#pragma endregion

#pragma region Level3
//	FCB* openfile(string&, string&, string&);
#pragma endregion


	
};