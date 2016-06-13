#include "FCB.h"

FCB::FCB()
{
	this->d = NULL;
	this->currRecNr = 0;
	this->currRecNrInBuff = 0;
	this->currSecNr = 0;
	this->FAT = NULL;
	this->maxRecNum = 0;
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
	//this->DAT = NULL;
}

FCB::~FCB()
{
	delete this->d;
	//delete this->DAT;
}

void FCB::closeFile()
{
	if (lock)
		throw "The file is locked!";
	flushFile();
	FileHeader* fh = new FileHeader();
	this->d->readSector(this->fileDesc.getFileAddr(), (Sector*)fh);
	fh->fileDesc.eofRecNr = this->fileDesc.eofRecNr;
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
}

void FCB::flushFile()
{
	this->d->writeSector(this->currSecNr, &(this->buffer));
}

void FCB::readRecord(char * record , unsigned int update, unsigned int rec)
{
	try
	{
		if (this->DAT[rec] == 0 || this->DAT[rec] == 2)
			throw "Record does not exist!";
		if (lock)
			throw "The file is locked for update!";
		if (this->mode == MODE::W || this->mode == MODE::E)
			throw "The file is not open for reading!";
		if (update)
			if (this->mode != MODE::WR)
				throw "The file is not open for writing!";
		if (rec != -1)
			if (rec >= numOfRecords)
				throw "Record doesn't exist!";
		int numOfRecsInSector = 1020 / this->fileDesc.getRecSize();
		int recSec = rec / numOfRecsInSector+1;
		int count = -1;
		int i = 0;
		while( i < 1600)
		{
			if (this->FAT[i])
			{
				count++;
				if (count == recSec)
					break;
			}
			i++;
		}
		if (i == 1600)
			throw "Wrong record number!";
		if(currSecNr!=i)
			d->readSector(i, &(this->buffer));

		currRecNrInBuff = rec%numOfRecsInSector;

		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
			record[i] = this->buffer.rawData[currRecNrInBuff*this->fileDesc.getRecSize() + i];
		if (!update)
		{
			if (numOfRecords - currRecNr > 1)
				this->currRecNrInBuff++;
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

void FCB::addRecord(char * record, unsigned int rec)
{
	try
	{
		//if (lock)
		//	throw "The file is locked!";
		//if (this->mode == MODE::R || this->mode == MODE::E)
		//	throw "The file is not open for writing!";
		//if (recInfo.size == 45)
		//	throw "File is full!";
		//if (lock && rec == currRecNr)
		//{
		//	for (int i = 0; i < this->fileDesc.getRecSize(); i++)
		//		this->buffer.rawData[currRecNrInBuff*this->fileDesc.getRecSize() + i] = record[i];
		//	this->flushFile();
		//	return;
		//}
		//else if (lock)
		//{
		//	throw "The file is lock for update!";
		//}
		//else
		//{
		//	if (rec == -1)
		//	{ 
		//		if (maxRecNum == numOfRecords)
		//		{
		//			this->d->extendFile(string(this->fileDesc.fileName), 1);
		//			int newMaxRecNum = maxRecNum + (1024 / this->fileDesc.getRecSize());
		//			int* tmpDAT = new int[maxRecNum];
		//			for (int i = 0; i < newMaxRecNum; i++)
		//			{
		//				if (i < maxRecNum)
		//					tmpDAT[i] = DAT[i];
		//				else
		//					tmpDAT[i] = 0;
		//			}
		//			maxRecNum = newMaxRecNum;
		//			delete this->DAT;
		//			//this->DAT = tmpDAT;
		//		}
		//		for(int i=0;i<maxRecNum;i++)
		//			if (DAT[i] == 0 || DAT[i] == 2)
		//			{
		//				rec = i;
		//				break;
		//			}
		//		if (rec == -1)
		//			throw "Weird error";
		//		this->addRecord(record, rec);
		//	}
		//	else
		//	{
		//		
		//		int numOfRecsInSector = 1020 / this->fileDesc.getRecSize();
		//		int recSec = rec / numOfRecsInSector + 1;
		//		int count = -1;
		//		int i = 0;
		//		while (i < 1600)
		//		{
		//			if (this->FAT[i])
		//			{
		//				count++;
		//				if (count == recSec)
		//					break;
		//			}
		//			i++;
		//		}
		//		if (i == 1600)
		//			throw "Wrong record number!";

		//		if (currSecNr != i)
		//			d->readSector(i, &(this->buffer));
		//		currRecNrInBuff = rec%numOfRecsInSector;
		//		char* recKey = new char[this->fileDesc.keySize];
		//		for (int i = 0; i < this->fileDesc.keySize; i++)
		//			recKey[i] = record[i + fileDesc.keyOffset];
		//		recInfo.records[recInfo.size] = RecEntry(rec, recKey, this->fileDesc.keySize);
		//		recInfo.size++;
		//		for (unsigned int i = 0; i < this->fileDesc.getRecSize(); i++)
		//			this->buffer.rawData[currRecNrInBuff*this->fileDesc.getRecSize() + i] == record[i];
		//		this->flushFile();
		//	}
		//}
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

int FCB::findRecByKey(string & key)
{
	if (!strcmp(fileDesc.keyType, "I"))
	{
		int convKey = stoi(key, nullptr, 10);

	}
	else if (!strcmp(fileDesc.keyType, "D"))
	{
		double convKey = stod(key);
	}
	else if (!strcmp(fileDesc.keyType, "F"))
	{
		float convKey = stof(key);
	}
	else if (!strcmp(fileDesc.keyType, "S"))
	{
		char* tmpKey = new char[fileDesc.keySize];
		strncpy_s(tmpKey, fileDesc.keySize, key.c_str(), fileDesc.keySize - 1);
	}
	return -1;
}

string& FCB::GetLastErrorMessage() { return this->lastErrorMessage; }
void FCB::SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }