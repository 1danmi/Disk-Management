#include "FCB.h"



FCB::FCB()
{
	this->d = NULL;
	this->currRecNr = 0;
	this->currRecNrInBuff = 0;
	this->currSecNr = 0;
	this->FAT = NULL;
}

FCB::FCB(Disk * disk)
{
	this->d = disk;
	this->currRecNr = 0;
	this->currRecNrInBuff = 0;
	this->currSecNr = 0;
	this->FAT = NULL;
}

FCB::~FCB()
{
	delete this->d;
}

void FCB::closeFile()
{
	flushFile();
	FileHeader* fh;
	this->d->readSector(this->fileDesc.getFileAddr(), (Sector*)fh);
	fh->fileDesc = this->fileDesc;
	fh->fat = this->FAT;
	this->d->writeSector(this->fileDesc.getFileAddr(), (Sector*)fh);
	d = nullptr;
}

void FCB::flushFile()
{
	this->d->writeSector(this->currSecNr, &(this->buffer));
}

void FCB::readRecord(char * , unsigned int update)
{
	try
	{
		if (this->mode == MODE::O || this->mode == MODE::E)
			throw "The file is not open for reading!";

	}
	catch (const char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown Exception";
	}
}

void FCB::writeRecord(char *)
{
}

void FCB::seek(unsigned int, int)
{
}

void FCB::updateCancel()
{
}

void FCB::deleteRecord()
{
}

void FCB::updateRecord(char *)
{
}