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
#include "Today.h"

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
	//Ctor
	Disk(void);
	Disk(string&, string&, char);
	~Disk(void);
	void seekToSector(unsigned int);
	void createDisk(string&, string&);
	void mountDisk(string&);
	void unmountDisk(void);
	void recreateDisk(string&);

	/*fstream * getDskFl();

	
	
	void writeSector(unsigned int, Sector*);
	void writeSector(Sector*);
	
	void readSector(int, Sector*);
	void readSector(Sector*);*/
	friend class TestLevel_0;
};