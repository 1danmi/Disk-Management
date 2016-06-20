#include "FCB.h"

FCB::FCB()
{
	this->d = NULL;
	this->currRecNr = 0;
	this->currRecNrInBuff = 0;
	this->currSecNr = 0;
	this->FAT = NULL;
	this->maxRecNum = 0;
	this->loaded = 0;
	//this->DAT = NULL;
}

FCB::FCB(Disk * disk)
{
	this->d = disk;
	this->currRecNr = 0;
	this->currRecNrInBuff = 0;
	this->currSecNr = 0;
	this->FAT = NULL;
	this->maxRecNum = 0;
	this->numOfRecords = 0;
	this->loaded = 0;
	//this->DAT = NULL;
}

FCB::~FCB()
{
	//delete this->d;
	//delete this->DAT;
}

void FCB::closeFile()
{
	if (!loaded)
		throw "No file is open!";
	if (lock)
		throw "The file is locked!";
	//flushFile();
	FileHeader* fh = new FileHeader();
	this->d->readSector(this->fileDesc.getFileAddr(), (Sector*)fh);
	fh->fileDesc.eofRecNr = this->maxRecNum;
	strncpy_s(fh->fileDesc.fileName,12,this->fileDesc.fileName,11);
	fh->recInfo = recInfo;
	//fh->fat = this->FAT;
	this->d->writeSector(this->fileDesc.getFileAddr(), (Sector*)fh);
	if (path >= 14 && path < 28)
		d->rootDir.msbSector.dirEntry[path - 14] = fileDesc;
	else if (path > -1 && path < 14)
		d->rootDir.lsbSector.dirEntry[path] = fileDesc;
	d->rootDirUpdate = 1;
	d = nullptr;
	delete fh;
	loaded = 0;
}

void FCB::flushFile()
{
	this->d->writeSector(this->currSecNr, &(this->buffer));
}

void FCB::readRecord(char * record , int rec)
{
	try
	{
		if (!loaded)
			throw "No file is open!";
		if (this->DAT[rec] == 0 || this->DAT[rec] == 2)
			throw "Record does not exist!";
		if (lock)
			throw "The file is locked for update!";
		if (this->mode == MODE::W || this->mode == MODE::E)
			throw "The file is not open for reading!";
		int numOfRecsInSector = 1020 / this->fileDesc.getRecSize();
		int recSec = (rec / numOfRecsInSector + 1);
		int recCls = recSec / 2;
		int count = -1;
		int i = 0;
		while (i < 1600)
		{
			if (this->FAT[i])
			{
				count++;
				if (count == recCls)
					break;
			}
			i++;
		}

		if (i == 1600)
			throw "Wrong record number!";
		if (recSec % 2)
			i = i * 2 + 1;
		else
			i *= 2;
		
		d->readSector(i, &(this->buffer));

		currRecNrInBuff = rec%numOfRecsInSector;

		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
			record[i] = this->buffer.rawData[currRecNrInBuff*this->fileDesc.getRecSize() + i];
		if (numOfRecords - currRecNr > 1)
			this->currRecNrInBuff++;
		else
			currRecNr = 0;
	}
	catch (char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown Exception";
	}
}

void FCB::addRecord(char * record)
{
	try
	{
		/*if (lock)
			throw "the file is locked!";*/
		if (!loaded)
			throw "No file is open!";
		if (this->mode == MODE::R || this->mode == MODE::E)
			throw "the file is not open for writing!";
		if (numOfRecords == 36)
			throw "File is full!";
		if (this->numOfRecords == this->maxRecNum)
		{
			this->d->extendFile(string(this->fileDesc.fileName), 1);
			this->FAT = this->d->getFat(string(this->fileDesc.fileName));
			this->fileDesc.fileSize += 2;
			this->maxRecNum = maxRecNum + 2*(1020 / this->fileDesc.getRecSize());
		}
		int recNr = -1;
		for (int i = 0; i < 36 && i < maxRecNum; i++)
			if (!DAT[i])
			{
				DAT[i] = 1;
				recNr = i;
				break;
			}
		if (recNr == -1)
			throw "Weird error";
	
		int numOfRecsInSector = 1020 / this->fileDesc.getRecSize();
		int recSec = (recNr / numOfRecsInSector + 1);
		int recCls = recSec/2;
		int count = -1;
		int i = 0;
		while (i < 1600)
		{
			if (this->FAT[i])
			{
				count++;
				if (count == recCls)
					break;
			}
			i++;
		}

		if (i == 1600)
			throw "Wrong record number!";
		if (recSec % 2)
			i = i * 2 + 1;
		else
			i *= 2;
		d->readSector(i, &(this->buffer));
		currSecNr = i;
		currRecNrInBuff = recNr%numOfRecsInSector;
		char recKey[12];
		for (int i = 0; i < this->fileDesc.keySize; i++)
			recKey[i] = record[i + fileDesc.keyOffset];
		for (int i = 0; i < recInfo.size; i++)
			if (recInfo.records[i].recNr == recNr)
				throw "Weird Error 2";
		recInfo.records[recInfo.size] = RecEntry(recNr, recKey, this->fileDesc.keySize);
		recInfo.size++;
		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
			this->buffer.rawData[currRecNrInBuff*this->fileDesc.getRecSize() + i] = record[i];
		this->flushFile();

#pragma region Update
		numOfRecords++;
		FileHeader* fh = new FileHeader();
		this->d->readSector(this->fileDesc.getFileAddr(), (Sector*)fh);
		fh->fileDesc.eofRecNr = maxRecNum;
		strncpy_s(fh->fileDesc.fileName, 12, this->fileDesc.fileName, 11);
		fh->recInfo = recInfo;
		//fh->fat = this->FAT;
		this->d->writeSector(this->fileDesc.getFileAddr(), (Sector*)fh);
		if (path >= 14 && path < 28)
			d->rootDir.msbSector.dirEntry[path - 14] = fileDesc;
		else if (path > -1 && path < 14)
			d->rootDir.lsbSector.dirEntry[path] = fileDesc;
		d->rootDirUpdate = 1;
#pragma endregion


	}
	catch (char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown Exception";
	}
}

void FCB::updateCancel()
{
	lock = 0;
}

void FCB::deleteRecord(int rec)
{
	try
	{
		if (lock)
			throw "The file is not locked for update!";
		if (this->mode != MODE::WR && this->mode!= MODE::W)
			throw "The file is not open for updating!";
		if (!this->DAT[rec])
			throw "Record doesn't exist!";
		if (this->DAT[rec] == 2)
			throw "File already deleted";

		this->DAT[rec] = 2;
		
		for (int i = rec; i < this->recInfo.size; i++)
			this->recInfo.records[i] = this->recInfo.records[i+1];
		this->recInfo.size--;
		this->recInfo.records[this->recInfo.size] = RecEntry();
#pragma region Update
		numOfRecords--;
		FileHeader* fh = new FileHeader();
		this->d->readSector(this->fileDesc.getFileAddr(), (Sector*)fh);
		fh->fileDesc.eofRecNr = this->fileDesc.eofRecNr;
		strncpy_s(fh->fileDesc.fileName, 12, this->fileDesc.fileName, 11);
		fh->recInfo = recInfo;
		this->d->writeSector(this->fileDesc.getFileAddr(), (Sector*)fh);
		if (path >= 14 && path < 28)
			d->rootDir.msbSector.dirEntry[path - 14] = fileDesc;
		else if (path > -1 && path < 14)
			d->rootDir.lsbSector.dirEntry[path] = fileDesc;
		d->rootDirUpdate = 1;
#pragma endregion
	}
	catch (char* str)
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
		/*if (!lock)
			throw "The file is not locked for update!";*/
		if (this->mode != MODE::WR)
			throw "The file is not open for updating!";
		char recKey[12];
		for (int i = 0; i < this->fileDesc.keySize; i++)
			recKey[i] = record[i + fileDesc.keyOffset];
		int rec = this->recInfo.findRecordNr(string(recKey));
		if (rec == -1)
			throw "Record does not exit!";
		int numOfRecsInSector = 1020 / this->fileDesc.getRecSize();
		int recSec = (rec / numOfRecsInSector + 1);
		int recCls = recSec / 2;
		int count = -1;
		int i = 0;
		while (i < 1600)
		{
			if (this->FAT[i])
			{
				count++;
				if (count == recCls)
					break;
			}
			i++;
		}

		if (i == 1600)
			throw "Wrong record number!";
		if (recSec % 2)
			i = i * 2 + 1;
		else
			i *= 2;
		d->readSector(i, &(this->buffer));
		currSecNr = i;
		currRecNrInBuff = rec%numOfRecsInSector;
		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
			this->buffer.rawData[currRecNrInBuff*this->fileDesc.getRecSize() + i] = record[i];
		this->flushFile();

#pragma region Update
		numOfRecords++;
		FileHeader* fh = new FileHeader();
		this->d->readSector(this->fileDesc.getFileAddr(), (Sector*)fh);
		fh->fileDesc.eofRecNr = maxRecNum;
		strncpy_s(fh->fileDesc.fileName, 12, this->fileDesc.fileName, 11);
		fh->recInfo = recInfo;
		//fh->fat = this->FAT;
		this->d->writeSector(this->fileDesc.getFileAddr(), (Sector*)fh);
		if (path >= 14 && path < 28)
			d->rootDir.msbSector.dirEntry[path - 14] = fileDesc;
		else if (path > -1 && path < 14)
			d->rootDir.lsbSector.dirEntry[path] = fileDesc;
		d->rootDirUpdate = 1;
#pragma endregion

		
	}
	catch (char* str)
	{
		throw str;
	}
	catch (const std::exception&)
	{
		throw "Unknown Exception";
	}
}

bool FCB::getLoaded() { return this->loaded; }

RecEntry FCB::getRecEntry(int index)
{
	return this->recInfo.records[index];
}

unsigned int FCB::getRecInfoSize() { return this->recInfo.size; }

string& FCB::GetLastErrorMessage() { return this->lastErrorMessage; }
void FCB::SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }