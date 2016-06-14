#include "Disk.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>     

//#include "Dir.h"
//#include "VHD.h"
//#include "FileHeader.h"
//#include "Sector.h"
//#include "FCB.h"

#pragma region Level0
__declspec(dllexport) void createDisk(Disk* THIS, char* &diskName, char*& diskOwner, char* &pwd) 
{ 
	try 
	{ 
		THIS->createDisk(string(diskName), string(diskOwner),string(pwd));
	} 
	catch (exception ex) 
	{ 
		THIS->SetLastErrorMessage(ex.what());   throw ex; } 
}
__declspec(dllexport) void mountDisk(Disk* THIS, char* &diskName)
{
	try
	{
		THIS->mountDisk(std::string(diskName));
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
__declspec(dllexport) void unmountDisk(Disk* THIS)
{
	try
	{
		THIS->unmountDisk();
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
__declspec(dllexport) void recreateDisk(Disk* THIS, char* &diskOwner)
{
	try
	{
		THIS->recreateDisk(std::string(diskOwner));
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
#pragma endregion

#pragma region Level1
__declspec(dllexport) void format(Disk* THIS)
{
	try
	{
		THIS->format();
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
__declspec(dllexport) int howMuchEmpty(Disk* THIS)
{
	try
	{
		THIS->howMuchEmpty();
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
#pragma endregion

#pragma region Level2
__declspec(dllexport) void createFile(Disk* THIS, char* &fileName, char* & recordFormat, unsigned int recLen, unsigned int recNum, unsigned int numOfSecs, char* & keyType, SLEVEL sLevel, unsigned int keyOffset, unsigned int keySize, unsigned int algo)
{
	try
	{
		THIS->createFile(string(fileName), string(recordFormat), recLen, recNum, numOfSecs, string(keyType), sLevel, keyOffset, keySize, algo);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
__declspec(dllexport) void delFile(Disk* THIS, char* &fileName)
{
	try
	{
		THIS->delFile(string(fileName));
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
__declspec(dllexport) void extendFile(Disk* THIS, char* &fileName, unsigned int size)
{
	try
	{
		THIS->extendFile(string(fileName), size);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
#pragma endregion

#pragma region Level3
__declspec(dllexport) FCB* openFile(Disk* THIS, char* fileName, MODE m)
{
	try
	{
		THIS->openFile(string(fileName), m);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
#pragma endregion

#pragma region FCB
__declspec(dllexport) void closeFile(FCB* THIS)
{
	try
	{
		THIS->closeFile();
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   
		throw ex;
	}
}
__declspec(dllexport) void readRecord(FCB* THIS, char * record, unsigned int rec)
{
	try
	{
		THIS->readRecord(record, rec);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());
		throw ex;
	}
}
__declspec(dllexport) void addRecord(FCB* THIS, char * record)
{
	try
	{
		THIS->addRecord(record);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());
		throw ex;
	}
}
//no seek func

__declspec(dllexport) void updateRecord(FCB* THIS, char * record)
{
	try
	{
		THIS->updateRecord(record);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());
		throw ex;
	}
}
__declspec(dllexport) void deleteRecord(FCB* THIS, unsigned int rec)
{
	try
	{
		THIS->deleteRecord(rec);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());
		throw ex;
	}
}
__declspec(dllexport) void updateCancel(FCB* THIS)
{
	try
	{
		THIS->updateCancel();
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());
		throw ex;
	}
}
#pragma endregion

extern "C" 
{  
	__declspec(dllexport) Disk* makeDiskObject() 
	{ 
		return new Disk(); 
	}  
	__declspec(dllexport) void deleteDiskObject(Disk*& THIS) 
	{ 
		if (THIS != NULL)    delete  THIS;   
		THIS = NULL; 
	}  
	__declspec(dllexport) const char* getLastDiskErrorMessage(Disk* THIS) 
	{ 
		const char* str = THIS->GetLastErrorMessage().c_str();   
		return str; 
	}

	__declspec(dllexport) void  deleteFcbObject(FCB*& THIS) 
	{ 
		if (THIS != NULL)   delete  THIS;  
		THIS = NULL; 
	}
	__declspec(dllexport) const  char* getLastFcbErrorMessage(FCB* THIS) 
	{ 
		const char* str = THIS->GetLastErrorMessage().c_str();  
		return str; 
	}
}

// extra
//
//__declspec(dllexport)   void  getVolumeHeader(Disk* THIS, VHD* buffer)
//{
//	memcpy_s(buffer, sizeof(VHD), &THIS->getVHD(), sizeof(VHD));
//}
//
//string str;
//__declspec(dllexport) const char*  getDat(Disk* THIS)
//{
//	std::stringstream ss;
//	ss << THIS->getDat();
//	str = ss.str();
//	return str.c_str();
//}
