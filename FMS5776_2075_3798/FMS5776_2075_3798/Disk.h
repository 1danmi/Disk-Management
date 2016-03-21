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

class Disk
{
private:
	VHD vhd;
	DAT dat;
	RootDir rootdir;
	bool mounted;
	fstream dskfl;
	unsigned int currDiskSectorNr;

	//char buffer[sizeof(Sector)];

public:
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


};