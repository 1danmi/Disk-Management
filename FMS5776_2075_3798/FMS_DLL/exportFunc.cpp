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
__declspec(dllexport) void howMuchEmpty(Disk* THIS)
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
		THIS->createFile(std::string(fn), std::string(fo), string(ft), recLen, numOfSecs, string(kt), ko, ks, algo));
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
__declspec(dllexport) void delFile(Disk* THIS, char* fileName, char* fileOwner, MODE m)
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
__declspec(dllexport) void delFile(FCB* THIS)
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

#pragma endregion
