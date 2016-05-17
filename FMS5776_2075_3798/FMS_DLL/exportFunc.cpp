#include "Dir.h"
#include "VHD.h"
#include "FileHeader.h"
#include "Sector.h"
#include "FCB.h"

#pragma region Level0
__declspec(dllexport) void createDisk(Disk* THIS, char* diskName, char* diskOwner) 
{ 
	try 
	{ 
		THIS->createDisk(std::string(diskName), std::string(diskOwner));
	} 
	catch (exception ex) 
	{ 
		THIS->SetLastErrorMessage(ex.what());   throw ex; } 
}
__declspec(dllexport) void mountDisk(Disk* THIS, char* diskName)
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
__declspec(dllexport) void recreateDisk(Disk* THIS, char* diskOwner)
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
__declspec(dllexport) void format(Disk* THIS, char* diskOwner)
{
	try
	{
		THIS->format(std::string(diskOwner));
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
__declspec(dllexport) void createFile(Disk* THIS, char* & fn, char* & fo, char* & ft, unsigned int recLen, unsigned int numOfSecs, char* & kt, unsigned int ko, unsigned int ks, unsigned int algo)
{
	try
	{
		THIS->createFile(std::string(fn), std::string(fo), string(ft), recLen, numOfSecs, string(kt), ko, ks, algo);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
__declspec(dllexport) void delFile(Disk* THIS, char* fileName, char* fileOwner)
{
	try
	{
		THIS->delFile(std::string(fileName), std::string(fileOwner));
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
__declspec(dllexport) void extendFile(Disk* THIS, char* fileName, char* fileOwner, unsigned int size)
{
	try
	{
		THIS->extendFile(std::string(fileName), std::string(fileOwner), size);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());   throw ex;
	}
}
#pragma endregion

#pragma region Level3
__declspec(dllexport) FCB* openFile(Disk* THIS, char* fileName, char* fileOwner, MODE m)
{
	try
	{
		THIS->openFile(std::string(fileName), std::string(fileOwner), m);
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
__declspec(dllexport) void readRecord(FCB* THIS, char * record, unsigned int update, unsigned int rec)
{
	try
	{
		THIS->readRecord(record, update, rec);
	}
	catch (exception ex)
	{
		THIS->SetLastErrorMessage(ex.what());
		throw ex;
	}
}
__declspec(dllexport) void writeRecord(FCB* THIS, char * record, unsigned int rec)
{
	try
	{
		THIS->writeRecord(record, rec);
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
__declspec(dllexport) void deleteRecord(FCB* THIS)
{
	try
	{
		THIS->deleteRecord();
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
}
