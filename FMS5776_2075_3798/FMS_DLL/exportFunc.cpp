#include "Disk.h";
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>     



extern "C"
{
	// init disk
	__declspec(dllexport) Disk*  makeDiskObject()
	{
		return new Disk();
	}
	__declspec(dllexport) void  deleteDiskObject(Disk*& THIS)
	{
		if (THIS != NULL)
			delete  THIS;
		THIS = NULL;
	}
	__declspec(dllexport) const  char*  getLastDiskErrorMessage(Disk* THIS)
	{
		const char* str = THIS->GetLastErrorMessage().c_str();
		return str;
	}

	__declspec(dllexport) void  deleteFcbObject(FCB*& THIS)
	{
		if (THIS != NULL)
			delete  THIS;
		THIS = NULL;
	}
	__declspec(dllexport) const  char*  getLastFcbErrorMessage(FCB* THIS)
	{
		const char* str = THIS->GetLastErrorMessage().c_str();
		return str;
	}

	// Level 0
	__declspec(dllexport) void  createDisk(Disk* THIS, char* diskName, char* diskOwner, char* password)
	{
		try
		{
			THIS->createDisk(string(diskName), string(diskOwner),  string(password));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  mountDisk(Disk* THIS, char* fileName)
	{
		try
		{
			THIS->mountDisk(string(fileName));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  unmountDisk(Disk* THIS)
	{
		try
		{
			THIS->unmountDisk();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  recreateDisk(Disk* THIS, char* diskOwner)
	{
		try
		{
			THIS->recreateDisk(string(diskOwner));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	__declspec(dllexport) void  addUser(Disk* THIS, char* user, SLEVEL sLevel, char* pwd, SLEVEL applicantSLevel)
	{
		try
		{
			THIS->addUser(string(user), sLevel, string(pwd), applicantSLevel);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  signIn(Disk* THIS, char* user, char* pwd)
	{
		try
		{
			THIS->signIn(string(user), string(pwd));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  signOut(Disk* THIS)
	{
		try
		{
			THIS->signOut();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  removeUser(Disk* THIS, char* user, char* pwd)
	{
		try
		{
			THIS->removeUser(string(user), string(pwd));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  removeUserSigned(Disk* THIS, char* user, SLEVEL applicantSLevel)
	{
		try
		{
			THIS->removeUserSigned(string(user), applicantSLevel);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}



	// Level 1
	__declspec(dllexport) void  format(Disk* THIS)
	{
		try
		{
			THIS->format();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) int   howMuchEmpty(Disk* THIS)
	{
		try
		{
			return THIS->howMuchEmpty();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	//Level 2
	__declspec(dllexport) void  createFile(Disk* THIS, char* fileName, char* recordFormat,
		unsigned int recLen, unsigned int recNum, unsigned int numOfSecs,
		char* keyType, SLEVEL sLevel, unsigned int keyOffset, unsigned int keySize, unsigned int algo)
	{
		try
		{
			THIS->createFile(string(fileName), string(recordFormat), recLen,
				recNum, numOfSecs,
				string(keyType), sLevel, keyOffset, keySize, algo);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	__declspec(dllexport) void  delFile(Disk* THIS, char* fileName)
	{
		try
		{
			THIS->delFile(string(fileName));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  extendFile(Disk* THIS, char* fileName, unsigned int num)
	{
		try
		{
			THIS->extendFile(string(fileName), num);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}


	// Level 3
	__declspec(dllexport)  FCB *  openFile(Disk* THIS, char* fileName, MODE openMode)
	{
		try
		{
			return THIS->openFile(string(fileName), openMode);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}


	// FCB
	__declspec(dllexport) void  closeFile(FCB* THIS)
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
	__declspec(dllexport) void  readRecord(FCB* THIS, char * record, unsigned int rec)
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
	__declspec(dllexport) void  addRecord(FCB* THIS, char * record)
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
	
	__declspec(dllexport) void  updateCancel(FCB* THIS)
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
	__declspec(dllexport) void  deleteRec(FCB* THIS, unsigned int rec)
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
	__declspec(dllexport) void  updateRecord(FCB* THIS, char * record)
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



	// extra

	__declspec(dllexport)   void  getVHD(Disk* THIS, VHD* buffer)
	{
		memcpy_s(buffer, sizeof(VHD), &THIS->getVHD(), sizeof(VHD));
	}

	string str;
	__declspec(dllexport) const char*  getDAT(Disk* THIS)
	{
		std::stringstream ss;
		//ss << THIS->getDAT();
		str = ss.str();
		return str.c_str();
	}

}
