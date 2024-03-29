#include "FileHeader.h"
/*************************************************
* FUNCTION
*	Ctor for FileHeader
* PARAMETERS
*   unsigned int - Sector Number
*	DirEntry - file description
*	DATtype - FAT
* RETURN VALUE
*	---
* MEANING
*	This function initializes the File Header
* SEE ALSO
*	---
**************************************************/
FileHeader::FileHeader(unsigned int sn, DirEntry fd, DATtype fat, SLEVEL sl)
{
	sLevel = sl;
	sectorNr = sn;
	fileDesc = fd;
	this->fat = fat;
	this->recInfo.size = 0;
}

DATtype FileHeader::getFat()
{
	return this->fat;
}
