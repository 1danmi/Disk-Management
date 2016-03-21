//#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Dir.h"
#include "VHD.h"
#include "DirEntry.h"
#include "FileHeader.h"
#include "Sector.h"
#include "DAT.h"
#include "Disk.h"
using namespace std;

int main()
{
	try
	{
		Disk disk((string)"Disk1", (string)"Owner", 'c');
		cin.get();
	}
	catch (const char* str)
	{
		cout << str << endl;
	}

	return 0;

}