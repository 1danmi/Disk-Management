#include "DAT.h"

/*************************************************
* FUNCTION
*	default Ctor for DAT
* PARAMETERS
*    ---
* RETURN VALUE
*	---
* MEANING
*     Initialize DAT with default values.
* SEE ALSO
*	---
**************************************************/
DAT::DAT()
{
	dat.set();
}

DAT::~DAT() {}

bool DAT::operator==(DAT const& dat)
{
	return this->dat == dat.dat;
}


