#pragma warning (disable:4996)
#include "Disk.h"
#include <ctime>

void Disk::seekToSector(unsigned int num)
{
	try
	{
		if (!dskfl.is_open())
		{
			throw "Disk file is not open!";
		}
		currDiskSectorNr = num;
		this->dskfl.seekp(currDiskSectorNr * 1024);
		this->dskfl.seekg(currDiskSectorNr * 1024);
	}
	catch (const char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown error";
	}
}

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
	bool mounted = false;
	unsigned int currDiskSectorNr = 0;
	//char buffer[sizeof(Sector)] = NULL;
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
	//if(mounted)
		//unmountDisk();
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
		dskfl.open(fileName, ios::binary | ios::out);
		if (dskfl.is_open())
		{
			char rawData[1020] = { 0 };
			for (int i = 0; i < 3200; i++)
			{
				Sector sec(i, rawData);
				dskfl.write((char*)& sec, sizeof(Sector));
			}
			dskfl.seekp(0);
			//VHD Initialization.
			string fd = "00/00/000";
			char date[10];
			_strdate(date);
			vhd = VHD(0, dn.c_str(), dow.c_str(), date, 1600, 1596, 1, 2, 800, 1000, 3, fd.c_str(), false);
			dskfl.write((char*)& vhd, sizeof(Sector));
			vhdUpdate = 0;
			//DAT Initialization
			this->dat.dat.set();
			for (int i = 0; i < 4; i++)
				this->dat.dat[i] = 0;
			dskfl.close();
			datUpdate = 0;
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
		if (mounted)
			throw "Disk already mounted";
		dskfl.open(fn+".fms", ios::in, ios::binary);
		if (dskfl.is_open() == true)
		{
			mounted = true;
			dskfl.read((char*)& vhd, 1024);
			dskfl.read((char*)& dat, 1024);
			dskfl.read((char*)& rootDir, 2048);
			currDiskSectorNr = 3;
			vhdUpdate = 0;
			datUpdate = 0;
			rootDirUpdate = 0;
		}
		else
			throw "File Problem!";
	}
	catch (const std::exception&)
	{
		throw "Mount unsuccesful";
	}
}

void Disk::unmountDisk(void)
{
	try
	{
		if (dskfl.is_open())
		{
			dskfl.seekp(0);
			if(vhdUpdate)
				dskfl.write((char*)& vhd, sizeof(Sector));
			if(datUpdate)
				dskfl.write((char*)& rootDir, sizeof(Sector));
			if(rootDirUpdate)
				dskfl.write((char*)& rootDir, sizeof(Sector)*2);
			dskfl.close();
			mounted = false;
		}
		else
			throw "File is open!";
	}
	catch (const char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown Problem!";
	}
}

void Disk::recreateDisk(string &)
{
}

//fstream * Disk::getDskFl()
//{
//	return nullptr;
//}
//
//void Disk::seekToSector(unsigned int)
//{
//}
//
//void Disk::writeSector(unsigned int, Sector *)
//{
//}
//
//void Disk::writeSector(Sector *)
//{
//}
//
//void Disk::readSector(int, Sector *)
//{
//}
//
//void Disk::readSector(Sector *)
//{
//}
