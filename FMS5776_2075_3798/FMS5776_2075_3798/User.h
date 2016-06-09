#pragma once
#include <string>
using namespace std;

enum SLEVEL {user=1, Administrator,Super_User,Owner};
class User
{
public:
	char name[12];
	SLEVEL sLevel;
	char password[12];
	User();
	User(string &, int, string &);
};
class UsersSec
{
public:
	int sectorNr;
	int numOfUsers = 0;
	User users[5];
	char RawData[1024 - 5*sizeof(User)-2*sizeof(int)];
	UsersSec() {}
	
};