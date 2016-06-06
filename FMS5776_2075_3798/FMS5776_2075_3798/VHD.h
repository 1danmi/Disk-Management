#pragma once
using namespace std;
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
		, const char[10], bool, unsigned int);
	~VHD() {};
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
	unsigned int addrUserSec;
	char formatDate[10];
	bool isFormated;
	char emptyArea[940];
	friend class TestLevel_0;;
	friend class Disk;
};
