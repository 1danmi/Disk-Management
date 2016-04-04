#pragma warning (disable:4996)
#include "DirEntry.h"
#include <ctime>
#define CRT_NO_WARNINGS
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
	unsigned int eorn, unsigned int mrs, unsigned int ars, char rf, unsigned int ko, 
	unsigned int ks, const char kt[2], unsigned char es)
{
	strcpy_s(fileName, fn);
	strcpy_s(fileOwner, fo);
	fileAddr = fa;
	char date[10];
	_strdate(date);
	strcpy_s(crDate,date);
	fileSize = fs;  //number of sectors
	eofRecNr = eorn;  //end of file record number
	maxRecSize = mrs; // קיבולת תאורטית
	actualRecSize = ars; //קיבולת מעשית
	recFormat[2] = rf; //fixed size
	keyOffset = ko;
	keySize = ks; //number of bytes
	strcpy_s(keyType, kt);
	entryStatus = es; //empty
}

unsigned char DirEntry::getEntryStatus()
{
	return this->entryStatus;
}

void DirEntry::setEntryStatus(unsigned char es)
{
	if (es != '0' || es != '1' || es != '2')
		throw "Entry status can be either 0(empty), 1(full) or 2(deleted)";
	entryStatus = es;

}

char * DirEntry::getFileName()
{
	return this->fileName;
}


