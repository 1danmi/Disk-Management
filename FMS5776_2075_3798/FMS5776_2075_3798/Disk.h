//class TestLevel_0;
#pragma once
#include "Dat.h"
#include "User.h"
#include "VHD.h"
#include "Dir.h"
#include "Sector.h"
#include "FileHeader.h"
#include <fstream>
#include "FCB.h"
using namespace std;
class FCB;
enum MODE;
class Disk
{
public:
	
	bool vhdUpdate;
	DAT dat;
	bool datUpdate;
	User currUser;
	UsersSec users;
	bool usersUpdate;
	bool rootDirUpdate;
	bool mounted;
	fstream dskfl;
	bool sign;
	unsigned int currDiskSectorNr;
	//char buffer[sizeof(Sector)];
	string lastErrorMessage;
	VHD vhd;
	RootDir rootDir;

#pragma region Level0

	//Ctor
	Disk(void);
	Disk(string&, string&, char, string&);
	//~Disk(void);
	
	void createDisk(string&, string&,string&);
	void mountDisk(string&);
	void unmountDisk(void);
	void recreateDisk(string&);
	bool isMounted();

	fstream * getDskFl();
	void seekToSector(unsigned int);
	void writeSector(unsigned int, Sector*);
	void writeSector(Sector*);
	void readSector(int, Sector*);
	void readSector(Sector*);
	//friend class TestLevel_0;

	void addUser(string& user, SLEVEL sLevel, string& pwd, SLEVEL applicantSLevel = SLEVEL::user);
	void signIn(string& user, string& pwd);
	void signOut();
	void removeUser(string& user, string& pwd);
	void removeUserSigned(string& user, SLEVEL applicantSLevel = SLEVEL::user);
#pragma endregion

#pragma region Level1

	void format();
	unsigned int howMuchEmpty();
	unsigned int howMuchEmpty(unsigned int);

	bool firstFit(DATtype&, unsigned int,unsigned int = 0);
	bool bestFit(DATtype&, unsigned int, unsigned int = 0);
	bool worstFit(DATtype&, unsigned int, unsigned int = 0);

	void alloc(DATtype&, unsigned int, unsigned int=0, unsigned int =0);
	void allocExtend(DATtype&, unsigned int, unsigned int=0);
	void dealloc(DATtype&);

#pragma endregion

#pragma region Level2

	void createFile(string&, string &, unsigned int, unsigned int, unsigned int, string &,SLEVEL, unsigned int, unsigned int = 0, unsigned int=0);
	void delFile(string &);
	void extendFile(string &, unsigned int);
	DATtype& getFat(string&);
	FileHeader& Disk::getFileHeader(string& fileName);
#pragma endregion

#pragma region Level3
	FCB* openFile(string&, MODE);	
#pragma endregion

#pragma region Level4
	string & GetLastErrorMessage();
	void SetLastErrorMessage(string lastErrorMessage);
	VHD getVHD();
	User getCU();
	DAT getDAT();

#pragma endregion
};