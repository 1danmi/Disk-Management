#include <iostream>
#include "Disk.h"

using namespace std;

class Level0Debug
{
public:
	static void startDebug(Disk& d,int mode)
	{
		string diskName;
		string ownerName;
		string ownerPwd;
		int a;
		switch (mode)
		{
		case 1:
			printStructSize();
		case 2:
			printDiskInfo(d);
		case 3:
		{
			cout << "Enter Disk Name:\n";
			cin >> diskName;
			cout << "Enter Owner Name:\n";
			cin >> ownerName;
			cout << "Enter Owner Password\n";
			cin >> ownerPwd;
			cout << "Creating Disk...\n";
			d.createDisk(diskName, ownerName, ownerPwd);
			cout << "Disk Created!\nWould you like to see the disk details?\n";
			cout << "1. Yeah, Sure!\n";
			cout << "2. No, I'm good\n";
			cin >> a;
			if (a == 1)
				startDebug(d, 2);
			break;
		}
		}
	}
	static void printStructSize()
	{
		cout << "start" << endl;
		cout << "Size Of Disk -->" << sizeof(Disk) << endl;
		cout << "Size Of Sector -->" << sizeof(Sector) << endl;
		cout << "Size Of VolumeHeader -->" << sizeof(VHD) << endl;
		cout << "Size Of DAT -->" << sizeof(DAT) << endl;
		cout << "Size Of DirEntry -->" << sizeof(DirEntry) << endl;
		cout << "Size Of SectorDir -->" << sizeof(SectorDir) << endl;
		cout << "Size Of FileHeader -->" << sizeof(FileHeader) << endl;
		cout << "Size Of usersSec -->" << sizeof(UsersSec) << endl;
		cout << "Size Of RootDir -->" << sizeof(RootDir) << endl;
	}
	static void printDiskInfo(Disk& d)
	{
		VHD* vh = &d.vhd;

		cout << "	disk name:        " << vh->diskName << endl;
		cout << "	Owner Name:       " << vh->diskOwner << endl;
		cout << "	prodDate:         " << vh->prodDate << endl;
		cout << "	formatDate:       " << vh->formatDate << endl;
		cout << "	isFormated:       " << vh->isFormated << endl;
		cout << "	addrDataStart:    " << vh->addrDataStart << endl;
		cout << "Users Info\n";
		for (int i = 0; i < d.users.numOfUsers; i++)
			cout << d.users.users[i].name << "\t" << d.users.users[i].password << endl;
		cout << "	ClusQty:          " << vh->ClusQty << endl;
		cout << "	dataClusQty:      " << vh->dataClusQty << endl;
		cout << "	addrDAT:          " << vh->addrDAT << endl;
		cout << "	addrRootDir:      " << vh->addrRootDir << endl;
		cout << "	addrDATcpy:       " << vh->addrDATcpy << endl;
		cout << "	addrRootDirCpy:   " << vh->addrRootDirCpy << endl << endl;
	}


};

int main()
{
	Disk d;
	cout << "Welcome to Level 0 Debuuging Mode!\nWhat would you like to do?\n";
	cout << "1. See structs Details\n";
	cout << "2. See disk Details\n";

	system("pause");
	return 0;
}