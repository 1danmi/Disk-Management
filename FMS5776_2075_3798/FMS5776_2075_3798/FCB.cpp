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
	if (path >= 14 && path < 28)
		d->rootDir.msbSector.dirEntry[path - 14] = fileDesc;
	else if (path > -1 && path < 14)
		d->rootDir.msbSector.dirEntry[path] = fileDesc;
	d = nullptr;
}

void FCB::flushFile()
{
	if (lock)
		throw "The file is locked!";
	this->d->writeSector(this->currSecNr, &(this->buffer));
}

void FCB::readRecord(char * record , unsigned int update, unsigned int rec)
{
	try
	{
		if (lock)
			throw "The file is locked!";
		if (this->mode == MODE::W || this->mode == MODE::E)
			throw "The file is not open for reading!";
		if (rec != -1)
		{
			if (rec >= numOfRecords)
				throw "Record number out of range!";
			this->currRecNr = rec;
		}
		else if (currRecNr >= numOfRecords)
			throw "Record number out of range!";
		int numOfRecs = 1020 / this->fileDesc.getRecSize();
		this->currSecNr = numOfRecords / numOfRecs;
		if (currRecNrInBuff != currSecNr)
			d->readSector(fileDesc.getFileAddr() + currSecNr, &(this->buffer));
		int recNum = numOfRecords%numOfRecs-1;
		for (int i = 0; i < this->fileDesc.getRecSize(); i++)
			record[i] = this->buffer.rawData[recNum*this->fileDesc.getRecSize() + i];
		if (!update)
		{
			if (numOfRecords - currRecNr > 1)
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

void FCB::writeRecord(char * record, unsigned int rec)
{
	try
	{
		if (lock)
			throw "The file is locked!";
		if (this->mode == MODE::R || this->mode == MODE::E)
			throw "The file is not open for writing!";
		if (rec != -1)
		{
			if (rec >= numOfRecords)
				throw "Record number out of range!";
			this->currRecNr = rec;
		}
		else if (currRecNr >= numOfRecords)
			throw "Record number out of range!";
		int numOfRecs = 1020 / this->fileDesc.getRecSize();
		this->currSecNr = numOfRecords / numOfRecs;
		if (currRecNrInBuff != currSecNr)
			d->readSector(fileDesc.getFileAddr() + currSecNr, &(this->buffer));
		int recNum = numOfRecords%numOfRecs - 1;
		for (int i = 0; i < this->fileDesc.getRecSize(); i++)
			this->buffer.rawData[recNum*this->fileDesc.getRecSize() + i]=record[i];
		flushFile();
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