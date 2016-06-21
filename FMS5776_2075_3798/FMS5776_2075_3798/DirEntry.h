#pragma once
#include "User.h"
using namespace std;
class DirEntry
{
public:
	DirEntry();
	DirEntry(const char[12], const char[12] ,unsigned int, unsigned int,
		unsigned int, unsigned int, char[2], unsigned int, unsigned int, 
		const char[2], unsigned char, SLEVEL);
	~DirEntry() {};
	unsigned char getEntryStatus();
	void setEntryStatus(unsigned char);
	char* getFileName();
	char* getOwnerName();
	unsigned int getFileAddr();
	void setFileSize(unsigned int);
	unsigned int getFileSize();
	void setEofRecNr(unsigned int);
	unsigned int getEofRecNr();
	unsigned int getRecSize();
	unsigned int getKeySize();
	unsigned int getKeyOffset();


	char fileName[12];
	char fileOwner[12];
	unsigned int fileAddr; //First sector of the file.
	char crDate[10];
	unsigned int fileSize; // number of sectors
	unsigned int eofRecNr;  //end of file record number
	//unsigned int maxRecSize; // קיבולת תאורטית
	unsigned int actualRecSize; //קיבולת מעשית
	char recFormat[2]; //fixed size
	unsigned int keyOffset;
	unsigned int keySize; //number of bytes
	char keyType[2]; // I - 00 / F - 01 / D - 10 / S - 10
	unsigned char entryStatus; // 0 - empty / 1- active / 2 - deleted
	SLEVEL sLevel;
	
	friend ostream& operator<<(ostream&, const DirEntry&);
};
