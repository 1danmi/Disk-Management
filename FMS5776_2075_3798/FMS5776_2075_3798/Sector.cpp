#include "Sector.h"
#include <string>

/*************************************************
* FUNCTION
*	Ctor for Sector
* PARAMETERS
*   unsigned int – Sector Number
*	char[1020] - raw Data
* RETURN VALUE
*	---
* MEANING
*     This function initializes the Sector
* SEE ALSO
*	---
**************************************************/
Sector::Sector(unsigned int sn, char rd[1020])
{
	sectorNr = sn;
	strcpy_s(rawData, rd);
}
