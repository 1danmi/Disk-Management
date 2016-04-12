#include "Dir.h"
/*************************************************
* FUNCTION
*	default Ctor for RootDir
* PARAMETERS
*   ---
* RETURN VALUE
*	---
* MEANING
*	This function initializes the RootDir struct
* SEE ALSO
*	---
**************************************************/
RootDir::RootDir()
{
	msbSector = SectorDir(2);
	lsbSector = SectorDir(3);
}
/*************************************************
* FUNCTION
*	Ctor for SectorDir
* PARAMETERS
*    int - num (number of sector)
* RETURN VALUE
*	---
* MEANING
*     This function initializes the SectorDir struct
* SEE ALSO
*	---
**************************************************/
SectorDir::SectorDir(int num)
{
	sectorNr = num;
}
