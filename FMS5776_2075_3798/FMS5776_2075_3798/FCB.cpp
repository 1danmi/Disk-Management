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

void FCB::closefile()
{
}

void FCB::flushfile()
{
}

void FCB::readRecord(char *, unsigned int)
{
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