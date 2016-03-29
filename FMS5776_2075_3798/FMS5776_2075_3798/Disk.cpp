#pragma warning (disable:4996)
#include "Disk.h"
#include <ctime>



/*************************************************
* FUNCTION
*	default Ctor
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

/*************************************************
* FUNCTION
*	mountDisk
* PARAMETERS
*    string& - file name.
* RETURN VALUE
*	---
* MEANING
*     This function mounts the disk
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
*	unmountDisk
* PARAMETERS
*	---
* RETURN VALUE
*	---
* MEANING
*     This function unmounts the disk
* SEE ALSO
*
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
*	recreateDisk
* PARAMETERS
*	string& - name of disk owner
* RETURN VALUE
*	---
* MEANING
*   This function recreates the disk. 
*	does the same then creating disk but doen't create a new file, instead just reinitializes the values.
*	conditions: a) file exists. b) wasn't mounted.
* SEE ALSO
*
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
*	getDskF1()
* PARAMETERS
*    ---
* RETURN VALUE
*	fstream*
* MEANING
*   This function 
* SEE ALSO
*
**************************************************/
fstream* Disk::getDskFl()
{
	if(dskfl.is_open())
		return &dskfl;
	return NULL;
}

/*************************************************
* FUNCTION
*	seekToSector
* PARAMETERS
*   unsigned int – number of sector to go to.
* RETURN VALUE
*	---
* MEANING
*   This function moves the I/O head to the wanted sector
* SEE ALSO
*
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
*	writeSector
* PARAMETERS
*   unsigned int - sector number to write on.
*	Sector* - sector to write.
* RETURN VALUE
*	---
* MEANING
*   This function writes a sector to the disk.
* SEE ALSO
*	---
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
*	writeSector
* PARAMETERS
*	Sector* - sector to write.
* RETURN VALUE
*	---
* MEANING
*   This function writes a sector to the disk.
* SEE ALSO
*	---
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
*	readSector
* PARAMETERS
*   int - sector number to write on.
*	Sector* - sector to write.
* RETURN VALUE
*	---
* MEANING
*   This function reads a sector on the disk.
* SEE ALSO
*	---
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
*	readSector
* PARAMETERS
*	Sector* - sector to write.
* RETURN VALUE
*	---
* MEANING
*   This function reads a sector on the disk.
* SEE ALSO
*	---
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

/*************************************************
* FUNCTION
*	format
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
*
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
*	howMuchEmpty()
* PARAMETERS
*   --–
* RETURN VALUE
*	int - number of free/empty clusters
* MEANING
*     This function checks how many clusters are empty. (in the dat map)
* SEE ALSO
*
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
bool Disk::firstFit(DATtype& fat, unsigned int clusters)
{
	if (this->howMuchEmpty() < clusters)
		throw "Not enough space in disk";
	fat.reset();
	int i = 0;
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
bool Disk::bestFit(DATtype& fat, unsigned int clusters)
{
	if (howMuchEmpty() < clusters)
		throw "Not enough space in disk!";
	int bFitSize = -1;
	int bFitIndex = -1;
	int tmpBestfit = 0;
	for (int i = 0; i < 1600; i++)
	{
		if (dat.dat[i])
			tmpBestfit++;
		/*else
		{
			if(tmpBestfit>bFitSize)

		}*/
	}
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
bool Disk::worstFit(DATtype & fat, unsigned int clusters)
{
	return false;
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
	switch (algo)
	{
	case 0:
		firstFit(fat, clusters);
		break;
	case 1:
		bestFit(fat, clusters);
		break;
	case 2:
		worstFit(fat, clusters);
		break;
	default:
		break;
	}

}

//FCB * Disk::openfile(string &, string &, string &)
//{
//	return nullptr;
//}




