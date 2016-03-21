#pragma once
//#include "Disk.h"
class VHD
{
public:
	/************************************************
	* FUNCTION
	*		VHD
	* PARAMETERS
	*		---
	* RETURN VALUE
	*		---
	* MEANING
	*     default constructor fot VHD class
	* SEE ALSO
	*		---
	*************************************************/
	VHD() {};
	VHD(unsigned int,const char[12],const char[12],const char[10], unsigned int, unsigned int
		, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int
		, const char[10], bool);
	~VHD() {};

private:
	unsigned int sectorNr;
	char diskName[12];
	char diskOwner[12];
	char prodDate[10];
	unsigned int ClusQty;
	unsigned int dataClusQty;
	unsigned int addrDAT;
	unsigned int addrRootDir;
	unsigned int addrDATcpy;
	unsigned int addrRootDirCpy;
	unsigned int addrDataStart;
	char formatDate[10];
	bool isFormated;
	char emptyArea[944];
	friend class TestLevel_0;;
	friend class Disk;
};
