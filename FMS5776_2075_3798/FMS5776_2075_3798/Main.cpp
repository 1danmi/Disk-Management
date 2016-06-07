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
		string path;
		string username;
		string pwd;
		string str;
		int sLevel;
		int a = 0;
		char s[1020];
		Sector sec(a, s);
		switch (mode)
		{
		case 1:
			printStructSize();
			break;
		case 2:
			printDiskInfo(d);
			break;
		case 3:
			cout << "Enter Disk Name:\n";
			cin >> diskName;
			cout << "Enter Owner Name:\n";
			cin >> ownerName;
			cout << "Enter Owner Password:\n";
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
		case 4:
			cout << "Enter File's Path:\n";
			cin >> path;
			cout << "Mounting Disk...\n";
			d.mountDisk(path);
			cout << "Disk Mounted!\nWould you like to see the disk details?\n";
			cout << "1. Yeah, Sure!\n";
			cout << "2. No, I'm good\n";
			cin >> a;
			if (a == 1)
				startDebug(d, 2);
			break;
		case 5:
			cout << "Enter Username:\n";
			cin >> username;
			cout << "Enter Password:\n";
			cin >> pwd;
			cout << "Signing In...\n";
			d.signIn(username, pwd);
			if (d.sign)
				cout << "Signed in successfully!\n";
			break;
		case 6:
			cout << "Signing Out...\n";
			d.signOut();
			if (!d.sign)
				cout << "Signed out successfully!\n";
			break;
		case 7:
			if (!d.sign)
				throw "You must be signed in order to add user!";
			cout << "Enter Username:\n";
			cin >> username;
			cout << "Enter Password:\n";
			cin >> pwd;
			cout << "Choose security level:\n";
			cout << "1. User" << endl;
			if (d.currUser.sLevel >= SLEVEL::Administrator)
				cout << "2. Administrator" << endl;
			if (d.currUser.sLevel >= SLEVEL::Super_User)
				cout << "3. Super User" << endl;
			cin >> sLevel;
			if (sLevel > d.currUser.sLevel)
				throw "You can't create user with higher permission than yours!";
			d.addUser(username, (SLEVEL)sLevel, pwd, d.currUser.sLevel);
			cout << "User Added!\n";
			break;
		case 8:
			if (d.sign)
			{
				cout << "Enter Username to remove:\n";
				cin >> username;
				cout << "Removing...\n";
				d.removeUserSigned(username, d.currUser.sLevel);
				cout << "User removed successfully!\n";
			}
			else
			{
				cout << "Enter Username to remove:\n";
				cin >> username;
				cout << "Enter Password:\n";
				cin >> pwd;
				d.removeUser(username, pwd);
				cout << "User removed successfully!\n";
			}
			break;
		case 9:
			cin.ignore();
			cout << "Enter string to write:\n";
			getline(cin, str);
			strncpy_s(sec.rawData,1020, str.c_str(),1019);
			cout << "Enter sector number:\n";
			cin >> a;
			
			//strncpy_s(s,1020,str.c_str(),1019);
			cout << "Writing...\n";
			d.writeSector(a, &sec);
			cout << "OK!\n";
			break;
		case 10:
			cout << "Enter sector number:\n";
			cin >> a;
			cout << "Reading...\n";
			d.readSector(a, &sec);
			cout << "Sector Content:\n";
			cout << sec.rawData << endl;
			break;
		case 11:
			cout << "Unmounting disk...\n";
			d.unmountDisk();
			if (!d.mounted)
				cout << "Unmounted successfull!\n";
			break;
		default:
			break;
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
		cout << "	Mounted:          " << d.mounted << endl;
		cout << "	prodDate:         " << vh->prodDate << endl;
		cout << "	formatDate:       " << vh->formatDate << endl;
		cout << "	isFormated:       " << vh->isFormated << endl;
		cout << "	Users Info:\n";
		for (int i = 0; i < d.users.numOfUsers; i++)
			cout << "\t" << d.users.users[i].name << "\t" << d.users.users[i].password << "\t" << d.users.users[i].sLevel << endl;
		cout << "	Signed:           " << d.sign << endl;
		cout << "	currUser:         " << d.currUser.name << "\t" << d.currUser.password << "\t" << d.currUser.sLevel << endl;
		cout << "	ClusQty:          " << vh->ClusQty << endl;
		cout << "	addrDataStart:    " << vh->addrDataStart << endl;
		cout << "	dataClusQty:      " << vh->dataClusQty << endl;
		cout << "	addrDAT:          " << vh->addrDAT << endl;
		cout << "	addrRootDir:      " << vh->addrRootDir << endl;
		cout << "	addrUserSec:      " << vh->addrUserSec << endl;
		cout << "	addrDATcpy:       " << vh->addrDATcpy << endl;
		cout << "	addrRootDirCpy:   " << vh->addrRootDirCpy << endl << endl;
	}
	static void welcomeDebugLevel0(Disk& d)
	{
		int a;
		cout << "Welcome to Level 0 Debugging Mode!\nWhat would you like to do?\n";
		cout << "1. See structs Details\n";
		cout << "2. See disk Details\n";
		cout << "3. Create Disk\n";
		cout << "4. Mount Disk\n";
		cout << "5. Sign In\n";
		cout << "6. Sign Out\n";
		cout << "7. Add User\n";
		cout << "8. Remove User\n";
		cout << "9. Write Sector\n";
		cout << "10. Read Sector\n";
		cout << "11. Unmount Disk\n";
		cout << "12. Go back do debugging Level1\n";
		cin >> a;
		while (a!=12)
		{
			if (a > 12 || a < 1)
			{
				cout << "Illegal Command!\n";
			}
			else
			{
				try {
					startDebug(d, a);
				}
				catch (const char* str){
					cout << str << endl;
				}
			}
			cout << "Welcome to Level 0 Debugging Mode!\nWhat would you like to do?\n";
			cout << "1. See structs Details\n";
			cout << "2. See disk Details\n";
			cout << "3. Create Disk\n";
			cout << "4. Mount Disk\n";
			cout << "5. Sign In\n";
			cout << "6. Sign Out\n";
			cout << "7. Add User\n";
			cout << "8. Remove User\n";
			cout << "9. Write Sector\n";
			cout << "10. Read Sector\n";
			cout << "11. Unmount Disk\n";
			cout << "12. Go back do debugging Level1\n";
			cin >> a;
		}
	}

};

class Level1Debug
{
public:
	static void startDebug(Disk& d, int mode)
	{
		DATtype fat;
		int algo;
		int sectors;
		switch (mode)
		{
		case 1:
			Level0Debug::welcomeDebugLevel0(d);
			break;
		case 2:
			printDiskInfo(d);
			break;
		case 3:
			d.format();
			break;
		case 4:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)"<< endl;	
			d.firstFit(fat, 2,6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 5:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)" << endl;
			d.bestFit(fat, 2, 6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 6:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)" << endl;
			d.worstFit(fat, 2, 6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 7:
			cout << "How many sector to allocate?\n";
			cin >> sectors;
			cout << "Choose allocation algorithm:\n";
			cout << "1. First Fit\n";
			cout << "2. Best Fit\n";
			cout << "3. Worse Fit\n";
			cin >> algo;
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)" << endl;
			d.alloc(fat, sectors, algo-1,6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 8:
			cout << "How many sector to extend?\n";
			cin >> sectors;
			cout << "Choose allocation algorithm:\n";
			cout << "1. First Fit\n";
			cout << "2. Best Fit\n";
			cout << "3. Worse Fit\n";
			cin >> algo;
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before Allocation)" << endl;
			d.alloc(fat, 3,1,6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before Extention)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << "\t(Before Extention)" << endl;
			d.allocExtend(fat, sectors, algo - 1);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After Extention)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << "\t(After Extention)" << endl;
			cout << "Test Finished!\n";
			break;
		case 9:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before Allocation)" << endl;
			d.alloc(fat, 3, 1, 6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After Allocation)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << "\t(Before Allocation)" << endl;
			d.dealloc(fat);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After Deallocation)" << endl;
			cout << "Test Finished!\n";
			break;
		default:
			break;
		}

	}
	static void printDiskInfo(Disk& d)
	{
		VHD* vh = &d.vhd;

		cout << "	disk name:        " << vh->diskName << endl;
		cout << "	Owner Name:       " << vh->diskOwner << endl;
		cout << "	Mounted:          " << d.mounted << endl;
		cout << "	prodDate:         " << vh->prodDate << endl;
		cout << "	formatDate:       " << vh->formatDate << endl;
		cout << "	isFormated:       " << vh->isFormated << endl;
		cout << "	Users Info:\n";
		for (int i = 0; i < d.users.numOfUsers; i++)
			cout << "\t" << d.users.users[i].name << "\t" << d.users.users[i].password << "\t" << d.users.users[i].sLevel << endl;
		cout << "	Signed:           " << d.sign << endl;
		cout << "	currUser:         " << d.currUser.name << "\t" << d.currUser.password << "\t" << d.currUser.sLevel << endl;
		cout << "	ClusQty:          " << vh->ClusQty << endl;
		cout << "	addrDataStart:    " << vh->addrDataStart << endl;
		cout << "	dataClusQty:      " << vh->dataClusQty << endl;
		cout << "	addrDAT:          " << vh->addrDAT << endl;
		cout << "	addrRootDir:      " << vh->addrRootDir << endl;
		cout << "	addrUserSec:      " << vh->addrUserSec << endl;
		cout << "	addrDATcpy:       " << vh->addrDATcpy << endl;
		cout << "	addrRootDirCpy:   " << vh->addrRootDirCpy << endl << endl;
	}
	static void welcomeDebugLevel1(Disk& d)
	{
		int a;
		d.mountDisk(string("Disk1.fms"));
		cout << "Welcome to Level 1 Debugging Mode!\nWhat would you like to do?\n";
		cout << "1. Set Disk (level 0)\n";
		cout << "2. See disk Details\n";
		cout << "3. Format Disk\n";
		cout << "4. Check first fit algorithm\n";
		cout << "5. Check best fit algorithm\n";
		cout << "6. Check worse fit algorithm\n";
		cout << "7. Allocate space\n";
		cout << "8. Extend Allocation\n";
		cout << "9. Deallocate Space\n";
		cout << "10. Exit\n";
		cin >> a;
		while (a != 10)
		{
			if (a > 10 || a < 1)
			{
				cout << "Illegal Command!\n";
			}
			else
			{
				try {
					startDebug(d, a);
				}
				catch (const char* str) {
					cout << str << endl;
				}
			}
			cout << "Welcome to Level 1 Debugging Mode!\nWhat would you like to do?\n";
			cout << "1. Set Disk (level 0)\n";
			cout << "2. See disk Details\n";
			cout << "3. Format Disk\n";
			cout << "4. Check first fit algorithm\n";
			cout << "5. Check best fit algorithm\n";
			cout << "6. Check worse fit algorithm\n";
			cout << "7. Allocate space\n";
			cout << "8. Extend Allocation\n";
			cout << "9. Deallocate Space\n";
			cout << "10. Exit\n";
			cin >> a;
		}
	}
	static void setDatTest(Disk& d)
	{
		for (int i = 6; i < 1600; i++)
			d.dat.dat[i] = 0;
		d.dat.dat[6] = 0;
		d.dat.dat[7] = 1;
		d.dat.dat[8] = 1;
		d.dat.dat[9] = 1;
		d.dat.dat[10] = 0;
		d.dat.dat[11] = 0;
		d.dat.dat[12] = 0;
		d.dat.dat[13] = 0;
		d.dat.dat[14] = 1;
		d.dat.dat[15] = 1;
		d.dat.dat[16] = 0;
		d.dat.dat[17] = 1;
		d.dat.dat[18] = 1;
		d.dat.dat[19] = 1;
		d.dat.dat[20] = 1;
		d.dat.dat[21] = 0;
		/*for (int i = 6; i < 1600; i++)
			d.dat.dat[i] = 0;
		d.dat.dat[6] = 1;
		d.dat.dat[7] = 0;
		d.dat.dat[8] = 1;
		d.dat.dat[9] = 0;
		d.dat.dat[10] = 1;
		d.dat.dat[11] = 0;
		d.dat.dat[12] = 1;
		d.dat.dat[13] = 0;
		d.dat.dat[14] = 1;
		d.dat.dat[15] = 0;
		d.dat.dat[16] = 1;
		d.dat.dat[17] = 0;
		d.dat.dat[18] = 1;
		d.dat.dat[19] = 0;
		d.dat.dat[20] = 1;
		d.dat.dat[21] = 0;*/

	}
};
int main()
{	
	try{
		Disk d;
		Level1Debug::welcomeDebugLevel1(d);
	}
	catch (const char* str){
		cout << str << endl;
	}
	system("pause");
	return 0;
}