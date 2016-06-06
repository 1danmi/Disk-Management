#pragma warning (disable:4996)
#include "User.h"

User::User(string & name, int sLevel, string & pwd)
{
	strncpy_s(this->name,12, name.c_str(), 11);
	strncpy_s(this->password, 12, pwd.c_str(), 11);
	switch (sLevel)
	{
	case 0:
		this->sLevel = SLEVEL::Super_User;
		break;
	case 1:
		this->sLevel = SLEVEL::Administrator;
		break;
	case 2:
		this->sLevel = SLEVEL::user;
		break;
	default:
		break;
	}
}
