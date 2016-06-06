#pragma once
#include <string>
using namespace std;

enum SLEVEL {user, Administrator,Super_User,Owner};
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
	int numOfUsers = 0;
	User users[5];
	char RawData[1024 - 5*sizeof(User)-sizeof(int)];
	UsersSec() {}
	
};