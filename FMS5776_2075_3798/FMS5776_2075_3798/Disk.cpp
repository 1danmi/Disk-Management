#pragma warning (disable:4996)
#include "Disk.h"
#include <ctime>

/*************************************************
* FUNCTION
*	defu=ault Ctor
* PARAMETERS
*   VHD - creates a disk header;
*	DAT - creates a disk DAT map;
*	RootDir - creates a disk directory;
*	bool - is the disk mounted?;
*	fstream  - DATA;
*	unsigned int - current sector number;
* RETURN VALUE
*	---
* MEANING
*     This function initializes the Disk with default parametres
* SEE ALSO
*	---
**************************************************/
Disk::Disk(void)
{
	VHD vhd();
	DAT dat();
	RootDir rootdir();
	bool mounted = false;
	fstream dskfl();
	unsigned int currDiskSectorNr = 0;
	//char buffer[sizeof(Sector)] = NULL;ffhkjhj
}

/*************************************************
* FUNCTION
*	Ctor for Disk class
* PARAMETERS
*    string& - Disk name
*    string& - Disk owner
*    char - c/m (c - to create disk, m - to mount disk)
* RETURN VALUE
*
* MEANING
*     This function initializes a new disk
* SEE ALSO
*
**************************************************/
Disk::Disk(string & dn, string & dow, char flag)
{
	
	try
	{
		dskfl.open("NewDisk.fms", ios::out | ios::in, ios::binary);
		if (flag == 'c')
		{
			createDisk(dn, dow);
		}
		else if (flag == 'm')
		{
			mountDisk(dn);
		}
		else
		{
			throw "Invalid parameters!";
		}
	}
	catch (const char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "File Problem!";
	}
}

Disk::~Disk(void)
{
	if(mounted)
		unmountDisk();
	//dskfl.close();
}
/*************************************************
* FUNCTION
*	createDisk
* PARAMETERS
*   string& - Disk name
*	string& - Disk owner
* RETURN VALUE
*	---
* MEANING
*     This function creates a new disk. NOT formatted.
* SEE ALSO
*
**************************************************/
void Disk::createDisk(string & dn, string & dow)
{
	try
	{
		string fileName = dn + ".fms";
		dskfl.open(fileName, ios::in | ios::out);
		if (dskfl.is_open())
		{
			char rawData[1020] = { 0 };
			for (int i = 0; i < 3200; i++)
			{
				Sector sec = Sector(i, rawData);
				dskfl.write((char*)& sec, sizeof(Sector));
			}
			dskfl.seekp(0);

			string fd = "00/00/000";
			char date[10];
			_strdate(date);
			vhd = VHD(0, dn.c_str(), dow.c_str(), date, 1600, 1596, 1, 2, 800, 1000, 3, fd.c_str(), false);
			dskfl.write((char*)& vhd, sizeof(Sector));

			dskfl.flush();
		}
		else
			throw "File Problem!";
	}
	catch (const char* str)
	{
		throw str;
	}
}

void Disk::mountDisk(string & fn)
{
	try
	{
		dskfl.open(fn, ios::in, ios::binary);
		if (dskfl.is_open() == true)
		{
			mounted = true;
			dskfl.read((char*)& vhd, 1024);
			dskfl.read((char*)& dat, 1024);
			dskfl.read((char*)& rootdir, 2048);
			currDiskSectorNr = 3;
		}
	}
	catch (const std::exception&)
	{
		throw "Mount unsuccesful";
	}
}

void Disk::unmountDisk(void)
{
	
	dskfl.close();
	mounted = false;
}

void Disk::recreateDisk(string &)
{
}

fstream * Disk::getDskFl()
{
	return nullptr;
}

void Disk::seekToSector(unsigned int)
{
}

void Disk::writeSector(unsigned int, Sector *)
{
}

void Disk::writeSector(Sector *)
{
}

void Disk::readSector(int, Sector *)
{
}

void Disk::readSector(Sector *)
{
}
