#pragma warning (disable:4996)
#include "User.h"

User::User()
{
	memcpy(this->name,"",1);
	memcpy(this->password, "", 1);
	this->sLevel = SLEVEL::user;
}

User::User(string & name, int sLevel, string & pwd)
{
	strncpy_s(this->name,12, name.c_str(), 11);
	strncpy_s(this->password, 12, pwd.c_str(), 11);
	switch (sLevel)
	{
	case 4:
		this->sLevel = SLEVEL::Owner;
		break;
	case 3:
		this->sLevel = SLEVEL::Super_User;
		break;
	case 2:
		this->sLevel = SLEVEL::Administrator;
		break;
	case 1:
		this->sLevel = SLEVEL::user;
		break;
	default:
		break;
	}
}
