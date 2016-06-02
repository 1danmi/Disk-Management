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
	FileHeader* fh = new FileHeader();
	this->d->readSector(this->fileDesc.getFileAddr(), (Sector*)fh);
	fh->fileDesc = this->fileDesc;
	fh->fat = this->FAT;
	this->d->writeSector(this->fileDesc.getFileAddr(), (Sector*)fh);
	if (path >= 14 && path < 28)
		d->rootDir.msbSector.dirEntry[path - 14] = fileDesc;
	else if (path > -1 && path < 14)
		d->rootDir.msbSector.dirEntry[path] = fileDesc;
	d = nullptr;
	delete fh;
}

void FCB::flushFile()
{
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
		if (update)
			if (this->mode != MODE::WR)
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
		int recNum = numOfRecords%numOfRecs-1;
		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
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
		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
			this->buffer.rawData[recNum*this->fileDesc.getRecSize() + i]=record[i];
		flushFile();
		if (numOfRecords - currRecNr > 1)
			this->currRecNr++;
		else
			currRecNr = 0;
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

//void FCB::seek(unsigned int, int)
//{
//}

void FCB::updateCancel()
{
	lock = 0;
}

void FCB::deleteRecord()
{
	try
	{
		if (!lock)
			throw "The file is not locked for update!";
		if (this->mode != MODE::WR)
			throw "The file is not open for updating!";
		int numOfRecs = 1020 / this->fileDesc.getRecSize();
		this->currSecNr = numOfRecords / numOfRecs;
		int recNum = numOfRecords%numOfRecs - 1;
		for (unsigned int i = recNum*fileDesc.getRecSize(); i < fileDesc.getKeySize(); i++)
			buffer.rawData[i + fileDesc.getKeyOffset()] = 0;
		lock = 0;
		flushFile();
		if (numOfRecords - currRecNr > 1)
			this->currRecNr++;
		else
			currRecNr = 0;
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

void FCB::updateRecord(char * record)
{
	try
	{
		if (!lock)
			throw "The file is not locked for update!";
		if (this->mode != MODE::WR)
			throw "The file is not open for updating!";
		int numOfRecs = 1020 / this->fileDesc.getRecSize();
		this->currSecNr = numOfRecords / numOfRecs;
		int recNum = numOfRecords%numOfRecs - 1;
		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
			this->buffer.rawData[recNum*this->fileDesc.getRecSize() + i] = record[i];
		lock = 0;
		flushFile();
		if (numOfRecords - currRecNr > 1)
			this->currRecNr++;
		else
			currRecNr = 0;
		
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

string& FCB::GetLastErrorMessage() { return this->lastErrorMessage; }
void FCB::SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }