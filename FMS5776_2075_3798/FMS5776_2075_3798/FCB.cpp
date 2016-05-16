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
	if (lock)
		throw "The file is locked!";
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
	if (lock)
		throw "The file is locked!";
	this->d->writeSector(this->currSecNr, &(this->buffer));
}

void FCB::readRecord(char * record , unsigned int update)
{
	try
	{
		if (lock)
			throw "The file is locked!";
		if (this->mode == MODE::W || this->mode == MODE::E)
			throw "The file is not open for reading!";
		int numOfRecs = 1020 / this->fileDesc.getRecSize();
		if (currRecNr > numOfRecs)
			throw "Record number out of range!";
		for (int i = 0; i < this->fileDesc.getRecSize(); i++)
			record[i] = this->buffer.rawData[currRecNr*this->fileDesc.getRecSize() + i];
		if (!update)
		{
			if (numOfRecs - currRecNr > 1)
				this->currRecNr++;
			else
				currRecNr = 0;
		}
		else
			lock = 1;
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