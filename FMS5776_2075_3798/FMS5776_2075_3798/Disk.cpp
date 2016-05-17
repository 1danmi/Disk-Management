#pragma warning (disable:4996)
#include "Disk.h"
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

#pragma region Level0

/*************************************************
* FUNCTION
*	void Disk(void)
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
*	Default CTOR for Disk.  
*	This function initializes the Disk with default parametres.
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
*	void Disk(string & dn, string & dow, char flag)
* PARAMETERS
*	string& - Disk name
*	string& - Disk owner
*	char - c/m (c - to create disk, m - to mount disk)
* RETURN VALUE
*	---
* MEANING
*	This function initializes a new disk.
* SEE ALSO
*	void createDisk(string&, string&)
*	void mountDisk(string&)
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

/*************************************************
* FUNCTION
*	~Disk(void)
* PARAMETERS
*	---
* RETURN VALUE
*	---
* MEANING
*	DTOR for Disk.
* SEE ALSO
*	void unmountDisk(void)
**************************************************/
Disk::~Disk(void)
{
	if(mounted)
		unmountDisk();
	//dskfl.close();
}

/*************************************************
* FUNCTION
*	void createDisk(string&, string&)
* PARAMETERS
*   string& - Disk name
*	string& - Disk owner
* RETURN VALUE
*	---
* MEANING
*	This function creates a new disk. NOT formatted.
* SEE ALSO
*	---
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

/*************************************************
* FUNCTION
*	void mountDisk(string&)
* PARAMETERS
*   string& - file name.
* RETURN VALUE
*	---
* MEANING
*	This function mounts the disk
* SEE ALSO
*	---
**************************************************/
void Disk::mountDisk(string & fn)
{
	try
	{
		if (mounted)
			throw "Disk already mounted";
		dskfl.open(fn+".fms", ios::in, ios::binary);
		if (dskfl.is_open())
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

/*************************************************
* FUNCTION
*	void unmountDisk(void)
* PARAMETERS
*	---
* RETURN VALUE
*	---
* MEANING
*	This function unmounts the disk.
* SEE ALSO
*	---
**************************************************/
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

/*************************************************
* FUNCTION
*	void recreateDisk(string&)
* PARAMETERS
*	string& - name of disk owner
* RETURN VALUE
*	---
* MEANING
*   This function recreates the disk. 
*	does the same then creating disk but doen't create a new file, instead just reinitializes the values.
*	conditions: a) file exists. b) wasn't mounted.
* SEE ALSO
*	---
**************************************************/
void Disk::recreateDisk(string & dow)
{
	try
	{
		if (mounted) return;
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
			vhd = VHD(0, vhd.diskName, dow.c_str(), date, 1600, 1596, 1, 2, 800, 1000, 3, fd.c_str(), false);
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
			throw "Disk doesn't exist";
	}
	catch (const char* str)
	{
		throw str;
	}
}

/*************************************************
* FUNCTION
*	bool isMounted();
* PARAMETERS
*   ---
* RETURN VALUE
*	Return wether the disk is mounted or not.
* MEANING
*   Return True if the disk is mounted, else - False.
* SEE ALSO
*	---
**************************************************/
bool Disk::isMounted()
{
	return mounted;
}

/*************************************************
* FUNCTION
*	fstream * getDskFl();
* PARAMETERS
*    ---
* RETURN VALUE
*	Returns the disk's file.
* MEANING
*   This function returns a fstream of the disk file.
* SEE ALSO
*	---
**************************************************/
fstream* Disk::getDskFl()
{
	if(dskfl.is_open())
		return &dskfl;
	return NULL;
}

/*************************************************
* FUNCTION
*	void seekToSector(unsigned int)
* PARAMETERS
*   unsigned int – number of sector to go to.
* RETURN VALUE
*	---
* MEANING
*   This function moves the I/O head to the wanted sector.
* SEE ALSO
*	---
**************************************************/
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
*	void writeSector(unsigned int, Sector*)
* PARAMETERS
*   unsigned int - sector number to write on.
*	Sector* - sector to write.
* RETURN VALUE
*	---
* MEANING
*   This function writes a sector to the disk.
* SEE ALSO
*	void seekToSector(unsigned int)
**************************************************/
void Disk::writeSector(unsigned int num, Sector* sec)
{
	try
	{
		if (num > 3200 || num <0)
			throw "Sector number is incorrect!";
		if (dskfl.is_open())
		{
			this->seekToSector(num);
			dskfl.write((char*)sec, sizeof(Sector));
			this->seekToSector(num + 1);
			this->currDiskSectorNr = num + 1;
		}
		else
			throw "File problem!";
	}
	catch(const char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown Problem!";
	}
}

/*************************************************
* FUNCTION
*	void writeSector(Sector*)
* PARAMETERS
*	Sector* - sector to write.
* RETURN VALUE
*	---
* MEANING
*   This function writes a sector to the disk.
* SEE ALSO
*	void seekToSector(unsigned int)
**************************************************/
void Disk::writeSector(Sector* sec)
{
	try
	{
		if (!dskfl.is_open())
			throw "File problem!";
		if (currDiskSectorNr > 3200)
			throw "Disk is full!";
		seekToSector(currDiskSectorNr);
		dskfl.write((char*)sec, sizeof(Sector));
		if (currDiskSectorNr < 3200)
		{
			currDiskSectorNr++;
			seekToSector(currDiskSectorNr);
		}
		else
		{
			currDiskSectorNr++;
			seekToSector(0);
		}
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

/*************************************************
* FUNCTION
*	void readSector(int, Sector*)
* PARAMETERS
*   int - sector number to read.
*	Sector* - buffer.
* RETURN VALUE
*	---
* MEANING
*   This function reads a sector on the disk.
* SEE ALSO
*	void seekToSector(unsigned int)
**************************************************/
void Disk::readSector(int num, Sector* sec)
{
	try
	{
		if (num > 3200 || num < 0)
			throw "Sector number is incorrect!";
		if (dskfl.is_open())
		{
			this->seekToSector(num);
			dskfl.read((char*)sec, sizeof(Sector));
			this->seekToSector(num + 1);
			this->currDiskSectorNr = num + 1;
		}
		else
			throw "File problem!";
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

/*************************************************
* FUNCTION
*	void readSector(Sector*)
* PARAMETERS
*	Sector* - sector to write.
* RETURN VALUE
*	---
* MEANING
*   This function reads a sector on the disk.
* SEE ALSO
*	void seekToSector(unsigned int)
**************************************************/
void Disk::readSector(Sector* sec)
{
	try
	{
		if (!dskfl.is_open())
			throw "File problem!";
		if (currDiskSectorNr > 3200)
			throw "Current disk sector is out of range!";
		seekToSector(currDiskSectorNr);
		dskfl.read((char*)sec, sizeof(Sector));
		if (currDiskSectorNr < 3200)
		{
			currDiskSectorNr++;
			seekToSector(currDiskSectorNr);
		}
		else
		{
			currDiskSectorNr++;
			seekToSector(0);
		}
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

#pragma endregion

#pragma region Level1

/*************************************************
* FUNCTION
*	void format(string&)
* PARAMETERS
*   string& - name of user
* RETURN VALUE
*	---
* MEANING
*   This function formats the disk
*	conditions: user name == disk owner name
*				not formated.
*				is mounted.
*				disk exists.
* SEE ALSO
*	---
**************************************************/
void Disk::format(string& name)
{
	if (vhd.isFormated) throw "already formated";
	if (strcmp(vhd.diskOwner, name.c_str()))
		throw "Only the disk owner can format the disk!";
	if (!mounted)
		throw "No disk is mounted!";
	if (!dskfl.is_open())
		throw "File problem!";
	dat.dat.set();
	for (int i = 0; i < 4; i++)
		this->dat.dat[i] = 0;
	datUpdate = 1;
	for (int i = 0; i < 14; i++)
	{
		rootDir.lsbSector.dirEntry[i].setEntryStatus('0');
		rootDir.msbSector.dirEntry[i].setEntryStatus('0');
	}
	rootDirUpdate = 1;
	_strdate(vhd.formatDate);
	vhdUpdate = 1;
	vhd.isFormated = 1;
}

/*************************************************
* FUNCTION
*	int howMuchEmpty();
* PARAMETERS
*   --–
* RETURN VALUE
*	int - number of free/empty clusters
* MEANING
*     This function checks how many clusters are empty. (in the dat map)
* SEE ALSO
*	int howMuchEmpty(unsigned int)
**************************************************/
int Disk::howMuchEmpty()
{
	int count = 0;
	for (int i = 4; i < 1600; i++)
		if (dat.dat[i])
			count++;
	return count;
}

/*************************************************
* FUNCTION
*	int howMuchEmpty(unsigned int)
* PARAMETERS
*   unsigned int start - 
* RETURN VALUE
*	int - number of free/empty clusters
* MEANING
*     This function checks how many clusters are empty. (in the dat map)
* SEE ALSO
*	int howMuchEmpty()
**************************************************/
int Disk::howMuchEmpty(unsigned int start)
{
	int count = 0;
	for (int i = start; i < 1600; i++)
		if (dat.dat[i])
			count++;
	return count;
}

/*************************************************
* FUNCTION
*
* PARAMETERS
*    int –
* RETURN VALUE
*
* MEANING
*     This function
* SEE ALSO
*
**************************************************/
bool Disk::firstFit(DATtype& fat, unsigned int clusters, unsigned int start)
{
	if (this->howMuchEmpty(start) < clusters)
		throw "Not enough space in disk";
	fat.reset();
	int i = start;
	while (clusters > 0 && i < 1600)
	{
		if (dat.dat[i])
		{
			dat.dat[i] = 0;
			fat[i] = 1;
			clusters--;
		}
		i++;
	}
	if (i >= 1600 && clusters > 0)
		throw "Oops, something went wrong";
	return true;
}

/*************************************************
* FUNCTION
*
* PARAMETERS
*    int –
* RETURN VALUE
*
* MEANING
*     This function
* SEE ALSO
*
**************************************************/
bool Disk::bestFit(DATtype& fat, unsigned int clusters, unsigned int start)
{
	if (howMuchEmpty(start) < clusters)
		throw "Not enough space in disk";
	int i = start;
	int bFitSize = 0;
	int bFitIndex = 0;
	int tmpBFitSize = 0;
	int tmpBFitIndex = 0;
	while (i < 1600)
	{
		tmpBFitSize = 0;
		if (dat.dat[i])
		{
			tmpBFitIndex = i;
			while (dat.dat[i])
			{
				tmpBFitSize++;
				i++;
			}
			if (clusters == tmpBFitSize)
			{
				bFitIndex = tmpBFitIndex;
				bFitSize = tmpBFitSize;
				break;
			}
			else if (clusters>tmpBFitSize)
			{
				if (tmpBFitSize > bFitSize)
				{
					bFitIndex = tmpBFitIndex;
					bFitSize = tmpBFitSize;
				}
			}
			else if (clusters < tmpBFitSize)
			{
				if (tmpBFitSize < bFitSize || bFitSize < clusters)
				{
					bFitIndex = tmpBFitIndex;
					bFitSize = tmpBFitSize;
				}
			}
		}
		else
			i++;
	}
	for (int i = 0; i < min(bFitSize, (int)clusters); i++)
	{
		dat.dat[i + bFitIndex] = 0;
		fat[i + bFitIndex] = 1;
	}
	if (clusters > bFitSize)
		bestFit(fat, clusters - bFitSize);
	return true;
}

/*************************************************
* FUNCTION
*
* PARAMETERS
*    int –
* RETURN VALUE
*
* MEANING
*     This function
* SEE ALSO
*
**************************************************/
bool Disk::worstFit(DATtype & fat, unsigned int clusters, unsigned int start)
{
	if (howMuchEmpty() < clusters)
		throw "Not enough space in disk";
	int maxLength = 0;
	int maxLengthIndex = 0;
	int tmpMaxLength = 0;
	int tmpMaxLengthIndex = 0;
	int i = start;
	while (i < 1600)
	{
		tmpMaxLength = 0;
		if (dat.dat[i])
		{
			tmpMaxLengthIndex = i;
			while (dat.dat[i])
			{
				tmpMaxLength++;
				i++;
			}
			if (tmpMaxLength> maxLength)
			{
				maxLength = tmpMaxLength;
				maxLengthIndex = tmpMaxLengthIndex;
				if (clusters == maxLength)
					break;
			}
		}
		else
			i++;
	}
	for (int i = 0; i < min(maxLength, (int)clusters); i++)
	{
		dat.dat[i + maxLengthIndex] = 0;
		fat[i + maxLengthIndex] = 1;
	}
	if (clusters > maxLength)
		worstFit(fat, clusters - maxLength);
	return true;
}

/*************************************************
* FUNCTION
*
* PARAMETERS
*    int –
* RETURN VALUE
*
* MEANING
*     This function
* SEE ALSO
*
**************************************************/
void Disk::alloc(DATtype & fat, unsigned int numOfSecs, unsigned int algo)
{
	unsigned int clusters;
	if (numOfSecs % 2 == 0) clusters = numOfSecs / 2;
	else clusters = (numOfSecs / 2) + 1;
	if (howMuchEmpty() < clusters)
		throw "Not enough space in disk!";
	switch (algo)
	{
	case 0:
		firstFit(fat, clusters,0);
		break;
	case 1:
		bestFit(fat, clusters,0);
		break;
	case 2:
		worstFit(fat, clusters,0);
		break;
	default:
		break;
	}

}

void Disk::allocExtend(DATtype& fat, unsigned int sectors, unsigned int algo)
{
	//Finding last allocated index;
	int lAlloc = 0;
	for (int i = 0; i < 1600; i++)
		if (fat[i])
			lAlloc = i;
	
	unsigned int clusters;
	if (sectors % 2 == 0) clusters = sectors / 2;
	else clusters = (sectors / 2) + 1;

	if (howMuchEmpty(lAlloc + 1) < clusters)
		throw "Not enough space in disk!";
	switch (algo)
	{
		case 0:
			firstFit(fat, clusters, lAlloc+1);
			break;
		case 1:
			bestFit(fat, clusters, lAlloc + 1);
			break;
		case 2:
			worstFit(fat, clusters, lAlloc + 1);
			break;
		default:
			break;
	}
}

void Disk::dealloc(DATtype& fat)
{
	dat.dat |= fat;
}
#pragma endregion

#pragma region Level2
void Disk::createFile(string & fn, string & fo, string & ft, unsigned int recLen, unsigned int numOfSecs, string & kt, unsigned int ko, unsigned int ks, unsigned int algo)
{
	try
	{
		int path =-1;
		for (int i = 0; i < 14; i++)
		{
			if (!strcmp(rootDir.lsbSector.dirEntry[i].getFileName(), fn.c_str()) || !strcmp(rootDir.msbSector.dirEntry[i].getFileName(), fn.c_str()))
				throw "File name in use";
			if (path == -1 && (rootDir.lsbSector.dirEntry[i].getEntryStatus() == 0 || rootDir.lsbSector.dirEntry[i].getEntryStatus() == 2))
			{
				path = i;
				break;
			}
			else if (path == -1 && (rootDir.msbSector.dirEntry[i].getEntryStatus() == 0 || rootDir.msbSector.dirEntry[i].getEntryStatus() == 2))
			{
				path = i + 14;
				break;
			}
		}
		if (path == -1)
			throw "To many files in the disk";
		
		DATtype fat;
		alloc(fat, numOfSecs, algo);
		int i = 0;
		unsigned int firstSector = -1;
		while (firstSector == -1 && i < 1600)
			if (fat[i])
				firstSector = i;
		DirEntry de(fn.c_str(), fo.c_str(), firstSector, numOfSecs, (numOfSecs-1)*(1024/recLen)-1, 
			recLen, recLen, ft.c_str()[0], ko, ks, kt.c_str(), '1');
		
		FileHeader fh(firstSector, de, fat);
		
		if (path >= 14 && path < 28)
			rootDir.msbSector.dirEntry[i - 14] = de;
		else if (path >= 0 && path < 14)
			rootDir.lsbSector.dirEntry[i] = de;
		else
			throw "Unknown Error!";
		writeSector(firstSector, (Sector*)&fh);
	}
	catch (char* str)
	{
		throw str;
	}
	catch (const std::exception& ex)
	{

	}
}

void Disk::delFile(string & fn, string & fo)
{
	try
	{
		int path = -1;
		for (int i = 0; i < 14; i++)
		{
			if (!strcmp(rootDir.lsbSector.dirEntry[i].getFileName(), fn.c_str()))
			{
				if (!strcmp(rootDir.lsbSector.dirEntry[i].getOwnerName(), fo.c_str()))
				{
					path = i;
					break;
				}
				else
				{
					throw "Only the file's owner can delete the file!";
					break;
				}
			}
			else if (!strcmp(rootDir.msbSector.dirEntry[i].getFileName(), fn.c_str()))
			{
				if (!strcmp(rootDir.msbSector.dirEntry[i].getOwnerName(), fo.c_str()))
				{
					path = i + 14;
					break;
				}
				else
				{
					throw "Only the file's owner can delete the file!";
					break;
				}
			}
		}
		if (path == -1)
			throw "File does not exist!";
		FileHeader* buffer = new FileHeader();
		if (path >= 14 && path < 28)
		{
			rootDir.msbSector.dirEntry[path - 14].setEntryStatus('2'); //2 = deleted
			readSector(rootDir.msbSector.dirEntry[path - 14].getFileAddr(), (Sector*)buffer);
			dealloc((*buffer).getFat());
		}
		else if (path > -1 && path < 14)
		{
			rootDir.lsbSector.dirEntry[path].setEntryStatus('2');
			readSector(rootDir.msbSector.dirEntry[path].getFileAddr(), (Sector*)buffer);
			dealloc((*buffer).getFat());
		}
		else throw "Unknown error!";
		delete buffer;
	}
	catch (const char* msg)
	{
		throw msg;
	}
	catch (const std::exception& e)
	{
		throw "Unknown error";
	}
	
}

void Disk::extendFile(string & fn, string & fo, unsigned int num)
{
	try
	{
		int path = -1;
		for (int i = 0; i < 14; i++)
		{
			if (!strcmp(rootDir.lsbSector.dirEntry[i].getFileName(), fn.c_str()))
			{
				if (!strcmp(rootDir.lsbSector.dirEntry[i].getOwnerName(), fo.c_str()))
				{
					path = i;
					break;
				}
				else
				{
					throw "Only the file's owner can delete the file!";
					break;
				}
			}
			else if (!strcmp(rootDir.msbSector.dirEntry[i].getFileName(), fn.c_str()))
			{
				if (!strcmp(rootDir.msbSector.dirEntry[i].getOwnerName(), fo.c_str()))
				{
					path = i + 14;
					break;
				}
				else
				{
					throw "Only the file's owner can delete the file!";
					break;
				}
			}
		}
		if (path == -1)
			throw "File does not exist!";
		
		DATtype fat;
		allocExtend(fat, num);
		if (path >= 14 && path < 28)
		{	
			unsigned int fileSize = rootDir.msbSector.dirEntry[path - 14].getFileSize();
			unsigned int recSize = rootDir.msbSector.dirEntry[path - 14].getRecSize();
			rootDir.msbSector.dirEntry[path - 14].setEofRecNr((fileSize + num - 1)*(1024 / recSize) - 1);
			rootDir.msbSector.dirEntry[path - 14].setFileSize(fileSize + num);
			FileHeader buffer(rootDir.msbSector.dirEntry[path - 14].getFileAddr(), rootDir.msbSector.dirEntry[path - 14], fat);
			writeSector(rootDir.msbSector.dirEntry[path - 14].getFileAddr(), (Sector*)&buffer);
		}
		else if (path > -1 && path < 14)
		{
			unsigned int fileSize = rootDir.msbSector.dirEntry[path].getFileSize();
			unsigned int recSize = rootDir.msbSector.dirEntry[path].getRecSize();
			rootDir.msbSector.dirEntry[path].setEofRecNr((fileSize + num - 1)*(1024 / recSize) - 1);
			rootDir.msbSector.dirEntry[path].setFileSize(fileSize + num);
			FileHeader buffer(rootDir.msbSector.dirEntry[path].getFileAddr(), rootDir.msbSector.dirEntry[path], fat);
			writeSector(rootDir.msbSector.dirEntry[path].getFileAddr(), (Sector*)&buffer);
		}
		else throw "Unknown error!";
	}
	catch (const char* msg)
	{
		throw msg;
	}
	catch (const std::exception& e)
	{
		throw "Unknown error";
	}
}
#pragma endregion

#pragma region Level3

FCB* Disk::openFile(string & fn, string & un, MODE io)
{
	try
	{
		int path = -1;
		for (int i = 0; i < 14; i++)
		{
			if (!strcmp(rootDir.lsbSector.dirEntry[i].getFileName(), fn.c_str()))
			{
				path = i;
				break;
			}
			if (!strcmp(rootDir.msbSector.dirEntry[i].getFileName(), fn.c_str()))
			{
				path = i+14;
				break;
			}
		}
		if (path == -1)
			throw "File Does Not Exist!";
		FileHeader* buffer = new FileHeader();
		if (path >= 14 && path < 28)
			readSector(rootDir.msbSector.dirEntry[path - 14].getFileAddr(), (Sector*)buffer);
		else if (path > -1 && path < 14)
			readSector(rootDir.msbSector.dirEntry[path].getFileAddr(), (Sector*)buffer);
		FCB fcb;
		fcb.path = path;
		fcb.mode = io;
		fcb.d = this;
		fcb.FAT = (*buffer).fat;
		fcb.fileDesc = (*buffer).fileDesc;
		fcb.numOfRecords = (*buffer).fileDesc.getEofRecNr();
		if (io == MODE::W || io == MODE::R || io == MODE::WR)
		{
			fcb.currRecNr = 0;
			fcb.currSecNr = fcb.fileDesc.getFileAddr();
			fcb.currRecNrInBuff = 0;
		}
		else if (io == MODE::E)
		{

			fcb.currRecNr = fcb.fileDesc.getEofRecNr()+1;
			fcb.currSecNr = fcb.fileDesc.getFileAddr()+fcb.fileDesc.getFileSize();
			fcb.currRecNrInBuff = 0;
		}
		delete buffer;
		return &fcb;
	}
	catch (const char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown Exception!";
	}
}

#pragma endregion

#pragma region Level4
	string& Disk::GetLastErrorMessage() { return this->lastErrorMessage; }
	void Disk::SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }
#pragma endregion



