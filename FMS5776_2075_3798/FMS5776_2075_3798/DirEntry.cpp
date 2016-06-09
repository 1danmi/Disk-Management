#pragma warning (disable:4996)
#include "DirEntry.h"
#include <cstring>
#include <ctime>
#define CRT_NO_WARNINGS
DirEntry::DirEntry()
{
	strcpy(this->fileName,"");
	strcpy(this->fileOwner,"");
	this->fileAddr = 0;
	char date[10];
	_strdate(date);
	strcpy_s(crDate, date);
	this->fileSize=0;
	this->eofRecNr = 0;
	this->actualRecSize = 0;
	strcpy(this->recFormat,"F");
	this->keyOffset=0;
	this->keySize = 0;
	strcpy(keyType,"F");
	this->entryStatus = '0'; // 0 - empty / 1- active / 2 - deleted
	this->sLevel = SLEVEL::user;
}
/*************************************************
* FUNCTION
*	Ctor for DirEntry
* PARAMETERS
*   char fn - file name
*	char fo - file fo
*	unsigned int fa - file address
*	unsigned int fs - file size (in sectors)
*	unsigned int eorn - EOF record number
*	unsigned int mrs - Maximum Record Size 
*	unsigned int ars - Actual Record Size
*	char rf - 00-F, 01-V, 10-D
*	unsigned int ko - Key Offset
*	unsigned int ks - Key Size
*	char kt - Key Type: 00-int, 01-float, 10-double, 11-char
*	unsigned char es - Entry status: 00-Empty, 01-Active, 10-in active
* RETURN VALUE
*	---
* MEANING
*	This function initializes a DirEntry
* SEE ALSO
*	---
**************************************************/
DirEntry::DirEntry(const char fn[12], const char fo[12], unsigned int fa, unsigned int fs,
	unsigned int eorn, unsigned int ars, char rf[2], unsigned int ko, 
	unsigned int ks, const char kt[2], unsigned char es,SLEVEL sl)
{
	strncpy_s(fileName,12, fn,11);
	strncpy_s(fileOwner,12, fo,11);
	fileAddr = fa;
	char date[10];
	_strdate(date);
	strcpy_s(crDate,date);
	fileSize = fs;  //number of sectors
	eofRecNr = eorn;  //end of file record number
	//maxRecSize = mrs; // קיבולת תאורטית
	actualRecSize = ars; //קיבולת מעשית
	strncpy_s(recFormat,2,rf,1); //fixed size
	keyOffset = ko;
	keySize = ks; //number of bytes
	strcpy_s(keyType, kt);
	entryStatus = es; //empty
	sLevel = sl;
}

unsigned char DirEntry::getEntryStatus()
{
	return this->entryStatus;
}

void DirEntry::setEntryStatus(unsigned char es)
{
	if (es != '0' && es != '1' && es != '2')
		throw "Entry status can be either 0(empty), 1(full) or 2(deleted)";
	entryStatus = es;

}

char * DirEntry::getFileName()
{
	return this->fileName;
}
char * DirEntry::getOwnerName()
{
	return this->fileOwner;
}

unsigned int DirEntry::getFileAddr()
{
	return this->fileAddr;
}

void DirEntry::setFileSize(unsigned int fs)
{
	fileSize = fs;
}

unsigned int DirEntry::getFileSize()
{
	return this->fileSize;
}

void DirEntry::setEofRecNr(unsigned int eof)
{
	this->eofRecNr = eof;
}

unsigned int DirEntry::getEofRecNr()
{
	return this->eofRecNr;
}

unsigned int DirEntry::getRecSize()
{
	return this->actualRecSize;
}

unsigned int DirEntry::getKeySize()
{
	return this->keySize;
}

unsigned int DirEntry::getKeyOffset()
{
	return this->keyOffset;
}

ostream & operator<<(ostream& out, const DirEntry& dirEntry)
{
	out << dirEntry.fileName << "\t" << dirEntry.fileOwner << "\t\t\t" << dirEntry.fileAddr << "\t\t" << dirEntry.crDate << "\t" << dirEntry.fileSize << "\t\t" << dirEntry.eofRecNr << "\t\t\t" << dirEntry.actualRecSize << "\t\t" << dirEntry.recFormat[0] << "\t\t" << dirEntry.keyOffset << "\t\t" << dirEntry.keySize << "\t\t" << dirEntry.keyType << "\t\t" << dirEntry.entryStatus << "\t\t" << dirEntry.sLevel << endl;
	return out;
}
